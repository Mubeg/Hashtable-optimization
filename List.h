#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include <locale.h>

#define asserted || (fprintf(stderr, "Asserted from %s on %d in %s\n", __LOCATION__), abort(), false);
#define list_assert(condition) if(!(condition)){fprintf(stderr, "Assertion failed File %s line %d function %s %s\n", __LOCATION__, #condition); abort();}
#undef list_assert
#define debug_only(name) 

#define list_assert(name) 

#define __LOCATION__  __FILE__, __LINE__, __PRETTY_FUNCTION__
#define LIST_INIT(name, ...) list_init((name), #name, ##__VA_ARGS__)

#define PREV(arg) lst->data[(arg)].prev
#define NEXT(arg) lst->data[(arg)].next
#define DATA(arg) lst->data[(arg)].data

//#define TESTING

#ifdef TESTING
#define NDEBUG
#endif
#include <assert.h>


typedef char * Elem_t;
#define ELEM_PRINT "%s" 

typedef long long int Canary_t;
#define CANARY_PRINT "%lX"

typedef unsigned long long int hash_t;
#define HASH_PRINT "%Lu"


struct Cluster_t{

	Elem_t data;
	int next;
	int prev;

};

//#pragma pack(push, 8)
struct List_t {

	hash_t hash; // always comes first
	const char * name;

	debug_only(Canary_t canary1);
	int free;
	int head;

	char * buff;
	debug_only(Canary_t *canary_dynamic1);
	Cluster_t *data;
	debug_only(Canary_t *canary_dynamic2);

	size_t size;
	size_t maxsize;
	debug_only(size_t false_poison);
	debug_only(int errnum);

	debug_only(Canary_t canary2);

};
//#pragma pack(pop)

#pragma pack(push, 1)
struct Torture_t {

	char exec1[1];
	List_t stk;
	char exec2[1];

};
#pragma pack(pop)

const int CHECK_ZERO_ = __LINE__;
const int CHECK_CANARY             = 1 << (__LINE__ - CHECK_ZERO_ - 1); //= 1;
const int CHECK_HASH               = 1 << (__LINE__ - CHECK_ZERO_ - 1); //= 2;
const int CHECK_SIZE               = 1 << (__LINE__ - CHECK_ZERO_ - 1); //= 4;
const int BUFF_NULLPTR             = 1 << (__LINE__ - CHECK_ZERO_ - 1); //= 8;
const int NAME_NULLPTR             = 1 << (__LINE__ - CHECK_ZERO_ - 1); //= 16;
const int CANARY_DYNAMIC1_NULLPTR  = 1 << (__LINE__ - CHECK_ZERO_ - 1); //= 32;
const int CANARY_DYNAMIC2_NULLPTR  = 1 << (__LINE__ - CHECK_ZERO_ - 1); //= 64;
const int DATA_NULLPTR             = 1 << (__LINE__ - CHECK_ZERO_ - 1); //= 128;
const int NEG_SIZE_MAXSIZE         = 1 << (__LINE__ - CHECK_ZERO_ - 1); //= 256;
const int CHECK_DYN_CAN_AND_DATA   = 1 << (__LINE__ - CHECK_ZERO_ - 1); //= 512;
const int NEG_SIZE_FALSE_POISON    = 1 << (__LINE__ - CHECK_ZERO_ - 1); //= 1024;
const int CHECK_NUM_POISON         = 1 << (__LINE__ - CHECK_ZERO_ - 1); //= 2048;
const int MAX_ERROR_NO 		   =      (__LINE__ - CHECK_ZERO_ - 1);


const bool DEBUG = 0;
const Canary_t CANARY_VALUE = 0xBEDAAAAAAAAAAAAA;
const long long int POISON = 'AAATIKIN';
const long long int POISON_POISON = 'AAA23DED';
const int LIST_INIT_SIZE = 5;
const int START_FUNCTION = 1;
const char LIST_LOG_FILE[]   = "list_log.txt";
const char IMAGE_OUT[]  = "Graph.ps";
const int MAX_COMMAND_LEN = 100;
const char OFILE[] = "tempfile";
const int END_FUNCTION = 0;
//const int LIST_CLUSTER_SIZE = sizeof(Elem_t) + 2*sizeof(int);



