#include "stdio.h"
#include "count.h"
#include "stdlib.h" //needed to use malloc
#include "string.h"
#include "ctype.h"

typedef struct HashTable_ HashTable;

typedef struct Node_ Node;

int hashCode(unsigned long long size, unsigned long long value){
	//printf("%llu\n", value % size);
	return value % size;
}

void insert(HashTable **table, unsigned long long value, int total){
	
	unsigned long long key = (unsigned long long) hashCode(total, value);
	//printf("%llu\n", key);
	if((*table)->visited[key] == 0){
		//printf("%ld\n", key);
		(*table)->visited[key] = 1;
		(*table)->addresses[key].value = value;
		(*table)->addresses[key].next = NULL;
		(*table)->size++;
	}
	else{
		Node *ptr = &(*table)->addresses[key];
		Node *prev = NULL;
		while(ptr != NULL){
			if(ptr->value == value){
				return;
			}
			prev = ptr;
			ptr = ptr->next;
		}
		Node *new = (Node *) malloc(sizeof(Node));
		new->next = NULL;
		new->value = value;
		prev->next = new;
		(*table)->size++;
	}
	(*table)->loadFactor = (double) (*table)->size / (*table)->total;
	if((*table)->loadFactor > 0.5){
		//printf("Old lf: %lf\t", table->loadFactor);
		//printf("size: %li\t total: %i\t lf: %lf\t", table->size, table->total, table->loadFactor);
		rehash(table, total);
		//printf("Load factor: %lf\t Size: %d\n", table->loadFactor, table->total);
	}
}

HashTable* create(int size){
	HashTable *table = (HashTable *)malloc(sizeof(HashTable));
	table->addresses = (Node *)malloc(sizeof(Node) * size);
	table->visited = (int *)malloc(sizeof(Node) * size);
	table->total = size;
	table->size = 0;
	table->loadFactor = 0;
	return table;
}

int search(HashTable *table, unsigned long long value){
	//Node *ptr = &table->addresses[key];
	//while(ptr != 
	return 0;
}

void rehash(HashTable **table, int total){
	HashTable *oldTable = *table;
	int oldLength = total;
	int newLength = total * 2;
	HashTable *newTable = create(newLength);
	int i;
	for(i = 0; i < oldLength; i++){
		
		if(oldTable->visited[i] != 0){
			Node *ptr = &oldTable->addresses[i];
			while(ptr != NULL){
				insert(&newTable, ptr->value, newLength);
				
				//printf("size: %li\t total: %i\tlf: %lf\n", newTable->size, newTable->total, newTable->loadFactor);
				ptr = ptr->next;
				
			}
		}
		
	}
	for(i = 0; i < oldLength; i++){
		if(oldTable->visited[i] != 0){
			Node *ptr = oldTable->addresses[i].next;
			while(ptr != NULL){
				Node *temp = ptr;
				ptr = ptr->next;
				free(temp);
			}
			
		}
	}
	//newTable->loadFactor = (double) newTable->size / newLength;
	//printf("newtable: %lf\t", newTable->loadFactor);
	*table = newTable;
	//printf("size: %li\t total: %i\t lf: %lf\t", (*table)->size, (*table)->total, (*table)->loadFactor);
	free(oldTable->addresses);
	free(oldTable->visited);
	free(oldTable);
}

int main(int argc, char **argv){
	FILE *file = fopen(argv[1], "r");
	//if file does not exist
	if(!file){
		printf("error");
		return 0;
	}
	char buffer[1000];
	HashTable *table = create(1000);
	if(fgets(buffer, 1000, file) == NULL){
		printf("%i",0);
		return 0;
	}
	
	rewind(file);
	
	while(fgets(buffer, 1000, file) != NULL){
   		char address[1000];
		strcpy(address, &buffer[0]);
		//test cases, if buffer[1] has an actual character (no, we can assume that each line will have only one address)
		//test cases, if address is not a proper hexadecimal
		//test cases, ones from fourth.c and third.c
		int i;
		int malInput = 0;
		
		if((strlen(address) - 1) < 3){
			continue;
		}
		for(i = 0; i < strlen(address) - 1; i++){
			if(i == 0 && address[0] != '0'){
				malInput = 1;
				//printf("hi1");
				break;
			}
			else if(i == 1 && address[1] != 'x'&& address[1] != 'X'){
				malInput = 1;
				//printf("hi2");
				break;
			}
			else if(i > 1 && isxdigit(address[i]) == 0){
				malInput = 1;
				//printf("hi3");
				break;
			}
		}
		if(malInput){
			continue;
		}
		else if(strlen(address) - 1 > 18){
			continue;
			
		}
		//printf("%i\n", strlen(address)-1);
		unsigned long long num = strtoull(address, NULL, 16);
		//printf("%llu\n", num);
		insert(&table, num, table->total);
		
	}
	printf("%i", table->size);	
	//printf("%i", table->total);
	fclose(file);
	int i;
	for(i = 0; i < table->total; i++){
		if(table->visited[i] != 0){
			Node *ptr = table->addresses[i].next;
			while(ptr != NULL){
				Node *temp = ptr;
				ptr = ptr->next;
				free(temp);
			}
			
		}
	}
	free(table->addresses);
	free(table->visited);
	free(table);
	return 0;
}
