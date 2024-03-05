// Group Number : 22
// ID : 2020B3A70838P		Name : AYUSH GUPTA
// ID : 2020B3A71425P 		Name : BHAVISHYA GARG
// ID : 2020B3A70880P		Name : KARTIK DANG
// ID : 2020B3A70841P		Name : MAYANK VERMA
// ID : 2020B3A70784P		Name : RAHUL GINODIA
// ID : 2020B4A70836P		Name : SRIJAN KHATRI

#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#ifndef hashmap_int
#define hashmap_int

static unsigned long hash_functionI(unsigned long x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

typedef struct HMIValues {
    int key;
    void* value;
} HMIValues;

typedef struct LinkedListI{
    HMIValues* val;
    struct LinkedListI* next;
} LinkedListI;

typedef struct HashMapI{
    HMIValues** vals;
    LinkedListI** collision_buckets;
    int count;
    int size;
} HashMapI;

static LinkedListI* allocate_listI() {
    LinkedListI* newList = (LinkedListI*) malloc(sizeof(LinkedListI));
    return newList;
}

static LinkedListI* list_insertI(LinkedListI* list, HMIValues* val) {
    if(!list) {
        LinkedListI* head = allocate_listI();
        head->val = val;
        head->next = NULL;
        list = head;
        return list;
    }
    else if(list->next == NULL){
        LinkedListI* node = allocate_listI();
        node->val = val;
        node->next = NULL;
        list->next = node;
        return list;
    }

    LinkedListI* temp = list;

    while(temp->next->next) temp = temp->next;
    LinkedListI* node = allocate_listI();
    node->val = val;
    node->next = NULL;
    temp->next = node;
    return list;
}

static LinkedListI** create_collision_bucketsI(HashMapI* hm) {
    LinkedListI** collision_buckets = (LinkedListI**) calloc(hm->size, sizeof(LinkedListI*));
    for(int i = 0;i<hm->size;i++) collision_buckets[i] = NULL;
    return collision_buckets;
}

static HMIValues* create_valueI(int key, void* val) {
    HMIValues* newVal = (HMIValues*) malloc(sizeof(HMIValues));
    // printf("%d\t%s\n", strl(key) key);
    newVal->key = key;
    newVal->value = val;
    return newVal;
}

static HashMapI* create_tableI(int size){
    HashMapI* newHM = (HashMapI*) malloc(sizeof(HashMapI));
    newHM->size = size;
    newHM->count = 0;
    newHM->vals = (HMIValues**) calloc(newHM->size, sizeof(HMIValues*));
    for(int i = 0;i<newHM->size;i++) {
        newHM->vals[i] = NULL;
    } 
    newHM->collision_buckets = create_collision_bucketsI(newHM);
    return newHM;
}

static void handle_collisionI(HashMapI* hm, unsigned long index, HMIValues* val) {
    LinkedListI* head = hm->collision_buckets[index];
    if(head == NULL) {
        head = allocate_listI();
        head->val = val;
        hm->collision_buckets[index] = head;
    }
    else{
        hm->collision_buckets[index] = list_insertI(head, val);
    }
}

static void HMI_insert(HashMapI* HM, int key, void* val) {
    // printf("%d %s\n", strlen(key), key);
    HMIValues* newVal = create_valueI(key, val);

    int index = hash_functionI(key)%HM->size;

    HMIValues* curr = HM->vals[index];

    HM->count++;
    if(curr == NULL) {
        HM->vals[index] = newVal;
    }
    else{
        if(curr->key == key) {
            HM->vals[index] = newVal;
        }
        else{
            handle_collisionI(HM, index, newVal);
        }
    }
}

static void* HMI_search(HashMapI* hm, int key) {
    // printf("index is: %d", index);
    // printf("%s\t", key);
    int index = hash_functionI(key)%hm->size;
    // printf("%s\n", key);
    HMIValues* val = hm->vals[index];
    LinkedListI* head = hm->collision_buckets[index];

    while(val != NULL) {
        if(val->key == key) return val->value;
        if(head == NULL) return NULL;
        val = head->val;
        head = head->next;
    }
    return NULL;
}

#endif