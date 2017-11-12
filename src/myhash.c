#include "myhash.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

const int maxp = 1000000007;

struct myhash* create_myhash() {
    struct myhash* ret = malloc(sizeof(struct myhash));
    ret->size = 4000000;
    ret->cnt = 0;
    ret->bucket = calloc(1, sizeof(struct hashnode *) * ret->size);
    //memset(ret->bucket, 0, sizeof(struct hashnode *) * 128);
    return ret;
}

int calc_keyhash(char *key) {
    int len = strlen(key);
    int ret = 0;
    for (int i = 0; i < len; i++)
        ret = ret * maxp + key[i];
    return ret;
}

void re_hash(struct myhash* dict) {
    printf("call re_hash here, dict size = %d\n", dict->size);
    struct hashnode** _bucket = calloc(1, sizeof(struct hashnode *) * dict->size * 2);
    //memset(_bucket, 0, sizeof(struct hashnode *) * dict->size * 2);
    if (_bucket != NULL) printf("zmalloc success");
    for (int i = 0; i < dict->size; i++) {
        struct hashnode* item = dict->bucket[i];
        //printf("get bucket[%d]\n", i); 
        while (item != NULL) {
            int index = item->key % (dict->size * 2);
            struct hashnode *next = item->next;
            item->next = _bucket[index];
            _bucket[index] = item;
            item = next;
        }
    }
    free(dict->bucket);
    //printf("zfree success\n");
    dict->bucket = _bucket;
    dict->size *= 2;
}

struct hashnode* get_value(struct myhash* dict, char *key) {
    int hashvalue = calc_keyhash(key);
    int index = (hashvalue % dict->size);
    if (index < 0) index += dict->size;

    //printf("get_value, key=%s\n", key);
    struct hashnode *item = dict->bucket[index];
    while (item != NULL) {
        if (item->key == hashvalue) return item;
        item = item->next;
    }
    return item;
}

void set_value(struct myhash* dict, char *key, int value) {
    int hashvalue = calc_keyhash(key);
    int index = (hashvalue % dict->size);
    if (index < 0) index += dict->size;    

    struct hashnode *item = malloc(sizeof(struct hashnode));
    item->key = hashvalue;
    item->value = value;
    item->next = dict->bucket[index];
    dict->bucket[index] = item;
    dict->cnt ++;
//    if (1.0 * dict->cnt / dict->size > 2) re_hash(dict); 
}


/*
int main() {

    struct myhash* dict = create_myhash();
    set_value(dict, "pancheng", 2);
    struct hashnode* item = get_value(dict, "pancheng");
    printf("%d\n", item->value);
    item->value = 3;
    set_value(dict, "cheng", 23);
    printf("%d\n", get_value(dict, "cheng")->value);
    return 0;
}
*/