bool list_init(List_t *lst, const char name[], const size_t init_list_size = LIST_INIT_SIZE);


int list_add_before(List_t *lst, Elem_t elem, int pos);


int list_add_after(List_t *lst, Elem_t elem, int pos);


int list_add_between(List_t *lst, Elem_t elem, int pos_left, int pos_right);


int list_add_head(List_t * lst);


bool list_del(List_t *lst, int pos);


int list_find(List_t *lst, size_t logical_pos, int head = -1);


bool list_deinit(List_t *lst);


Elem_t list_get(List_t *lst, int pos);


bool list_set(List_t *lst, int pos, Elem_t elem);


bool list_resize_if_needed(List_t *lst, bool is_increasing = false);


bool list_shift_unwatched_poison(void * buff, Elem_t poison, size_t size, int shift);


void set_data(List_t * lst);


void set_dynamic_canaries(List_t * lst);


bool fill_data_with_poison(void * data, const size_t size, long long int poison, const size_t Elem_size);


void * recalloc_safe(void * const data, const long long int prev_num, const long long int num, const size_t size);


void zero_data(void * const data, const int start, const int end);


bool check_list(List_t *lst, const char called_from_file[], int line, const char func[], bool print_all = true);


void list_dump(List_t * const lst, const char called_from_file[], int line, const char func[], bool ok, time_t curtime = -1);


void dot_list(List_t * lst, const char ofile[]);


bool check_maxsize(List_t * const stk);


bool check_number_of_poison(List_t * const stk);


bool is_poison(Elem_t elem, long long int poison, const size_t Elem_size);


bool check_nullptr(const void * const stk);


bool check_canary(List_t * const stk);


bool check_size_not_neg(size_t const stk);


bool check_hash(List_t * const stk);


bool check_hashable(List_t * const stk);


bool check_dynamic_canaries_and_data(List_t * const stk);


bool is_equal_hash_t(const hash_t left, const hash_t right);


hash_t find_sum_hash(List_t * const stk, size_t size);


hash_t my_hash(const void * const stk, size_t size);


bool check_size(List_t * const stk);








bool list_init(List_t *lst, const char name[], const size_t init_list_size /*= LIST_INIT_SIZE*/){

	list_assert(check_nullptr(lst));
	if(init_list_size < 0){
		return false;	
	}

	debug_only(lst->canary1 = CANARY_VALUE);
	
	lst->maxsize = init_list_size;

	lst->buff = (char *) calloc(lst->maxsize*sizeof(Cluster_t) debug_only(+ 2*sizeof(Canary_t)), sizeof(char));
	if(lst->buff == nullptr){
		return false;
	}
	
	debug_only(set_dynamic_canaries(lst));
	set_data(lst);

	for(int i = 0; i < lst->maxsize; i++){	

		debug_only(fill_data_with_poison(&DATA(i), 1, i == 0 ? POISON_POISON : POISON, sizeof(Elem_t)));
		fill_data_with_poison(&NEXT(i), 1,  0, sizeof(int));
		fill_data_with_poison(&PREV(i), 1, -1, sizeof(int));
	}
	
	debug_only(lst->false_poison = 0);

	lst->head = 0;
	lst->free = 1;
	for(int i = 1; i < lst->maxsize - 1; i++){ //next[last] = 0
		NEXT(i) = i + 1;
	}

	lst->size = 1; // data[0] - protected
	debug_only(lst->errnum = 0);

	lst->name = name[0] == '&' ? name + 1 : name;

	debug_only(lst->canary2 = CANARY_VALUE);

	debug_only(lst->hash = find_sum_hash(lst, sizeof(List_t)));

	list_assert(check_list(lst, __LOCATION__));
 
	return true;
}

int list_add_before(List_t *lst, Elem_t elem, int pos){

	list_assert(check_list(lst, __LOCATION__));
	
	int new_pos = list_add_between(lst, elem, PREV(pos), pos);
	
	list_assert(check_list(lst, __LOCATION__));

	return new_pos;
}

