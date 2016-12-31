#ifndef COUNT_H
#define COUNT_H

struct Node_{
	unsigned long long value;
	struct Node_ *next;
};

struct HashTable_{
	int size;
	int total;
	double loadFactor;
	int *visited;
	struct Node_ *addresses;
};

int hashCode(unsigned long long size, unsigned long long value);

void insert(struct HashTable_ **table, unsigned long long value, int total);

struct HashTable_ *create(int size);

int search(struct HashTable_ *table, unsigned long long value);

void rehash(struct HashTable_ **table, int total);

#endif
