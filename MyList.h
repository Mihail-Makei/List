#ifndef LIST_MYLIST_H
#define LIST_MYLIST_H
#include "Config.h"
#include <assert.h>


typedef int elem_t;


typedef struct MyList
{
    int kan1;
    elem_t* data;
    int* next;
    int* prev;
    int size;
    int capacity;
    int head;
    int tail;
    int free;
    int hash;
    int err;
    int sorted;
    int kan2;
} list_t;


int ListHash(list_t list)
{
    int hash = 0;
    for (int i = 0; i < list.capacity; i++)
        hash = hash * 2 + list.data[i];
    return hash;
}

bool verificator(list_t list)
{
    if (list.kan1 != KAN1)
    {
        list.err = ERR_KAN1;
        return false;
    }

    if (list.kan2 != KAN2)
    {
        list.err = ERR_KAN2;
        return false;
    }

    if (list.size < 0)
    {
        list.err = ERR_SIZE;
        return false;
    }

    if (list.hash != ListHash(list))
    {
        list.err = ERR_HASH;
        return false;
    }

    if (list.data == nullptr)
    {
        list.err = ERR_DATA;
        return false;
    }

    if (list.size > list.capacity)
    {
        list.err = ERR_OVERFLOW;
        return false;
    }

    return true;
}

int ListCreate(list_t* list)
{
    list->kan1 = KAN1;
    list->kan2 = KAN2;

    list->size = 0;
    list->capacity = MAX_LIST;

    list->data = (elem_t*) calloc(list->capacity, sizeof(elem_t));
    if (!list->data)
    {
        list->err = ERR_ALLOC;
        return 0;
    }

    list->next = (int*) calloc(list->capacity, sizeof(int));
    if (!list->next)
    {
        list->err = ERR_ALLOC;
        return 0;
    }

    list->prev = (int*) calloc(list->capacity, sizeof(int));
    if (!list->prev)
    {
        list->err = ERR_ALLOC;
        return 0;
    }

    list->free = 1;
    list->head = 0;
    list->tail = 0;

    list->data[0] = POISON;
    list->next[0] = 0;
    list->prev[0] = 0;

    list->data[list->capacity-1] = POISON;
    list->next[list->capacity-1] = 0;
    list->prev[list->capacity-1] = -1;

    for (int i = 1; i < (list->capacity - 1); i++)
    {
        list->data[i] = POISON;
        list->next[i] = i + 1;
        list->prev[i] = -1;
    }

    list->hash = ListHash(*list);
    list->err = 0;
    return 1;
}

int ListResize(list_t* list)
{
    assert(verificator(*list));

    list->capacity *= MULTIPLIER;

    elem_t* data = (elem_t*) realloc(list->data, list->capacity * sizeof(elem_t));
    if (!data)
    {
        list->err = ERR_REALLOC;
        return 0;
    }

    int* next = (int*) realloc(list->next, list->capacity * sizeof(int));
    if (!next)
    {
        list->err = ERR_REALLOC;
        return 0;
    }

    int* prev = (int*) realloc(list->prev, list->capacity * sizeof(int));
    if (!prev)
    {
        list->err = ERR_REALLOC;
        return 0;
    }

    list->data = data;
    for (int i = (list->capacity / MULTIPLIER); i < list->capacity; i++)
        list->data[i] = POISON;

    list->next = next;
    for (int i = (list->capacity / MULTIPLIER); i < list->capacity; i++)
        list->next[i] = i + 1;
    list->next[list->capacity - 1] = 0;
    if (list->prev[list->capacity / MULTIPLIER - 1] == -1)
        list->next[list->capacity / MULTIPLIER - 1] = list->capacity / MULTIPLIER;

    list->prev = prev;
    for (int i = (list->capacity / MULTIPLIER); i < list->capacity; i++)
        list->prev[i] = -1;

    list->free = list->capacity / MULTIPLIER;

    list->hash = ListHash(*list);
    return 1;
}


