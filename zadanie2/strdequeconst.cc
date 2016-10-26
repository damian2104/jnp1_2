#include "strdeque.h"
#include "strdequeconst.h"

unsigned long emptystrdeque() {
    static unsigned long id =  strdeque_new();
    return id;
}