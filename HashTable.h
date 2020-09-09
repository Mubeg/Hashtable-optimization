#include"ionegin"
#include"List.h"


#define HASH_TABLE_INIT(name, ...) hash_table_init((name), #name, ##__VA_ARGS__)
#define table_assert(condition) if(!(condition)){fprintf(stderr, "Assertion failed File %s line %d function %s %s\n", __LOCATION__, #condition); abort();}


const int THE_GREATEST_PRIME_NUMBER = 1303;
const char OTABLE_FILE[] = "ofile.csv";
const char ITABLE_FILE[] = "itext.txt";
const long long int HASH_TABLE_INIT_SIZE = 1303*1303*1303;



struct Hash_table_t {

	const char * name;
	const char * hash_name;

	Canary_t canary1;

	List_t data[THE_GREATEST_PRIME_NUMBER];

	size_t size;

	Canary_t canary2;

};


bool hash_table_init(Hash_table_t *hash_table, const char name[], const size_t init_table_size /*= HASH_TABLE_INIT_SIZE*/);


bool hash_table_put(Hash_table_t *hash_table, Elem_t elem, hash_t hash);


void ready_for_gnu_plot(Hash_table_t *hash_table, FILE * file);


bool hash_table_deinit(Hash_table_t *hash_table);



