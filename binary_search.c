#include <stdio.h>
//review

//assumes a sorted arry
int binary_search(int *array, int max, int min, int key)
{
	while(min <= max)
	{
		int center = min + (max - min) / 2; 
		if(array[center] == key)
		{
			return center; //return location
		}
		else if(key > array[center]) 
		{
			min = center + 1;
		}
		else 
		{
			max = center - 1;
		}
	}
	return -1;
}
int main(void)
{
	int sorted_array[10] = {2, 6, 7, 8, 9, 10, 12, 16, 18, 20};
	int result = binary_search(sorted_array, 10, 0, 8);
	printf("resulting index: %d", result);

	return 0;
}
