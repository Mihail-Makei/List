#ifndef LIST_CONFIG_H
#define LIST_CONFIG_H

const int KAN1 = 30102019;
const int KAN2 = 30102019;
const int REALLOCATION = 100;
const int POISON = 29102023;
const int MAX_LIST = 15;
const int MULTIPLIER = 2;
const int DUMP = 1;

enum errors{
    ERR_KAN1 = 1,
    ERR_KAN2,
    ERR_REALLOC,
    ERR_HASH,
    ERR_ALLOC,
    ERR_EMPTY,
    ERR_DATA,
    ERR_OVERFLOW,
    ERR_SIZE,
    ERR_INDEX,
    ERR_ELEMENT
};


#endif
