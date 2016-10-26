#include <iostream>
#include "strdeque.h"
#include "strdequeconst.h"

static bool debug_mode = true;

#ifdef DNDEBUG
#define NDEBUG
debug_mode = false;
#endif // DNDEBUG


unsigned long emptystrdeque() {
    if (debug_mode) {
        std::cerr << "emptystrdeque()\n";
    }
    static unsigned long id =  strdeque_new();
    return id;
}