int list_add_after(List_t *lst, Elem_t elem, int pos){

	list_assert(check_list(lst, __LOCATION__));
	
	int new_pos = list_add_between(lst, elem, pos, NEXT(pos));
	
	list_assert(check_list(lst, __LOCATION__));

	return new_pos;
}

int list_add_between(List_t *lst, Elem_t elem, int pos_left, int pos_right){

	list_assert(check_list(lst, __LOCATION__));
	
	if(!list_resize_if_needed(lst, /*is_increasing = true*/ true)){
		list_assert(check_list(lst, __LOCATION__));
		return -1;
	}

	debug_only(if(is_poison(elem, POISON, sizeof(Elem_t))){
		lst->false_poison++;
	})

	int new_pos = lst->free;
	DATA(new_pos) = elem;
	lst->free = NEXT(new_pos);

	NEXT(new_pos)                    = pos_right;
	PREV(new_pos)                    = pos_left == 0 ? lst->head : pos_left;
	pos_left  == 0 ? lst->head       = new_pos : NEXT(pos_left) = new_pos;
	pos_right != 0 ? PREV(pos_right) = new_pos : 0;
	
	lst->size++;
	
	debug_only(lst->hash = find_sum_hash(lst, sizeof(List_t)));
	
	list_assert(check_list(lst, __LOCATION__));

	return new_pos;
}

int list_add_head(List_t * lst){
	
	list_assert(check_list(lst, __LOCATION__));
	
	int head = lst->free;
	lst->free = NEXT(lst->free);
	PREV(head) = 0;
	NEXT(head) = 0;

	debug_only(lst->hash = find_sum_hash(lst, sizeof(List_t)));

	list_assert(check_list(lst, __LOCATION__));

	return head;
}

bool list_del(List_t *lst, int pos){

	list_assert(check_list(lst, __LOCATION__));
	list_assert(pos >= 0);


	debug_only(if(is_poison(DATA(pos), POISON, sizeof(Elem_t))){
		lst->false_poison--;
	})

	PREV(pos) == 0 ? lst->head = NEXT(pos) : NEXT(PREV(pos)) = NEXT(pos);
	PREV(NEXT(pos)) = PREV(pos);

	NEXT(pos) = lst->free;
	PREV(pos) = -1;
	lst->free = pos;
	debug_only(fill_data_with_poison(&DATA(pos), 1, POISON, sizeof(Elem_t)));

	lst->size--;

	debug_only(lst->hash = find_sum_hash(lst, sizeof(List_t)));

	list_assert(check_list(lst, __LOCATION__));

	return true;
}

int list_find(List_t *lst, size_t logical_pos, int head /*= -1*/){
	
	list_assert(lst != nullptr);
	list_assert(logical_pos >= 0);	
	list_assert(check_list(lst, __LOCATION__));
	
	int counter = 0;
	int pos = -1;

	if(head == -1){
		head = lst->head;
	}
	
	for(pos = head; counter < logical_pos; counter++, pos = NEXT(pos));

	list_assert(check_list(lst, __LOCATION__));

	return pos;
}

bool list_deinit(List_t *lst){

	list_assert(check_list(lst, __LOCATION__));
	
	if(lst->buff == nullptr) return false;	

	zero_data(lst->buff, 0, lst->maxsize*sizeof(Cluster_t) debug_only(+ 2*sizeof(Canary_t)));
	free(lst->buff);

	return true;
}


Elem_t list_get(List_t *lst, int pos){

	list_assert(check_list(lst, __LOCATION__));
	list_assert(pos >= 0);
	
	return DATA(pos);
}


bool list_set(List_t *lst, int pos, Elem_t elem){

	list_assert(check_list(lst, __LOCATION__));
	list_assert(pos >= 0);
	
	debug_only(if(is_poison(elem, POISON, sizeof(Elem_t))){
		lst->false_poison++;
	})
	DATA(pos) = elem;
	lst->size++;

	debug_only(lst->hash = find_sum_hash(lst, sizeof(List_t)));

	list_assert(check_list(lst, __LOCATION__));

	return true;
}


