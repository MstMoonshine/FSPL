#include "include/scopeStack.h"
#include <stdio.h>

/* RUN THIS:
gcc -c test.c -o test.o -I../ ; gcc -o test -I../ test.o -L../lib -lsplc ; ./test
*/

int main() {
    symbolTable *table1 = createTable(createNodeEntry("ID1", createEntryValue(1)));
    symbolTable *table2 = createTable(createNodeEntry("ID2", createEntryValue(2)));
    symbolTable *table3 = createTable(createNodeEntry("ID3", createEntryValue(3)));

    scopeStack *stack = initStack(table1);
    pushScope(stack, table2);
    pushScope(stack, table3);

    printf("********\n");
    printStack(*stack);
    printf("********\n");

    popScope(stack);

    printf("********\n");
    printStack(*stack);
    printf("********\n");

}