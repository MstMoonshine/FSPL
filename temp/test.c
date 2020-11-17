#include "include/symbolTable.h"

int main() {
    symbolTable *newTable = createTable();
    clearTable(newTable);

    insert(newTable, createNodeEntry("1", createEntryValue(1)));
}