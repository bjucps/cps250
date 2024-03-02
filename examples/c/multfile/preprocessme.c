#include <stdio.h>

#define WORLD "mondo"

#define PI 3.1415926

#define ADD(x, y) ((x) + (y))

#define SQUARE(x) ((x) * (x))

// Debug-builds-only logging macros
#ifdef DEBUG
#   define dlog(msg)       printf(__FILE__ ":%d:" msg "\n", __LINE__);
#	define dlogf(fmt, ...) printf(__FILE__ ":%d:" fmt "\n", __LINE__, __VA_ARGS__)
#else
#	define dlog(...)  /* NOTHING */
#	define dlogf(...) /* NOTHING */
#endif

int main()
{
	dlog("Abandon hope all ye who enter here...");
    puts("Hello " WORLD "!!");
	printf("Have some %f for dessert!\n", PI);
    
	int count = 0;
    printf("%d\n", ADD(2, 2) * 4);
    printf("%d\n", SQUARE(++count));
	dlogf("count ended up at %d", count);

#ifdef DEBUG
	puts("dump out a bunch of important stuff for debugging...");
#endif

    puts("We who are about to die salute you.");
}
