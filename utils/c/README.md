# C Data Structure Utility Libraries

## list.h

This is an in-line linked-list header-only library extracted from the Linux kernel source tree (GPL licensed, of course).

Read more about how to use it:

* [from kernelnewbies.org](https://kernelnewbies.org/FAQ/LinkedLists)
* [from the book Linux Device Drivers, 2nd Ed.](https://www.oreilly.com/library/view/linux-device-drivers/0596000081/ch10s05.html)

## utstring.h

Troy Hanson's BSD-licensed dynamic C-string object header-only macro library.

It provides only a few features, but important/useful ones:

* general "slice" management of a dynamically allocated/growable `char` buffer *(creating, clearing, freeing, accessing pointer/length)*
* operations for *appending* either raw bytes (`utstring_bincpy`), a formatted string (`utstring_printf`), or another `UT_string` instance (`utstring_concat`)
* a sophisticated/high-efficiency forward/reverse substring search facility (`utstring_find` and `utstring_findR`)

See more at the [project page](https://troydhanson.github.io/uthash/utstring.html).

**CAUTION**: pay close attention to the documentation and our example programs to understand the difference between `utstring_new` and `utstring_init`, between `utstring_free` and `utstring_done`

## uthash.h

Troy Hanson's BSD-licensed header-only macro library for implementing hash tables ("dictionaries").

See the [user guide](https://troydhanson.github.io/uthash/userguide.html) for more details.
