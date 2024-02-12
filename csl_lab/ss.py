# Simple Strings Demo (in Python)
#--------------------------------

name = input("Please enter your name: ").strip()
while name == "":
    name = input("Please enter your name: ").strip()

if len(name) > 20:
    print("That's a long name!")

if name[0].upper() == 'J':
    print("I see you have excellent taste in initials...")

if ' ' in name:
    split_spot = name.find(' ')
    first = name[:split_spot]
    rest = name[split_spot + 1:]
else:
    first = name
    rest = ''

print("May I call you " + first + " Q. " + rest + "?")
