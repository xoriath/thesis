#!/usr/bin/env python
# -*- coding: UTF-8 -*-
import cv2
import numpy
import operator
import matplotlib.pyplot as plt
import sys,os

def showHelp():
	print "Usage: {} <file>".format(sys.argv[0])

def getFileName():
	if len(sys.argv) != 2:
		showHelp()
		raise AttributeError('Incorrect number of argumenst passed')
	if os.path.exists(sys.argv[1]):
		return sys.argv[1]
	raise IOError('File does not exist') 
def main():
	filename = getFileName()
	cap = cv2.VideoCapture(filename)

	ret, im = cap.read()
	im = im.astype('float32')
	prev_gray = cv2.cvtColor(im,cv2.COLOR_BGR2GRAY)
	move = None
	points = []

	while True:
		ret, im = cap.read()
		if ret is False:
			break
		im = im.astype('float32')
		im = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
		p = cv2.phaseCorrelate(im,prev_gray)
		prev_gray = im

		# P is movement form top left = (0,0), so need to invert all numbers
		if move is None:
			move = (-p[0], -p[1])
		else:
			move = ( move[0] - p[0], move[1] - p[1])	
		print move
		points.append(move)
		#print 'Total move: ', move

	plt.figure(1)
	line = plt.plot(points)
	plt.legend(line, ('Horizontal', 'Vertical'), 'best')
	plt.xlabel('Frame')
	plt.ylabel('Movement')
	plt.title('Phase Correlation Movement')

	xp = []
	yp = []
	for p in points:
		xp.append(p[1])
		yp.append(p[0])

	plt.figure(2)
	line = plt.plot(yp,xp)
	plt.xlabel('Horizontal Movement')
	plt.ylabel('Vertical Movement')
	plt.title('Phase Correlation Movement, x-y plot')
	plt.annotate('Start', xy=(0, 0), xytext=(-20, 400),arrowprops=dict(facecolor='black', shrink=0.05))
	plt.show()

if __name__ == '__main__':
	main()
