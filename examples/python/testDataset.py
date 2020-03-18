# test_Dataset.py
from Dataset import Dataset

def main():
	print 'This is a program to compute the min, max, mean, and'
	print 'standard deviation for a set of numbers. \n'

	data = Dataset()
	while True:
		xStr = raw_input('Enter a number: ')
		if xStr == '':
			break;
		try:
			x = float(xStr)
		except ValueError:
			print 'Invalid Entry Ignored: Input was not a number'
			continue
		data.add(x)

	print 'Summary of ...'

if __name__ == '__main__':
	main()

