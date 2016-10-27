#include "strdeque.h"
#include "strdequeconst.h"

#ifndef NDEBUG
static const bool debug = true;
#else
static const bool debug = false;
#endif


unsigned long jnp1::emptystrdeque() {
    if (debug) {
        std::cerr << "emptystrdeque()\n";
    }
    static unsigned long id = jnp1::strdeque_new();
    return id;
}