int ListPushBack(list_t* list, elem_t value)
{
    assert(verificator(*list));

    list->size++;
    if (list->size == list->capacity)
        ListResize(list);

    int num = list->free;
    printf("INDEX\t%d\n", num);
    list->data[list->free] = value;

    list->prev[list->free] = list->tail;
    if (list->size == 1)
        list->head = list->free;

    list->tail = list->free;
    int temp = list->next[list->free];
    list->next[list->free] = 0;
    if (list->size > 1)
        list->next[list->prev[list->free]] = list->free;
    list->free = temp;

    list->hash = ListHash(*list);

    return num;
}


elem_t ListPopBack(list_t* list)
{
    assert(verificator(*list));
    if (list->size == 0)
    {
        list->err = ERR_EMPTY;
        return -1;
    }

    elem_t value = list->data[list->tail];
    list->size--;

    if (list->size == 0)
    {
        list->next[list->tail] = list->free;
        list->free = list->tail;

        list->head = 0;
        list->tail = 0;
        list->prev[list->free] = -1;
        list->data[list->free] = POISON;

        list->hash = ListHash(*list);

        return value;
    }

    list->next[list->tail] = list->free;
    list->free = list->tail;
    list->tail = list->prev[list->free];
    list->next[list->prev[list->free]] = 0;
    list->prev[list->free] = -1;
    list->data[list->free] = POISON;
    list->hash = ListHash(*list);

    return value;
}

elem_t ListTopBack(list_t* list)
{
    assert(verificator(*list));
    if (list->size == 0)
    {
        list->err = ERR_EMPTY;
        return -1;
    }

    return list->data[list->tail];
}

int ListPushFront(list_t* list, elem_t value)
{
    assert(verificator(*list));

    list->size++;
    if (list->size == list->capacity)
        ListResize(list);

    if (list->size == 1)
    {
        list->data[list->free] = value;
        list->tail = list->free;
        list->head = list->free;
        list->prev[list->free] = 0;
        int temp = list->free;
        list->free = list->next[temp];
        list->next[temp] = 0;
        list->hash = ListHash(*list);

        return temp;
    }

    list->data[list->free] = value;
    int temp = list->free;
    list->free = list->next[temp];
    list->next[temp] = list->head;
    list->head = temp;
    list->prev[temp] = 0;
    list->prev[list->next[temp]] = temp;
    list->hash = ListHash(*list);


    return temp;
}

elem_t ListPopFront(list_t* list)
{
    assert(verificator(*list));
    if (list->size == 0)
    {
        list->err = ERR_EMPTY;
        return -1;
    }

    list->size--;
    elem_t value = list->data[list->head];

    list->data[list->head] = POISON;
    int temp = list->head;
    list->head = list->next[temp];
    list->next[temp] = list->free;
    list->prev[temp] = -1;
    list->free = temp;
    list->prev[list->head] = 0;
    if (list->size == 0)
    {
        list->tail = 0;
    }
    list->hash = ListHash(*list);

    return value;
}

elem_t ListTopFront(list_t* list)
{
    assert(verificator(*list));
    if (list->size == 0)
    {
        list->err = ERR_EMPTY;
        return -1;
    }

    return list->data[list->head];
}

int ListInsertAfter(list_t* list, int index, elem_t value)
{
    assert(verificator(*list));
    if (list->prev[index] == -1)
    {
        list->err = ERR_INDEX;
        return -1;
    }

    list->size++;
    if (list->size == list->capacity)
        ListResize(list);

    int num = 0;
    if (index == list->tail)
    {
        num = ListPushBack(list, value);
        list->hash = ListHash(*list);
        return num;
    }

    num = list->free;
    list->free = list->next[num];
    list->data[num] = value;
    list->prev[num] = index;
    list->next[num] = list->next[index];
    list->prev[list->next[num]] = num;
    list->next[index] = num;

    list->hash = ListHash(*list);
    return num;
}