bool list_resize_if_needed(List_t *lst, bool is_increasing/* = false*/){

	list_assert(check_list(lst, __LOCATION__));
	
	if(is_increasing && (lst->size == lst->maxsize)){


		void * temp = recalloc_safe(lst->buff, lst->maxsize*sizeof(Cluster_t) debug_only(+ 2*sizeof(Canary_t)), 
				       lst->maxsize*2*sizeof(Cluster_t) debug_only(+ sizeof(Canary_t)*2), sizeof(char));
		
		if(temp == nullptr){
			return false;		
		}

		lst->buff = (char *)temp;
		set_data(lst);
		lst->maxsize *= 2;
		debug_only(set_dynamic_canaries(lst));

		for(int i = lst->maxsize/2; i < lst->maxsize; i++){

			debug_only(fill_data_with_poison(&DATA(i), 1, POISON, sizeof(Elem_t)));
			fill_data_with_poison(&NEXT(i), 1,  0, sizeof(int));
			fill_data_with_poison(&PREV(i), 1, -1, sizeof(int));
		}

		lst->free = lst->maxsize/2;
		for(int i = lst->free; i < lst->maxsize - 1; i++){ //next[last] = 0
			NEXT(i) = i + 1;
		}

		debug_only(lst->hash = find_sum_hash(lst, sizeof(List_t)));

	}
	/*if(!is_increasing && stk->size < stk->maxsize/4){

		void * temp = recalloc_safe(stk->buff, stk->maxsize*sizeof(Elem_t) + sizeof(Canary_t), 
				       stk->maxsize*sizeof(Elem_t)/2 + sizeof(Canary_t)*2, sizeof(char));
		if(temp == nullptr){
			fprintf(stderr, "realloc problem while making smaller ????\n");
			return false;
		}
		if(temp != stk->buff){
			fprintf(stderr, "WOW, realloc tryies to move data!\n!\n!\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		}
		
		stk->buff = (char *)temp;
		stk->maxsize /= 2;
		set_dynamic_canaries_and_data(stk);

		stk->hash = find_sum_hash(stk, sizeof(Stack_t));
	}*/
	

	list_assert(check_list(lst, __LOCATION__));

	return true;
}

void set_data(List_t * lst){

	if(lst == nullptr) return;

	lst->data = (Cluster_t *)(lst->buff debug_only(+ sizeof(Canary_t)));

}

debug_only(void set_dynamic_canaries(List_t * lst){

	if(lst == nullptr) return;

	lst->canary_dynamic1 = (Canary_t *) lst->buff;
	lst->canary_dynamic1[0] = CANARY_VALUE;

	lst->canary_dynamic2 = (Canary_t *)(lst->buff + sizeof(Canary_t) + lst->maxsize*sizeof(Cluster_t));
	lst->canary_dynamic2[0] = CANARY_VALUE;

})

bool fill_data_with_poison(void * data, const size_t size, long long int poison, const size_t Elem_size){
	
	list_assert(data != nullptr);
	if(size < 0) return false;

	//printf("data[%p]: posison: %d, size %d, Elem_size %d\n", data, poison, size, Elem_size);

	for(unsigned int i = 0; i < size * Elem_size; i++){
		((char *)data)[i] = ((char *) &poison)[i % Elem_size];
	}

	return true;

}

void * recalloc_safe(void * const data, const long long int prev_num, const long long int num, const size_t size){
	
	list_assert(data != nullptr);
		
	if(data == nullptr) return nullptr;

	if(prev_num >= num){

		zero_data(data, num*size, prev_num*size);
		return realloc(data, num*size);
	}
	
	if(sizeof(char) != 1){
		list_assert('0xBEDA' != '0xBEDA');
	}
	
	char * new_data = (char *) calloc(num, size);
	if(new_data == nullptr){
		return nullptr;
	}

	for(int i = 0; i < prev_num*size; i++){
		new_data[i] = ((char *) data)[i];
	}

	zero_data(data, 0, prev_num*size);


	free(data);
	return (void *) new_data;
}

void zero_data(void * const data, const int start, const int end){

	list_assert(data != nullptr);
	list_assert(start < end);	

	for(int i = start; i < end; i++){
		((char *) data)[i] = '\0';
	}

}

