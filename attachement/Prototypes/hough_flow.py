#!/usr/bin/env python
# -*- coding: UTF-8 -*-
import cv2
import cv
import numpy
import math
import matplotlib.pyplot as plt
import sys,os

def showHelp():
	print "Usage: {} <file>".format(sys.argv[0])

def getFileName():
	if len(sys.argv) != 2:
		showHelp()
		raise AttributeError('Incorrect number of arguments passed')
	if os.path.exists(sys.argv[1]):
		return sys.argv[1]
	raise IOError('File does not exist') 

def draw_flow(im, flow, step=16):
	h, w = im.shape[:2]
	y, x = numpy.mgrid[step/2:h:step, step/2:w:step].reshape(2, -1)
	fx, fy = flow[y,x].T
	
	lines = numpy.vstack([x, y, x+fx, y+fy]).T.reshape(-1, 2, 2)
	lines = numpy.int32(lines)
	
	vis = cv2.cvtColor(im, cv2.COLOR_GRAY2BGR)
	for (x1,y1),(x2,y2) in lines:
		cv2.line(vis, (x1,y1), (x2,y2), (0, 255, 0), 1)
		cv2.circle(vis, (x1, y1), 1, (0,255,0), -1)
	return vis
	
def generate_hough(gray):
	lines = 0
	edges = cv2.Canny(gray, 50, 200)
	print edges
	lines = cv2.HoughLinesP(edges, 1, math.pi/180, 100)
	vis = cv2.cvtColor(gray, cv2.COLOR_GRAY2BGR)
	#for rho, theta in lines[0][:100]:
		#a = math.cos(theta)
		#b = math.sin(theta)
		#x0 = a * rho
		#y0 = b * rho
		#x1 = int(x0 + 1000 * (-b))
		#y1 = int(y0 + 1000 * (a))
		#x2 = int(x0 - 1000 * (-b))
		#y2 = int(y0 - 1000 * (a))
		#cv2.line(vis, (x1,y1), (x2,y2), (0, 255, 0), 1)
	for x1,y1,x2,y2 in lines[0]:
		cv2.line(vis, (x1,y1), (x2,y2), (0,255,0), 2)
	return vis
	
def main():
	cap = cv2.VideoCapture(getFileName())
	ret, im = cap.read()
	prev_gray = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
	frame = 0
	while True:
		ret, im = cap.read()
		frame += 1
		gray = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
		print("Frame " + str(frame)) 
		try:
			cv2.imshow('HoughLines', generate_hough(gray))
		except TypeError:
			None
		
		flow = cv2.calcOpticalFlowFarneback(prev_gray,gray,0.5,1,3,15,3,5,1)
		prev_gray = gray

		# plot the flow vectors
		cv2.imshow('Optical flow',draw_flow(gray,flow))
		if cv2.waitKey(10) == 27:
			break

if __name__ == '__main__':
	main()
