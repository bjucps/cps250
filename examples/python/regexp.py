#!/usr/bin/python3

import re

# find a contraction in a sentence
sentence = "This sentence doesn't contain anything much, but I'll be jiggered."
#apostrophe matches itself
#finds contractions
match = re.search("[a-z]+'[a-z]+", sentence)
if match:
   #group returns text that is matched
    print("Found contraction:", match.group())


# find a date in a sentence and extract its parts
sentence = "At 5/21/2003, 3:50pm, something will happen."
match = re.search(r"(\d\d?)/(\d\d?)/(\d\d\d\d)", sentence)
if match:
    print("Found date:", match.group())
    month, day, year = match.group(1, 2, 3)
    print("Month: %s; Day: %s; Year: %s\n" % (month, day, year))

# A commented regular expression with the re.VERBOSE flag 
match = re.search(r"""
    (\d\d?)   # Month
    /(\d\d?)  # Day
    /(\d\d\d\d) # Year
    """, 
    sentence,
    re.VERBOSE)


sentence = "He said, 'I like Java!'"

# extract all the words in a sentence
# findall returns all occurrence of regular expressions
matchList = re.findall("[a-zA-Z]+", sentence)
print(matchList)