debug_only(bool check_list(List_t *lst, const char called_from_file[], int line, const char func[], bool print_all/* = true*/){


	bool passed = true;
	bool hashable = true;

	if(!check_nullptr((void *) lst)){
		return false;
	}

	if(lst->errnum != 0){
		return false;	
	}

// A Lot of checks below
	if(DEBUG) printf("Passed: %d\n", passed);

	passed = check_canary(lst)                     ? passed : (lst->errnum += CHECK_CANARY, false);
	if(DEBUG) printf("Passed: %d\n", passed);

	passed = check_hash(lst)		       ? passed : (lst->errnum += CHECK_HASH, false);
	if(DEBUG) printf("Passed: %d\n", passed);

	passed = check_size(lst)                       ? passed : (lst->errnum += CHECK_SIZE, false);
	if(DEBUG) printf("Passed: %d\n", passed);


	passed = check_nullptr(lst->buff)              ? passed : (lst->errnum += BUFF_NULLPTR, false);
	if(DEBUG) printf("Passed: %d\n", passed);
 
	passed = check_nullptr(lst->name)              ? passed : (lst->errnum += NAME_NULLPTR, false);
	if(DEBUG) printf("Passed: %d\n", passed);

	passed = check_nullptr(lst->canary_dynamic1)   ? passed : (lst->errnum += CANARY_DYNAMIC1_NULLPTR, false);
	if(DEBUG) printf("Passed: %d\n", passed);

	passed = check_nullptr(lst->canary_dynamic2)   ? passed : (lst->errnum += CANARY_DYNAMIC2_NULLPTR, false);
	if(DEBUG) printf("Passed: %d\n", passed);

	passed = check_nullptr(lst->data)              ? passed : (lst->errnum += DATA_NULLPTR, false);
	if(DEBUG) printf("Passed: %d\n", passed);


	passed = check_maxsize(lst)	               ? passed : (lst->errnum += NEG_SIZE_MAXSIZE, false);
	if(DEBUG) printf("Passed: %d\n", passed);

	passed = check_dynamic_canaries_and_data(lst)  ? passed : (lst->errnum += CHECK_DYN_CAN_AND_DATA, false);
	if(DEBUG) printf("Passed: %d\n", passed);

	passed = check_size_not_neg(lst->false_poison) ? passed : (lst->errnum += NEG_SIZE_FALSE_POISON, false);
	if(DEBUG) printf("Passed: %d\n", passed);
	
	passed = check_number_of_poison(lst)	       ? passed : (lst->errnum += CHECK_NUM_POISON, false);
	if(DEBUG) printf("Passed: %d\n", passed);

/*	passed = check_canary(lst)? passed : (lst->errnum = 1, false);
	passed = check_canary(lst)? passed : (lst->errnum = 1, false);
	passed = check_canary(lst)? passed : (lst->errnum = 1, false);
	passed = check_canary(lst)? passed : (lst->errnum = 1, false);
	passed = check_canary(lst)? passed : (lst->errnum = 1, false);
	passed = check_canary(lst)? passed : (lst->errnum = 1, false);*/

	if(DEBUG) printf("\n");

// End of a Lot of checks
		
	if(print_all || !passed){
		list_dump(lst, called_from_file, line, func, passed);
	}

	return passed;
})


