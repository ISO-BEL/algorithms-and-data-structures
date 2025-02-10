#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct btree *create_node(int data);

struct btree
{
	int value;	
	int index;
	struct btree *lr[2];
};
//if null is reached in both directions (free)
void dfs_destroy_tree(struct btree *node)
{
	if(!node) return;
	dfs_destroy_tree(node->lr[0]);
	//cant move leftward
	dfs_destroy_tree(node->lr[1]);
	//cant move rightward or leftward
	free(node);
}
struct btree *create_tree(int *array, int size, int i)
{
	struct btree *node = NULL; 
	if(i < size)
	{
		node = create_node(array[i]);

		node->lr[0] = create_tree(array, size, 2 * i + 1);
		node->lr[1] = create_tree(array, size, 2 * i + 2);
	}
	return node;
}
struct btree *create_node(int data)
{
	struct btree *temp = malloc(sizeof(struct btree));
	temp->value = data;
	//temp->lr = NULL
	temp->lr[0] = NULL;
	temp->lr[1] = NULL;
	return temp;
}
int find_node(int data, struct btree *root)
{
	struct btree *temp = root;
	int depth = 0;
	while(temp)
	{
		if(temp->value == data)
			return depth;
		else if(data > temp->value)
			temp = temp->lr[1];
		else
			temp = temp->lr[0];

		depth++;
	}
	return -1;
}
void dfs_into_array(struct btree *node, int *array, int size, int i) 
{
	if(!node) return;
	
	dfs_into_array(node->lr[0], array, size, i);
	if(i < size)
	{
		array[i] = node->value;
		i++;
	}
	dfs_into_array(node->lr[1], array, size, i);
}
void in_order_dfs(struct btree *node)
{
	if(!node) return;
	in_order_dfs(node->lr[0]);
	printf("%d ", node->value);
	in_order_dfs(node->lr[1]);
}
void pre_order_dfs(struct btree *node)
{
	if(!node) return;
	printf("%d ", node->value);
	pre_order_dfs(node->lr[0]);
	pre_order_dfs(node->lr[1]);
}
void post_order_dfs(struct btree *node)
{
	if(!node) return;
	post_order_dfs(node->lr[0]);
	post_order_dfs(node->lr[1]);
	printf("%d ", node->value);
}
void bfs(struct btree *node)
{
	

}
int main(void)
{
	struct btree *first;
	struct btree *second;
	struct btree *third;
	struct btree *fourth;

	first = create_node(19);
	second = create_node(12);
	third = create_node(10);
	fourth = create_node(43);

	first->lr[0] = second;
	first->lr[1] = fourth;
	second->lr[0] = third;

	int size = 20;
	int array[20] = {0};
	int i = 0;
//	dfs_into_array(first, array, size, i);
//	for(int i = 0; i < size; i++) 
//		printf("[%d]", array[i]);
//	printf("\n");

	int depth = find_node(10, first);
	printf("depth: %d\n", depth);
	in_order_dfs(first);
	printf("\n");
	pre_order_dfs(first);
	printf("\n");
	post_order_dfs(first);
	printf("\n");

	int arr[12] = {2, 4, 5, 6, 3, 1, 6, 7, 8, 4, 7, 3};
	struct btree *fa = create_tree(arr, 12, 0);
	in_order_dfs(fa);
	printf("\n");
	
	dfs_destroy_tree(first);
	return 0;
}
