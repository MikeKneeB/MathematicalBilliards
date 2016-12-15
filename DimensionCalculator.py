#!/usr/bin/python

import argparse
import numpy
import math

parser = argparse.ArgumentParser('Calculates box dimensions of a fractal image.')

parser.add_argument('datafile', nargs=1, help='Data file.')
parser.add_argument('maxboxes', nargs=1, type=int, help='Root number of boxes to use.')

def main():
	args = parser.parse_args()	
	
	data = numpy.loadtxt(args.datafile[0], skiprows=1, usecols = (5, 6))
	datatsize = len(data)

	maxsize = 10

	outfile = open('boxdim.dat', 'w')
	outfile.write('{0:<10}{1:<17}{2:<17}{3:<10}{4:<10}\n'.format('nboxes', 'boxlen', 'iboxlen', 'count', 'boxdim'))

	for i in range(1, args.maxboxes[0]+1):
		output = numpy.zeros([i, i])
		boxlen = 1.0*maxsize*2/i
		for j in range(i):
			for k in range(i):
				box = (-maxsize + k*boxlen, -maxsize + j*boxlen)	
				for point in data:
					if checkin(box, boxlen, point):
						output[k][j] += 1 
		count = countfull(output)
		outfile.write('{0:<10}{1:<17}{2:<17}{3:<10}\n'.format(i*i, boxlen, 1.0/boxlen, count))

	outfile.close()

def checkin(box, boxlen, point):
	if point[0] > box[0] and point[0] < box[0] + boxlen and point[1] > box[1] and point[1] < box[1] + boxlen:
		return True
	else:
		return False

def countfull(data):
	length = len(data)
	output = 0
	for i in range(length):
		for j in range(length):
			if data[j][i] != 0:
				output += 1
	
	return output

if __name__ == '__main__':
	main()   