elem_t ListDeleteAfter(list_t* list, int index)
{
    assert(verificator(*list));
    if (list->prev[index] == -1)
    {
        list->err = ERR_INDEX;
        return -1;
    }
    if (list->next[index] == 0)
    {
        list->err = ERR_ELEMENT;
        return -1;
    }

    list->size--;
    int num = 0;

    if (list->next[index] == list->tail)
    {
        num = ListPopBack(list);
        list->hash = ListHash(*list);
        return num;
    }
    num = list->data[list->next[index]];

    int next = list->next[index];
    list->prev[list->next[next]] = index;
    list->prev[next] = -1;
    list->next[index] = list->next[next];
    list->next[next] = list->free;
    list->free = next;
    list->data[next] = POISON;
    list->hash = ListHash(*list);
    return num;
}

int ListInsertBefore(list_t* list, int index, elem_t value)
{
    assert(verificator(*list));
    if (list->prev[index] == -1)
    {
        list->err = ERR_INDEX;
        return -1;
    }

    list->size++;
    if (list->size == list->capacity)
        ListResize(list);

    int num = 0;
    if (index == list->head)
    {
        num = ListPushFront(list, value);
        list->hash = ListHash(*list);
        return num;
    }
    num = list->free;

    list->free = list->next[num];
    list->data[num] = value;
    list->next[num] = index;
    list->prev[num] = list->prev[index];
    list->prev[index] = num;
    list->next[list->prev[num]] = num;

    list->hash = ListHash(*list);

    return num;
}

elem_t ListDeleteBefore(list_t* list, int index)
{
    assert(verificator(*list));
    if (list->prev[index] == -1)
    {
        list->err = ERR_INDEX;
        return -1;
    }
    if (list->prev[index] == 0)
    {
        list->err = ERR_ELEMENT;
        return -1;
    }

    list->size--;
    int num = 0;
    if (list->prev[index] == list->head)
    {
        num = ListPopFront(list);
        list->hash = ListHash(*list);
        return num;
    }

    int prev = list->prev[index];
    num = list->data[prev];
    list->data[prev] = POISON;
    list->next[list->prev[prev]] = index;
    list->prev[index] = list->prev[prev];
    list->prev[prev] = -1;
    list->next[prev] = list->free;
    list->free = prev;
    list->hash = ListHash(*list);

    return num;
}

int ListHead(list_t list)
{
    assert(verificator(list));
    return list.head;
}

int ListNext(list_t* list, int index)
{
    assert(verificator(*list));
    if (list->prev[index] == -1)
    {
        list->err = ERR_INDEX;
        return 0;
    }
    if (list->next[index] == 0)
    {
        list->err = ERR_ELEMENT;
        return 0;
    }

    return list->next[index];
}

int ListTail (list_t list)
{
    assert(verificator(list));
    return list.tail;
}

int ListPrev(list_t* list, int index)
{
    assert(verificator(*list));
    if (list->prev[index] == -1)
    {
        list->err = ERR_INDEX;
        return -1;
    }
    if (list->prev[index] == 0)
    {
        list->err = ERR_ELEMENT;
        return 0;
    }

    return list->prev[index];
}

int ListSearch(list_t list, elem_t value)
{
    assert(verificator(list));

    int i = list.head;
    while (list.data[i] != value)
    {
        i = list.next[i];
        if (i == 0)
            return 0;
    }
    return i;
}

void ListSortLogNumbers(list_t* list) // NOT READY
{
    assert(verificator(*list));

    list_t* temp = {};
    temp = (list_t*) calloc(1, sizeof(list_t));
    ListCreate(temp);

    temp->size = list->size;
    temp->capacity = list->capacity;
    temp->head = 1;
    temp->kan1 = list->kan1;
    temp->kan2 = list->kan2;
    temp->tail = list->size;

    if (temp->size == temp->capacity)
        temp->free = 0;
    else
        temp->free = temp->size + 1;
    temp->next[temp->size] = 0;
    for (int i = 1; i <= temp->size; i++)
        temp->prev[i] = i - 1;

    int counter = list->head;
    int tempcounter = 0;
    for (int i = 1; i <= temp->size; i++)
    {
        temp->data[i] = list->data[counter];
        tempcounter = list->next[counter];
        counter = tempcounter;
    }


    list->kan1 = temp->kan1;
    list->size = temp->size;
    for (int i = 0; i < list->capacity; i++)
    {
        list->data[i] = temp->data[i];
        list->next[i] = temp->next[i];
        list->prev[i] = temp->prev[i];
    }
    list->capacity = temp->capacity;
    list->head = temp->head;
    list->tail = temp->tail;
    list->free = temp->free;
    list->hash = ListHash(*list);
    list->kan2 = temp->kan2;

    ///list = temp; - NOT WORKING
}


