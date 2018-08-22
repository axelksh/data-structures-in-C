#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

struct entry_s
{
	char *key;
	char *value;
	struct entry_s *next;
};

typedef struct entry_s entry_t;

struct hash_table_s
{
	int size;
	struct entry_s **table;
};

typedef struct hash_table_s hash_table_t;

/*
	Create a hash table
*/
hash_table_t *create_hash_table(int size)
{
	hash_table_t *hashtable = NULL;

	if (size < 1) return NULL;

	if ( (hashtable = malloc(sizeof(hash_table_t))) == NULL )
	{
		return NULL;
	}

	if ( (hashtable->table = malloc(sizeof(entry_t *) * size)) == NULL )
	{
		return NULL;
	}

	for (int i = 0; i < size; ++i)
	{
		hashtable->table[i] = NULL;
	}

	hashtable->size = size;

	return hashtable;
}

/*
	Hash a string for a particular hash table.
*/
int hash(hash_table_t *hashtable, char *key)
{
	unsigned long int hashval;
	int i = 0;

	while(hashval < ULONG_MAX && i < strlen(key))
	{
		hashval = hashval << 8;
		hashval += key[i];
		i++;
	}

	return hashval % hashtable->size;
}

/*
	Create a key-value pair. 
*/
entry_t *ht_new_pair(char *key, char *value)
{
	entry_t *newpair;

	if ( (newpair = malloc(sizeof(entry_t))) == NULL )
	{
		return NULL;
	}

	if ( (newpair->key = strdup(key)) == NULL )
	{
		return NULL;
	}

	if ( (newpair->value = strdup(value)) == NULL )
	{
		return NULL;
	}

	newpair->next = NULL;

	return newpair;
}

/*
	Insert a key-value pair into a hash table.
*/
void ht_set(hash_table_t *hashtable, char *key, char *value)
{
	int bin = 0;
	entry_t *newpair = NULL;
	entry_t *next = NULL;
	entry_t *last = NULL;

	bin = hash(hashtable, key);

	next = hashtable->table[bin];

	while(next != NULL && next->key != NULL && strcmp(key, next->key) > 0)
	{
		last = next;
		next = next->next;
	}

	if (next != NULL && next->key != NULL && strcmp(key, next->key) == 0)
	{
		free(next->value);
		next->value =  strdup(value);
	}
	else
	{
		newpair = ht_new_pair(key, value);

		if (next == hashtable->table[bin])
		{
			newpair->next = next;
			hashtable->table[bin] = newpair;
		}
		else if (next == NULL)
		{
			last->next = newpair;
		}
		else
		{
			newpair->next = NULL;
			last->next = newpair;
		}
	}
}

/*
	Retrieve a key-value pair from a hash table.
*/
char *ht_get(hash_table_t *hashtable, char *key)
{
	int bin = hash(hashtable, key);
	entry_t *pair = hashtable->table[bin];

	while(pair != NULL && pair->key != NULL && strcmp(key, pair->key) > 0)
	{
		pair = pair->next;
	}

	if (pair == NULL || pair->key == NULL || strcmp(key, pair->key) != 0)
	{
		return NULL;
	}
	else
	{
		return pair->value;
	}
}

int main()
{
	hash_table_t *hashtable = create_hash_table(3);
	
	ht_set(hashtable, "English", "Hello");
	ht_set(hashtable, "France", "Bonjour");
	ht_set(hashtable, "Germany", "Guten tag");

	printf("%s\n", ht_get(hashtable, "English"));
	printf("%s\n", ht_get(hashtable, "France"));
	printf("%s\n", ht_get(hashtable, "Germany"));

	return 0;
}

