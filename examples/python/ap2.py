#!/usr/bin/env python3
import argparse

parser = argparse.ArgumentParser(description='Configures 4690 controllers.')
parser.add_argument('-q', '--quiet', action='store_true', default=False, help="Pipe down while outputting.")
parser.add_argument('infile', help='Input file')
parser.add_argument('outfile', nargs='?', help='Output file')
parser.add_argument('-e', '--encoding', default="utf-8", help="Character encoding to use")

args = parser.parse_args()

print('Input file:', args.infile)
print('Output file:', args.outfile) # args.outfile may be None
print('Quiet mode?', args.quiet)
print('Encoding:', args.encoding)
