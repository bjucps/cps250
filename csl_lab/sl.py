# Simple List (Array) Demo in Python
#-----------------------------------

def show_nums(num_list: list):
    nsum = 0
    print(f"I have {len(num_list)} numbers here...")
    for i, n in enumerate(num_list):
        nsum += n
        print(f"num_list[{i}] = {n}; nsum = {nsum}")
    print()

nums = [1, 2, 3, 4]
show_nums(nums)

nval = int(input("Enter a number: "))
npos = int(input("Where should I insert it? "))
if not (0 <= npos < len(nums)):
    print("Naughty user!  I can't insert it there!  I'll do it at the end...")
    npos = len(nums)

nums.insert(npos, nval)
show_nums(nums)

menu_items = [
    ('a', 'Apples'),
    ('b', 'amBrosia'),
    ('c', 'aCorns'),
]
print("Would you like:")
print("---------------")
for tag, name in menu_items:
    print(f"({tag}): {name}")
print("---------------")

choice = input("> ")[0]
chosen = None
for tag, name in menu_items:
    if tag == choice:
        chosen = name
        break

if not chosen:
    print("Hey, you didn't choose anything!")
else:
    print(f"I see you chose {chosen}!")    