debug_only(void list_dump(List_t * const lst, const char called_from_file[], int line, const char func[], bool ok, time_t curtime /* = -1*/){

	if(lst == nullptr) return;

	if(curtime == -1){
		time(&curtime);	
	}

	FILE *log_file = fopen(LIST_LOG_FILE, "a");
	if(log_file == nullptr){
		fprintf(stderr, "Not able to open %s in %s line %d in %s\n", LIST_LOG_FILE, __LOCATION__);
	}


	fprintf(log_file, "\nTime and date: %s\n"
			  "Dumping list from file %s, line %d, function %s [%s]\n"
			  "List [%p] %s {\n"
			  "\n\t\t hash    = " HASH_PRINT "\n"
			  "\n\t\t canary1 = " CANARY_PRINT "\n"
			  "\t\t free    = %d\n"
			  "\t\t head    = %d\n"
			  "\t\t size    = %d\n"
			  "\t\t maxsize = %d\n"
			  "\n\t\t buff = [%p]\n"
			  "\t\t canary_dynamic1 [%p] = " CANARY_PRINT "\n"
			  "\t\t data = [%p]{\n", 
		ctime(&curtime),
		called_from_file, line, func, ok ? "ok" : "ERROR!!!",
		lst, lst->name,
		lst->hash,
		lst->canary1,
		lst->free,
		lst->head,
		lst->size, 
		lst->maxsize,
		lst->buff, 
		lst->canary_dynamic1, lst->canary_dynamic1 == nullptr ? 'NULLPTR' : lst->canary_dynamic1[0],
		lst->data);
	fflush(log_file);
	
	if(lst->data != nullptr){
		if(check_maxsize(lst))
			for(int i = 0; i < lst->maxsize; i++){

				fprintf(log_file, "\t\t\t Cluster_t [%d]{\n"
						  "\t\t\t\t data = %d %s\n"
						  "\t\t\t\t next = %d\n"
						  "\t\t\t\t prev = %d\n", i, DATA(i), is_poison(DATA(i), POISON, sizeof(Elem_t)) ? "POISON?" : "", 
									NEXT(i), PREV(i));
			}
	}
	fprintf(log_file, "\t\t }\n");
	fflush(log_file);
	
	fprintf(log_file, "\t\t canary_dynamic2 [%p] = " CANARY_PRINT "\n",  
		lst->canary_dynamic2, lst->canary_dynamic2 == nullptr ? 'NULLPTR' : lst->canary_dynamic2[0]);

	fprintf(log_file, "\n\t\t errnum   = ");
	for(int i = 0; i < MAX_ERROR_NO; i++){
		fprintf(log_file, "%d", (lst->errnum >> i) % 2);
	}
	fprintf(log_file, "\n");
	fflush(log_file); 

	fprintf(log_file, "\n\t\t canary2 = " CANARY_PRINT "\n\n\t}\n\n",
		lst->canary2);

	fflush(log_file);
	/*

	Time and date: ....
	Dumping stack from file main.cpp, line 123, function check() [ok] ([ERROR!!!])
	Stack [0x1124asda] lst1 {
	
		Canary_t canary1 = ...	

		hash_t hash    = ....
		size_t size    = ....
		size_t maxsize = ....

		char * buff = [0x231141]
		Canary_t * canary_dynamic1 [0x1425123] = ...
		Elem_t *data = [0x23123]{
			* data[0] = ..
			  data[1] = ...  POISON?
			....
		}
		Canary_t * canary_dynamic2 [0x2131331] = ... 

		int errnum      = ...

		Canary_t canary2 = ...
	
	}

	*/

	fclose(log_file);

})

void dot_list(List_t * lst, const char ofile[]){

	list_assert(check_list(lst, __LOCATION__));

	FILE *file = fopen(ofile, "w");
	fprintf(file, "digraph %s{\n", lst->name);

	for(int i = 0; i < lst->maxsize; i++){
	
		char color[MAX_COMMAND_LEN] = {};
		sprintf(color, "color = \"%s\"", i == 0 ? "orange" : (NEXT(i) == 0 ? "red" : (PREV(i) == -1 ? "blue" : "green")));
		fprintf(file, "%d [%s; shape = record; label =\"{index | value} | {%d|" ELEM_PRINT "}\"]\n", i, color, i, DATA(i));
	}
	
	fprintf(file, "free -> %d\n", lst->free, DATA(lst->free));
	fprintf(file, "head -> %d\n", lst->head, DATA(lst->head));
	
	for(int i = 0; i < lst->maxsize; i++){


		if(i == 0){
			fprintf(file, "%d -> %d\n", i, i);
		}
		if(NEXT(i) != 0){
			fprintf(file, "%d -> %d\n", i, NEXT(i));
		}
		if(PREV(i) > 0){
			fprintf(file, "%d -> %d\n", i, PREV(i));
		}
	}
	fprintf(file, "}\n");

	fclose(file);
	
	char command[MAX_COMMAND_LEN];

	sprintf(command, "dot -Tps %s -o %s\n", ofile, IMAGE_OUT);
	std::system(command);

	sprintf(command, "rm %s\n", ofile);
	std::system(command);
	
}

