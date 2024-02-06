#include <stdio.h>
#include <assert.h>

struct intslice {
    int   *data;
    size_t used;
    size_t size;
};

int sum_intslice(struct intslice *s) {
    int sum = 0;
    for (size_t i = 0; i < s->used; ++i) {
        sum += s->data[i];
    }
    return sum;
}

void append_intslice(struct intslice *slice, int new_value) {
    assert(slice->used < slice->size);
    slice->data[slice->used] = new_value;
    slice->used += 1;
}

int main() {
    int storage[10];
    struct intslice arr = {
		.data = storage,
        .used = 0,
        .size = sizeof(storage) / sizeof(int),
    };

    append_intslice(&arr, 1);
    append_intslice(&arr, 2);
    append_intslice(&arr, 3);
    append_intslice(&arr, 42);

	for (size_t i = 0; i < arr.used; ++i) {
		printf("slice[%zu] = %d\n", i, arr.data[i]);
	}
	printf("sum is %d\n", sum_intslice(&arr));

	return 0;
}
