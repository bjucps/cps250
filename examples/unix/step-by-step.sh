#!/bin/sh

tr -cs A-Za-z '\n' | tee step1.txt |\
	tr A-Z a-z | tee step2.txt |\
	sort | tee step3.txt |\
	uniq -c | tee step4.txt |\
	sort -rn | tee step5.txt |\
	sed "${1}q"