debug_only(bool check_maxsize(List_t * const lst){
	
	if(lst == nullptr) return false;

	return lst->maxsize == ((Cluster_t *)lst->canary_dynamic2) - lst->data; 

})

debug_only(bool check_number_of_poison(List_t * const lst){

	if(!check_hashable(lst)) return false;

	size_t counter = 0;

	if(lst->data == nullptr){
		return false;	
	}

	//list_dump(lst, __LOCATION__, false);
	
	for(size_t i = 0; i < lst->maxsize; i++){

		//printf("[%04d]: %d\n", i, lst->data[i]);
		counter += is_poison(DATA(i), POISON, sizeof(Elem_t)) ? 1 : 0;
	}

	//printf("%d %d %d %d \n", counter, lst->false_poison, lst->maxsize, lst->size);
	
	return counter - lst->false_poison == lst->maxsize - lst->size;
})

debug_only(bool is_poison(Elem_t elem, long long int poison, const size_t Elem_size){

	for(unsigned int i = 0; i < Elem_size; i++){
		if(((char *) &elem)[i] != ((char *) &poison)[i]){
			return false;
		}
	}

	return true;

})

bool check_nullptr(const void * const lst){
	
	if(lst == nullptr){
		return false;
	}
	
	return true;
}

debug_only(bool check_canary(List_t * const lst){

	if(lst == nullptr) return false;
	return lst->canary1 == lst->canary2 && lst->canary2 == CANARY_VALUE;
})

bool check_size_not_neg(const size_t size){

	return size >= 0;
}

debug_only(bool check_hash(List_t * const lst){

	if(!check_hashable(lst)) return false;
	return is_equal_hash_t(find_sum_hash(lst, sizeof(List_t)), lst->hash);
})

debug_only(bool check_hashable(List_t * const lst){
	
	return check_size(lst) && check_maxsize(lst) && check_size_not_neg(lst->false_poison);
})

debug_only(bool check_dynamic_canaries_and_data(List_t * const lst){

	if(lst == nullptr) return false;
	if(lst->canary_dynamic1 == lst->canary_dynamic2) return false;
	if(lst->canary_dynamic1 == nullptr) return false;

	return !((char *)(lst->canary_dynamic2) - (char *)(lst->canary_dynamic1) != sizeof(Canary_t) + lst->maxsize*sizeof(Cluster_t) 
		|| (char *)lst->data - (char *)lst->canary_dynamic1 != sizeof(Canary_t) 
		|| lst->canary_dynamic2[0] != lst->canary_dynamic1[0] 
		|| lst->canary_dynamic2[0] != CANARY_VALUE);

})

bool is_equal_hash_t(const hash_t left, const hash_t right){
	
	return left == right;
}

debug_only(hash_t find_sum_hash(List_t * const lst, size_t size){

	if(lst == nullptr) return false;

	hash_t hash_sum = 0;
	
	hash_sum += my_hash(lst + sizeof(hash_t), size - sizeof(hash_t));
	hash_sum += my_hash(lst->buff, lst->buff == nullptr ? 0 : sizeof(lst->canary_dynamic1) + sizeof(lst->canary_dynamic2)
							       + sizeof(Cluster_t)*lst->maxsize);
	hash_sum += my_hash(lst->name, lst->name == nullptr ? 0 : strlen(lst->name));

	return hash_sum;

})

/*hash_t my_hash(const void * const data, size_t size){

	if(data == nullptr) return false;

	hash_t hash_sum = 0;

	for(size_t counter = 0; counter < size; counter++){

		hash_sum = (hash_sum << 2) + (counter+1)*((*((char *) data + counter))^0xfc);
	}

	return hash_sum;

}*/

bool check_size(List_t * const lst){
	
	if(lst == nullptr) return false;

	if(lst->size < 0 || lst->size > lst->maxsize){
		return false;
	}

	return true;

}



