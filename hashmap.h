#include<string.h>
#include<stdlib.h>

unsigned long hash_function(unsigned char* str) {
    unsigned long hash = 5381;
    int c;
    while(c = *str++) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

template <typename T> struct HMValues {
    char* key;
    T value;
};

template <typename T> struct LinkedList{
    HMValues<T>* val;
    LinkedList* next;
};

template <typename T> struct HashMap{
    HMValues<T>** vals;
    LinkedList<T>** collision_buckets;
    int count;
    int size;
};

template <typename T> LinkedList<T>* allocate_list() {
    LinkedList<T>* newList = (LinkedList<T>*) malloc(sizeof(LinkedList<T>));
    return newList;
}

template <typename T> LinkedList<T>* list_insert(LinkedList<T>* list, HMValues<T>* val) {
    if(!list) {
        LinkedList<T>* head = allocate_list<T>();
        head->val = val;
        head->next = NULL;
        list = head;
        return list;
    }
    else if(list->next = NULL){
        LinkedList<T>* node = allocate_list<T>();
        node->val = val;
        node->next = NULL;
        list->next = node;
        return list;
    }

    LinkedList<T>* temp = list;

    while(temp->next->next) temp = temp->next;
    LinkedList<T>* node = allocate_list<T>();
    node->val = val;
    node->next = NULL;
    temp->next = node;
    return list;
}

template <typename T> LinkedList<T>** create_collision_buckets(HashMap<T>* hm) {
    LinkedList<T>** collision_buckets = (LinkedList<T>**) calloc(hm->size, sizeof(LinkedList<T>*));
    for(int i = 0;i<hm->size;i++) collision_buckets[i] = NULL;
    return collision_buckets;
}

template <typename T> HMValues<T>* create_value(char* key, T val) {
    HMValues<T>* newVal = (HMValues<T>*) malloc(sizeof(HMValues<T>));
    newVal->key = (char*) malloc(strlen(key) + 1);
    strcpy(newVal->key, key);
    newVal->value = val;
    return newVal;
}

template <typename T> HashMap<T>* create_table(int size){
    HashMap<T>* newHM = (HashMap<T>*) malloc(sizeof(HashMap<T>));
    newHM->size = size;
    newHM->count = 0;
    newHM->vals = (HMValues<T>**) calloc(newHM->size, sizeof(HMValues<T>*));
    for(int i = 0;i<newHM->size;i++) {
        newHM->vals[i] = NULL;
    } 
    newHM->collision_buckets = create_collision_buckets<T>(newHM);
    return newHM;
}

template <typename T> void free_val(HMValues<T>* val) {
    free(val->key);
    free(val->value);
    free(val);
}

template <typename T> void free_HM(HashMap<T>* HM) {
    for(int i = 0;i<HM->size;i++) {
        if(HM->vals[i] != NULL) free(HM->vals[i]);
    }
    free(HM->vals);
    free(HM);
}

template <typename T> void handle_collision(HashMap<T>* hm, unsigned long index, HMValues<T>* val) {
    LinkedList<T>* head = hm->collision_buckets[index];
    if(head == NULL) {
        head = allocate_list<T>();
        head->val = val;
        hm->collision_buckets[index] = head;
    }
    else{
        hm->collision_buckets[index] = list_insert<T>(head, val);
    }
}

template <typename T> void HM_insert(HashMap<T>* HM, char* key, T val) {
    HMValues<T>* newVal = create_value<T>(key, val);

    int index = hash_function(key)%HM->size;

    HMValues<T>* curr = HM->vals[index];

    if(curr == NULL) {
        if(HM->count == HM->size) {
            printf("Error!!! HashMap is full\n");
            free(newVal);
            return;
        }
        HM->vals[index] = newVal;
        HM->count++;
    }
    else{
        if(strcmp(curr->key, key) == 0) {
        }
        else{
            handle_collision<T>(HM, index, newVal);
        }
    }
}

template <typename T> T HM_search(HashMap<T>* hm, char *key) {
    int index = hash_function(key);
    HMValues<T>* val = hm->vals[index];
    LinkedList<T>* head = hm->collision_buckets[index];

    while(val != NULL) {
        if(strcmp(val->key, key) == 0) return val->value;
        if(head == NULL) return NULL;
        item = head->val;
        head = head->next;
    }
    return NULL;
}