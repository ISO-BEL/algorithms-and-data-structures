#include <stdio.h>

void move_zeroes(int* nums, int nums_size) 
{
	int j = 0;
	{
		int i = 0;
		while(i < nums_size)
		{
			if(nums[i])
			{
				nums[j] = nums[i];	
				j++;
			}
			i++
		}
	}
	//place zeros
	while(j < nums_size)
	{
		nums[j] = 0;	
		j++;
	}
}

void move_zeroes_first(int *nums, int nums_size)
{
	int i = 0;
	int end = nums_size - 1;
	while(i < end)
	{
		if(!nums[end])
		{	end--;
			continue;
		}
		else if(!nums[i])
		{
			int k = i;
			while(k < end)
			{	nums[k] = nums[k + 1];
				k++;
			}
			nums[end] = 0;
			end--;
		}
		if(nums[i])
			i++;
	}
}
int main(void)
{
	int array[10] = {1, 3, 0, 112, 5, 0, 0, 12, 0, 1};
	for(int i = 0; i < 10; i++)
		printf("[%d]", array[i]);
	printf("\n");

	move_zeroes(array, 10);
	for(int i = 0; i < 10; i++)
		printf("[%d]", array[i]);
	printf("\n");

	
	return 0;
}

