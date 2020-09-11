#include"HashTable.h"

int main(){	

	clock_t start = clock();
	
	int buff_size = 0;
	Buff_elem_t *buff = read_file_to_created_buff(ITABLE_FILE, &buff_size);

	change_ch1_to_ch2_and_count_in_ch_buff(' ', '\0', buff, buff_size);

	int text_size = 0;
	str_ptr text = make_text_must_free(buff, buff_size, &text_size);

	Hash_table_t hash_table = {};

	HASH_TABLE_INIT(&hash_table);
	printf("%d\n", text_size);
	for(int _ = 0; _ < 100; _++){
	
		//printf("Cycle#%d\n",_);
		
		for(size_t i = 0; i < text_size; i++){	
			
			hash_t hash = my_hash(text[i].str, sizeof(char)*text[i].size);

			int pos = hash_table_find(&hash_table, text[i].str, hash);
			if (pos < 0){
				pos = hash_table_put(&hash_table, text[i].str, hash);
			}

		}
		for(size_t i = 0; i < text_size; i++){	
			
			hash_t hash = my_hash(text[i].str, sizeof(char)*text[i].size);
			
			int pos = hash_table_find(&hash_table, text[i].str, hash);
			if (pos >= 0){
				if(!hash_table_del(&hash_table, pos, hash)){
					fprintf(stderr, "Error!\n");	
				}
			}

		}
	}

	hash_table_deinit(&hash_table);

	free(text);
	free(buff);
	clock_t end = clock();
	
	double time = double(end - start)/CLOCKS_PER_SEC;
	printf("Programm has been working for %lf seconds.\n", time);

	return 0;	
}


bool hash_table_init(Hash_table_t *hash_table, const char name[]){

	table_assert(hash_table != nullptr);
	if(HASH_TABLE_SIZE < 0){
		return false;	
	}		

	debug_only(hash_table->canary1 = CANARY_VALUE;)
	
	hash_table->size = HASH_TABLE_SIZE;

	for(size_t i = 0; i < hash_table->size; i++){
		LIST_INIT(hash_table->data + i);
	}
	
	
	debug_only(hash_table->name = name[0] == '&' ? name + 1 : name;)

	debug_only(hash_table->canary2 = CANARY_VALUE;)
	
 
	return true;
}


int hash_table_put(Hash_table_t *hash_table, Elem_t elem, hash_t hash){

	table_assert(hash_table != nullptr);

	List_t * list = (hash_table->data + hash % HASH_TABLE_SIZE);
	int pos = -1;
	list->head == 0 ? (list->head = list_add_head(list), pos = list->head, list_set(list, pos, elem)) : pos = list_add_after(list, elem, list->head);
 	
	return pos;
}

int hash_table_find(Hash_table_t *hash_table, Elem_t key, hash_t hash){

	table_assert(hash_table != nullptr);
	
	bool found = false;
	int pos = -1;
	List_t * lst = (hash_table->data + hash % HASH_TABLE_SIZE);
	
	
	for(int i = 0; i < lst->size; i++){

		pos = list_find(lst, i);
		
		if(pos < 0){
			break;
		}

		Elem_t temp = list_get(lst, pos);
		
		if(temp == nullptr){
			continue;	
		}
		if(!strcmp(temp, key)){
			found = true;
			break;	
		}
	}
	return found ? pos : -1;
}

Elem_t hash_table_get(Hash_table_t *hash_table, int pos, hash_t hash){

	table_assert(hash_table != nullptr);
	
	return list_get(hash_table->data + hash%HASH_TABLE_SIZE, pos);
}


bool hash_table_del(Hash_table_t *hash_table, int pos, hash_t hash){

	table_assert(hash_table != nullptr);

	return list_del(hash_table->data + hash%HASH_TABLE_SIZE, pos);
}


bool hash_table_deinit(Hash_table_t *hash_table){

	table_assert(hash_table != nullptr);
	
	for(int i = 0; i < hash_table->size; i++){

		if(!list_deinit(hash_table->data + i)){
			return false;
		}
	}
	return true;
}




