#!/usr/bin/env python
# -*- coding: UTF-8 -*-
import cv2
import numpy

def draw_flow(im, flow, step=16):
	print flow
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
	
cap = cv2.VideoCapture('/home/moro/Dropbox/Litteratursøk/video/referanse_fart.mp4')

ret, im = cap.read()
im = numpy.asarray(im[:,:])
prev_gray = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)

while True:
	ret, im = cap.read()
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

    # plot the flow vectors
	cv2.imshow('Optical flow',draw_flow(gray,flow))
	if cv2.waitKey(1) == 27:
		print "BREAK"
		break
	if cv2.waitKey(1) == 'r':
		print "RESET"
		flow = numpy.array((10,10), dtype=numpy.int32)
