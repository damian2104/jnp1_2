#include "strdeque.h"
#include "strdequeconst.h"

static bool debug_mode = true;

#ifdef DNDEBUG
#define NDEBUG
debug_mode = false;
#endif // DNDEBUG
#include<assert.h>

unsigned long emptystrdeque() {
    if (debug_mode) {
        cerr << "emptystrdeque()\n";
    }
    static unsigned long id =  strdeque_new();
    assert(id == 0);
    return id;
}
