#!/usr/bin/env python
# -*- coding: UTF-8 -*-
import cv2
import numpy
import operator
import matplotlib.pyplot as plt
import sys,os

move = None

def showHelp():
	print "Usage: {} <file>".format(sys.argv[0])

def getFileName():
	if len(sys.argv) != 2:
		showHelp()
		raise AttributeError('Incorrect number of argumenst passed')
	if os.path.exists(sys.argv[1]):
		return sys.argv[1]
	raise IOError('File does not exist') 
	

def draw_flow(im, flow, step=32):
	global move
	h, w = im.shape[:2]
	y, x = numpy.mgrid[step/2:h:step, step/2:w:step].reshape(2, -1)
	fx, fy = flow[y,x].T
	if move is None:
		move = flow[y,x].T
	else:
		move += flow[y,x].T
	
	lines = numpy.vstack([x, y, x+fx, y+fy]).T.reshape(-1, 2, 2)
	lines = numpy.int32(lines)
	vis = cv2.cvtColor(im, cv2.COLOR_GRAY2BGR)
	for (x1,y1),(x2,y2) in lines:
		cv2.line(vis, (x1,y1), (x2,y2), (0, 255, 0), 1)
		cv2.circle(vis, (x1, y1), 1, (0,255,0), -1)
	return vis

def main():	
	cap = cv2.VideoCapture(getFileName())
	ret, im = cap.read()
	if ret is False:
		print "Failed to read file {}".format(getFileName())
		return
	im = numpy.asarray(im[:,:])
	prev_gray = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
	points = []

	while True:
		ret, im = cap.read()
		if ret is False:
			break
		im = numpy.asarray(im[:,:])
		gray = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
		flow = numpy.array((10,10), dtype=numpy.int32)
		flow = cv2.calcOpticalFlowFarneback(
			prev=prev_gray, 
			next=gray,
			flow=None,
			pyr_scale=float(0.5), 
			levels=1, 
			winsize=9, 
			iterations=1, 
			poly_n=7, 
			poly_sigma=float(1.5),
			flags=cv2.OPTFLOW_FARNEBACK_GAUSSIAN)
		prev_gray = gray

		#move_temp = numpy.array([0.0, 0.0])
		#for i in flow:
		#	for j in i:
		#		move_temp += j
		#
		#move_temp /= flow.shape[0] * flow.shape[1]
		#move += move_temp
		#print "Movement between frames:"
		#print move_temp
		
		# plot the flow vectors
		cv2.imshow('Original', im)
		cv2.imshow('Optical flow',draw_flow(gray,flow))
		m = numpy.divide(move.sum(axis=1), flow.shape[0] * flow.shape[1])
		print "Total movement: {}".format(m)
		p = (m[0], m[1])
		points.append(p)	
		if cv2.waitKey(1) == 27:
			print "BREAK"
			break
		if cv2.waitKey(1) == 'r':
			print "RESET"
			flow = numpy.array((10,10), dtype=numpy.int32)
		
	
	plt.figure(1)
	line = plt.plot(points)
	plt.legend(line, ('Horizontal', 'Vertical'), 'best')
	plt.xlabel('Frame')
	plt.ylabel('Movement')
	plt.title('Farneback Movement')

	xp = []
	yp = []
	for p in points:
		xp.append(p[1])
		yp.append(p[0])

	plt.figure(2)
	line = plt.plot(yp,xp)
	plt.xlabel('Horizontal Movement')
	plt.ylabel('Vertical Movement')
	plt.title('Farneback Movement, x-y plot')
	plt.annotate('Start', xy=(0, 0), xytext=(-20, 400),arrowprops=dict(facecolor='black', shrink=0.05))
	plt.show()
	
if __name__ == '__main__':
	main()
