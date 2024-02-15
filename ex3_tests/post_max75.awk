#!/usr/bin/env -S awk -f

BEGIN {
	FS = ":"	# input: separate fields on ":" characters
	OFS = "\t"	# outout: separate fields with "\t" characters
}

# for each line of input ("word:line:col")
{
	# word_index is an associative array mapping "word" to "L1:C1[ L2:C2[ ...]]"
	if ($1 in word_index) {
		word_index[$1] = word_index[$1] " " $2 ":" $3
	} else {
		word_index[$1] = $2 ":" $3
	}
	
	# word_count is an associative array mapping "word" to count
	word_count[$1]++;
}

END {
	# print out word list with counts/indices
	for (word in word_index) {
		print word, word_count[word], word_index[word]
	}
}
