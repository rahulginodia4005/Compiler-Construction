#include<string.h>
#include<stdlib.h>
#include<stdio.h>

unsigned long hash_function(char* str) {
    unsigned long hash = 5381;
    int c;
    while((c = (*str++))) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

typedef struct HMValues {
    char* key;
    void* value;
} HMValues;

typedef struct LinkedList{
    HMValues* val;
    struct LinkedList* next;
} LinkedList;

typedef struct HashMap{
    HMValues** vals;
    LinkedList** collision_buckets;
    int count;
    int size;
} HashMap;

LinkedList* allocate_list() {
    LinkedList* newList = (LinkedList*) malloc(sizeof(LinkedList));
    return newList;
}

LinkedList* list_insert(LinkedList* list, HMValues* val) {
    if(!list) {
        LinkedList* head = allocate_list();
        head->val = val;
        head->next = NULL;
        list = head;
        return list;
    }
    else if(list->next == NULL){
        LinkedList* node = allocate_list();
        node->val = val;
        node->next = NULL;
        list->next = node;
        return list;
    }

    LinkedList* temp = list;

    while(temp->next->next) temp = temp->next;
    LinkedList* node = allocate_list();
    node->val = val;
    node->next = NULL;
    temp->next = node;
    return list;
}

LinkedList** create_collision_buckets(HashMap* hm) {
    LinkedList** collision_buckets = (LinkedList**) calloc(hm->size, sizeof(LinkedList*));
    for(int i = 0;i<hm->size;i++) collision_buckets[i] = NULL;
    return collision_buckets;
}

HMValues* create_value(char* key, void* val) {
    HMValues* newVal = (HMValues*) malloc(sizeof(HMValues));
    // printf("%s\n", key);
    newVal->key = (char*) malloc(strlen(key) * sizeof(char));
    strcpy(newVal->key, key);
    newVal->value = val;
    return newVal;
}

HashMap* create_table(int size){
    HashMap* newHM = (HashMap*) malloc(sizeof(HashMap));
    newHM->size = size;
    newHM->count = 0;
    newHM->vals = (HMValues**) calloc(newHM->size, sizeof(HMValues*));
    for(int i = 0;i<newHM->size;i++) {
        newHM->vals[i] = NULL;
    } 
    newHM->collision_buckets = create_collision_buckets(newHM);
    return newHM;
}

void handle_collision(HashMap* hm, unsigned long index, HMValues* val) {
    LinkedList* head = hm->collision_buckets[index];
    if(head == NULL) {
        head = allocate_list();
        head->val = val;
        hm->collision_buckets[index] = head;
    }
    else{
        hm->collision_buckets[index] = list_insert(head, val);
    }
}

void HM_insert(HashMap* HM, char key[], void* val) {
    printf("%s\n", key);
    HMValues* newVal = create_value(key, val);

    int index = hash_function(key)%HM->size;

    HMValues* curr = HM->vals[index];

    if(curr == NULL) {
    //     if(HM->count == HM->size) {
    //         printf("Error!!! HashMap is full\n");
    //         free(newVal);
    //         return;
    //     }
        HM->vals[index] = newVal;
        HM->count++;
    }
    else{
        if(strcmp(curr->key, key) == 0) {
            HM->vals[index] = newVal;
        }
        else{
            handle_collision(HM, index, newVal);
        }
    }
}

void* HM_search(HashMap* hm, char *key) {
    int index = hash_function(key)%hm->size;
    // printf("index is: %d", index);
    HMValues* val = hm->vals[index];
    LinkedList* head = hm->collision_buckets[index];

    while(val != NULL) {
        if(strcmp(val->key, key) == 0) return val->value;
        if(head == NULL) return NULL;
        val = head->val;
        head = head->next;
    }
    return NULL;
}
