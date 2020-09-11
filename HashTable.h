#include"ionegin"
#include"List.h"
#include <time.h>


#define HASH_TABLE_INIT(name, ...) hash_table_init((name), #name, ##__VA_ARGS__)
#define table_assert(condition) if(!(condition)){fprintf(stderr, "Assertion failed File %s line %d function %s %s\n", __LOCATION__, #condition); abort();}


const int THE_GREATEST_PRIME_NUMBER = 1303;
const char ITABLE_FILE[] = "itext.txt";
const long long int HASH_TABLE_SIZE = 115249; //no_more
const char HASH_TABLE_LOG_FILE[]   = "hash_table_log.txt";



struct Hash_table_t {

	const char * name;
	const char * hash_name;

	debug_only(Canary_t canary1;)

	List_t data[HASH_TABLE_SIZE];

	size_t size;

	debug_only(Canary_t canary2;)

};


bool hash_table_init(Hash_table_t *hash_table, const char name[]);


int  hash_table_put(Hash_table_t *hash_table, Elem_t elem, hash_t hash);


int hash_table_find(Hash_table_t *hash_table, Elem_t elem, hash_t hash);


Elem_t hash_table_get(Hash_table_t *hash_table, int pos, hash_t hash);


bool hash_table_del(Hash_table_t *hash_table, int pos, hash_t hash);


bool hash_table_deinit(Hash_table_t *hash_table);



