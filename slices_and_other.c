#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

//slices (strings)
typedef struct string
{
	char *text;
	int length;
}String;

//safe array in c
typedef struct SafeIntArray64
{
	int64_t *data;	
	size_t length;
	size_t cap;
}int_array64;

//mutiple returns in functions
struct num_err
{	
	int num;
	int err;
};
struct num_err add(int x, int y)
{
	struct num_err d;
	d.num = x + y;
	d.err = 0;
	return d;
}

static inline void place_in_slice(String slice, char *t)
{
	for(int i = 0; i < slice.length; i++)
	{	if(!*t)
		{ break;
		}
		slice.text[i] = t[i];
	}
}
static inline void print_slice(String slice)
{
	for(int i = 0; i < slice.length; i++)
	{	if(!slice.text[i]) break;
		printf("%c", slice.text[i]);
	}
	printf("\n");
}
static inline void print_pool(String pool, int seg)
{
	for(int i = 0; i < pool.length; i = i + seg)
	{	if(!pool.text[i] || !pool.text[i + 1]) break; //TODO : figure out why i need [i + 1] condition to fix
		for(int j = i; j < i + seg && j < pool.length; j++)
		{
			if(!pool.text[j]) break;
			printf("%c", pool.text[j]);
		}
		printf("\n");
	}
}
int main(void)
{
	//memory curruption consern when acessing the memory in the allocated pool that hasnt been assigned
	//the strings end with a zero
	String dialog_pool;
	dialog_pool.length = 2000;
	dialog_pool.text = malloc(dialog_pool.length);
	memset(dialog_pool.text, 0, dialog_pool.length);

	//starts at a location
	//length determines its end	
	String line1;
	line1.text = dialog_pool.text + 0;	
	line1.length = 100;
	String line2;
	line2.text = dialog_pool.text + 100;	
	line2.length = 200;

	place_in_slice(line1, "welcome young chap, nice seeing you here.");
	place_in_slice(line2, "welcome young chap, nice seeing you here, buddy");
	printf("%s\n", line1.text);
	printf("%s\n", line2.text);
	print_slice(line2);
	printf("\n");
	print_pool(dialog_pool, 100);

	struct num_err s;
	s = add(10, 39);
	printf("num = %d\n", s.num);
	printf("err = %d\n", s.err);

	int_array64 numbers;
	numbers.data = malloc((sizeof *numbers.data) * 100);
	numbers.cap = 100;
	numbers.length = 0;
	
	return 0;
}
