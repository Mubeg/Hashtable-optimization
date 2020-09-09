//DEF_HASH(num, name, hash_code /*hash = ...*/)

#define WORD text[i].str
#define LEN text[i].size
#define ROL(hash) ((hash >> (sizeof(hash)*8 - 1)) | (hash << 1))

DEF_HASH(1, sillyHash, hash = 1;)

DEF_HASH(2, FirstLetter, hash = (int)WORD[0];)

DEF_HASH(3, WordLen, hash = strlen(WORD);)

DEF_HASH(4, LetterSum, for(int j = 0; j < LEN; j++){hash += (int) WORD[j];})

DEF_HASH(5, Rolleft, for(int j = 0; j < LEN; j++){hash = (hash_t) ROL(hash) ^ WORD[j];})

DEF_HASH(6, MyHash, hash = my_hash(WORD, sizeof(char)*LEN);)

DEF_HASH(100, end, do_break = true;)

#undef WORD
#undef LEN
#undef ROL
