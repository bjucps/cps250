# Create static library

gcc -c add.c sub.c
ar rcs libmymath.a add.o sub.o

# Create shared library

gcc -c -fPIC add.c sub.c
gcc -shared -olibmymath.so add.o sub.o

# Compile with static library

gcc -static mymain.c -L. -lmymath -omymainstatic

# Compile with dynamic library

gcc mymain.c -L. -lmymath -omymainshared

# To execute mymainshared

Put libmymath.so in /usr/lib, or

export LD_LIBRARY_PATH=.