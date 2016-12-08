#!/usr/bin/python

import argparse
import numpy

parser = argparse.ArgumentParser('REEEEE')

parser.add_argument('datafile', nargs=1, help='Data file.')

def main():
	args = parser.parse_args()	
	
	data = numpy.loadtxt(args.datafile[0], skiprows=1, usecols = (5, 6))
	datatsize = len(data)

	#print data

	maxsize = 60

	for i in range(1, 11):
		output = numpy.zeros([i, i])
		boxlen = maxsize*2/i
		for j in range(i):
			for k in range(i):
				box = (-maxsize + k*boxlen, -maxsize + j*boxlen)	
				for point in data:
					if checkin(box, boxlen, point):
						output[k][j]++

def checkin(box, boxlen, point):
	if point[0] > box[0] and point[0] < box[0] + boxlen and point[1] > box[1] and point[1] < box[1] + boxlen:
		return True
	else
		return False

if __name__ == '__main__':
	main()   
