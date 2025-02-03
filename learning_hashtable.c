#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ht_entry
{
	int key;
	char *string_value;
	struct ht_entry *next;
};
struct ht
{
	struct ht_entry *entries;
	size_t capacity;
	size_t length;
};

struct ht *create_table(int cap)
{
	if(!cap)
		return NULL;
	struct ht *table = malloc(sizeof *table);
	if(!table)
		return NULL;

	table->capacity = cap;
	table->length = 0;

	table->entries = calloc(table->capacity, sizeof(struct ht_entry));
	if(!table->entries) 
	{	free(table);
		return NULL;
	}
	table->entries->next = NULL;
	return table;
}
void destory_table(struct ht *table)
{
	struct ht_entry *temp = table->entries;
	while(temp)
	{	free(temp->next);
		temp = temp->next;
	}	

	free(table->entries);
	free(table);
}
int ascii_hash_set(struct ht *table, char *string)
{
	if(table->length == table->capacity)
	{
		fprintf(stderr, "table is at filled\n");
		//auto rehash
		return -1;
	}
	int key = 0;

	for(int i = 0; string[i]; i++)
	{	key += string[i]; //change to = for collision test
	}
	key = key % table->capacity;

	//add into bucket
	if(table->entries[key].string_value)
	{	struct ht_entry *temp = table->entries + key;
		//UNTIL
		for(; temp->next; temp = temp->next);

		temp->next = calloc(1, sizeof(struct ht_entry));
		temp = temp->next;

		temp->key = key;
		temp->string_value = malloc(strlen(string));
		strcpy(temp->string_value, string);
		
		return key;	
	}
	else
	{
	//add if original
	table->entries[key].key = key;
	table->entries[key].string_value = malloc(strlen(string));
	strcpy(table->entries[key].string_value, string);
 
	table->length++;
	return key;	
	}
} 
void print_table(struct ht *table) 
{
	int flag;
	for(int i = 0; i < table->capacity; i++)
	{
		for(struct ht_entry *entry = table->entries + i; entry; entry = entry->next) 
		{	printf(": %s", entry->string_value);
		}	
		printf("\n");
	}
}
//prints the entire chain/bucket
void search_by_key(struct ht *table, int key) 
{
	for(struct ht_entry *temp = table->entries + key; temp; temp = temp->next)
		printf("search: %s\n", temp->string_value);
}
int main(void)
{
	struct ht *table;
	int key;
	int GOTOHASGONE = 0;

label:
	table = create_table(16);
	ascii_hash_set(table, "foo");
	key = ascii_hash_set(table, "bar");
	ascii_hash_set(table, "bash");
	ascii_hash_set(table, "battle");
	ascii_hash_set(table, "hash");
	ascii_hash_set(table, "table");
	ascii_hash_set(table, "hello");
	ascii_hash_set(table, "world");
	print_table(table);
	search_by_key(table, key); 
	destory_table(table);
	if(!GOTOHASGONE)
	{	GOTOHASGONE = 1;
		goto label;	
	}
	if(!table)
		print_table(table); 

	exit(0);
}
