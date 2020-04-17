#!/usr/bin/env python3

import argparse

parser = argparse.ArgumentParser(description='Configures 4690 controllers.')
parser.add_argument('--ip', required=False, help='IP Address')
parser.add_argument('--quiet', action='store_true', help='Minimize output to screen')
args = parser.parse_args()

if args.ip:
    print('IP Address:', args.ip)
else:
    print('No IP Address Supplied')
print('Quiet:', args.quiet)

