#include <stdlib.h>
#include <stdio.h>
#include "MyList.h"

void test();

int main() {
    test();
    return 0;
}

void test()
{
    list_t list = {};
    ListCreate(&list);

    {
        ListPushBack(&list, 10);
        ListPushBack(&list, 20);
        ListPushBack(&list, 30);
        ListPushBack(&list, 40);
        ListPushBack(&list, 50);
        ListPushBack(&list, 60);
        ListPushBack(&list, 70);
        ListPushBack(&list, 80);
        ListPushBack(&list, 90);
        ListPushBack(&list, 100);

        int value = ListPopBack(&list);
        printf("VALUE\t%d\n", value);
        value = ListPopBack(&list);
        printf("VALUE\t%d\n", value);
        value = ListPopBack(&list);
        printf("VALUE\t%d\n", value);
        value = ListPopBack(&list);
        printf("VALUE\t%d\n", value);
        value = ListPopBack(&list);
        printf("VALUE\t%d\n", value);
        value = ListPopBack(&list);
        printf("VALUE\t%d\n", value);
        value = ListPopBack(&list);
        printf("VALUE\t%d\n", value);
        value = ListPopBack(&list);
        printf("VALUE\t%d\n", value);
        value = ListPopBack(&list);
        printf("VALUE\t%d\n", value);
        value = ListTopBack(&list);
        printf("VALUE\t%d\n", value);
        value = ListPopBack(&list);
        printf("VALUE\t%d\n", value);

        printf("TEST 1 OK\n");
    }

    ListDestruct(&list);

    printf("\n\n\n");

    {
        ListCreate(&list);

        int where10 = ListPushFront(&list, 10);0
        int where20 = ListPushFront(&list, 20);
        int where30 = ListPushFront(&list, 30);
        int where40 = ListPushBack(&list, 40);
        int where50 = ListPushBack(&list, 50);
        int where60 = ListPushBack(&list, 60);
        int where70 = ListPushFront(&list, 70);
        int where55 = ListInsertAfter(&list, where50, 55);
        int where45 = ListInsertBefore(&list, where50, 45);
        printf("RESULT DELETE\t%d\n", ListDeleteAfter(&list, where30));
        printf("RESULT DELETE\t%d\n", ListDeleteBefore(&list, where45));
        printf("SEARCH\t%d\n", ListSearch(list, 50));

        ListDump(list);

        /*ListSortLogNumbers(&list);

        ListDump(list);*/

        ListSort(&list);

        ListDump(list);

        ErrPrint(list);

        ListPushBack(&list, 10);
        ListPushBack(&list, 20);
        ListPushBack(&list, 30);
        ListPushBack(&list, 40);
        ListPushBack(&list, 50);
        ListPushBack(&list, 60);
        ListPushBack(&list, 70);
        ListPushBack(&list, 80);
        ListPushBack(&list, 90);
        ListPushBack(&list, 100);
        ListPushBack(&list, 10);
        ListPushBack(&list, 20);
        ListPushBack(&list, 30);
        ListPushBack(&list, 40);
        ListPushBack(&list, 50);
        ListPushBack(&list, 60);
        ListPushBack(&list, 70);
        ListPushBack(&list, 80);
        ListPushBack(&list, 90);
        ListPushBack(&list, 100);
        ListPushBack(&list, 10);
        ListPushBack(&list, 20);
        ListPushBack(&list, 30);
        ListPushBack(&list, 40);
        ListPushBack(&list, 50);
        ListPushBack(&list, 60);
        ListPushBack(&list, 70);
        ListPushBack(&list, 80);
        ListPushBack(&list, 90);
        ListPushBack(&list, 100);
        ListPushBack(&list, 10);
        ListPushBack(&list, 20);
        ListPushBack(&list, 30);
        ListPushBack(&list, 40);
        ListPushBack(&list, 50);
        ListPushBack(&list, 60);
        ListPushBack(&list, 70);
        ListPushBack(&list, 80);
        ListPushBack(&list, 90);
        ListPushBack(&list, 100);
        ListPushBack(&list, 10);
        ListPushBack(&list, 20);
        ListPushBack(&list, 30);
        ListPushBack(&list, 40);
        ListPushBack(&list, 50);
        ListPushBack(&list, 60);
        ListPushBack(&list, 70);
        ListPushBack(&list, 80);
        ListPushBack(&list, 90);
        ListPushBack(&list, 100);
        ListInsertAfter(&list,25, 45);
        ListInsertAfter(&list,25, 45);
        ListInsertAfter(&list,25, 45);
        ListInsertAfter(&list,25, 45);
        ListInsertAfter(&list,25, 45);
        ListInsertAfter(&list,25, 45);
        ListInsertAfter(&list,25, 45);
        ListInsertBefore(&list, 60, 100);
        ListInsertBefore(&list, 60, 100);
        ListInsertBefore(&list, 60, 100);
        ListPushBack(&list, 150);
        ListPushBack(&list, 150);
        ListPushBack(&list, 150);
        ListDeleteAfter(&list, 62);
        ListDeleteBefore(&list, 65);
        ListSort(&list);

        ListDump(list);

        /*printf("VALUE\t%d\tINDEX\t%d\n", ListPopFront(&list), where70);
        printf("VALUE\t%d\tINDEX\t%d\n", ListPopBack(&list), where60);
        printf("VALUE\t%d\tINDEX\t%d\n", ListPopFront(&list), where30);
        printf("VALUE\t%d\tINDEX\t%d\n", ListPopFront(&list), where20);
        printf("VALUE\t%d\tINDEX\t%d\n", ListPopFront(&list), where10);
        printf("VALUE\t%d\tINDEX\t%d\n", ListPopFront(&list), where40);
        printf("VALUE\t%d\tINDEX\t%d\n", ListTopFront(&list), where50);
        printf("VALUE\t%d\tINDEX\t%d\n", ListPopFront(&list), where50);*/

        ListDestruct(&list);
        printf("TEST 2 OK\n");
    }

    {
        ListCreate(&list);

        ListPopBack(&list);

        if (list.err)
            ErrPrint(list);
        else
            printf("TEST 3 OK\n");

        ListDestruct(&list);
    }

    ListDestruct(&list);
}