int cmp (const int *a, const int *b)
{
    return *a - *b;
}


void ListSort(list_t* list)
{
    assert(verificator(*list));

    elem_t* tempdata = nullptr;
    tempdata = (elem_t*) calloc(list->size, sizeof(elem_t));

    int counter = list->head;
    int tmpcounter = 0;
    for (int i = 0; i < list->size; i++)
    {
        tempdata[i] = list->data[counter];
        tmpcounter = list->next[counter];
        counter = tmpcounter;
    }

    qsort(tempdata, list->size, sizeof(elem_t), (int(*) (const void*, const void*)) cmp);

    for (int i = 1; i <= list->size; i++)
        list->data[i] = tempdata[i-1];
    for (int i = list->size + 1; i < list->capacity; i++)
        list->data[i] = POISON;

    for (int i = 1; i < list->capacity; i++)
    {
        list->prev[i] = -1;
        list->next[i] = i + 1;
    }
    for (int i = 1; i <= list->size; i++)
        list->prev[i] = i - 1;
    list->next[list->size] = 0;
    list->next[list->capacity - 1] = 0;

    list->head = 1;
    list->tail = list->size;
    list->free = list->size + 1;

    list->hash = ListHash(*list);
}

void ListDump(list_t list)
{
    printf("KAN1\t%d\n", list.kan1);
    printf("KAN2\t%d\n", list.kan2);
    printf("SIZE\t%d\n", list.size);
    printf("CAPACITY\t%d\n", list.capacity);
    printf("HEAD\t%d\n", list.head);
    printf("TAIL\t%d\n", list.tail);
    printf("FREE\t%d\n", list.free);

    for (int i = 0; i < list.capacity; i++)
        printf("NUM\t%d\tDATA\t%d\tNEXT\t%d\tPREV\t%d\n", i, list.data[i], list.next[i], list.prev[i]);
}

void ErrPrint(list_t list)
{
    switch (list.err)
    {
        case ERR_KAN1:
            printf("Error %d. List is spoilt\n", list.err);
            if (DUMP)
                ListDump(list);
            break;

        case ERR_KAN2:
            printf("Error %d. List is spoilt\n", list.err);
            if (DUMP)
                ListDump(list);
            break;

        case ERR_REALLOC:
            printf("Error %d. Reallocation error\n", list.err);
            if (DUMP)
                ListDump(list);
            break;

        case ERR_HASH:
            printf("Error %d. Hash error\n", list.err);
            if (DUMP)
                ListDump(list);
            break;

        case ERR_ALLOC:
            printf("Error %d. Allocation error\n", list.err);
            if (DUMP)
                ListDump(list);
            break;

        case ERR_EMPTY:
            printf("Error %d. List is empty\n", list.err);
            if (DUMP)
                ListDump(list);
            break;

        case ERR_DATA:
            printf("Error %d. List data not found\n", list.err);
            if (DUMP)
                ListDump(list);
            break;

        case ERR_OVERFLOW:
            printf("Error %d. List size is bigger than list capacity\n", list.err);
            if (DUMP)
                ListDump(list);
            break;

        case ERR_SIZE:
            printf("Error %d. List size is below zero\n", list.err);
            if (DUMP)
                ListDump(list);
            break;

        case ERR_INDEX:
            printf("Error %d. Empty element\n", list.err);
            if (DUMP)
                ListDump(list);
            break;

        case ERR_ELEMENT:
            printf("Error %d. Empty element\n", list.err);
            if (DUMP)
                ListDump(list);
            break;
    }
}

void ListDestruct(list_t* list)
{
    free(list->data);
    list->data = nullptr;

    free(list->next);
    list->next = nullptr;

    free(list->prev);
    list->prev = nullptr;
}

#endif //LIST_MYLIST_H
