#ifndef _MY_HASH_H_
#define _MY_HASH_H_

struct hashnode {
    int key;
    int value;
    struct hashnode *next;
};

struct myhash {
    int size;
    int cnt;
    struct hashnode **bucket;
};

struct myhash * create_myhash();

struct hashnode* get_value(struct myhash* dict, char *key);
void set_value(struct myhash* dict, char *key, int value);

#endif
