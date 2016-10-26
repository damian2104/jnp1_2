#include <iostream>
#include "strdeque.h"
#include "strdequeconst.h"

#ifndef NDEBUG
static const bool debug = true;
#else
static const bool debug = false;
#endif

namespace {


    bool debug_mode() {
        static std::ios_base::Init init;
        return debug;
    }
}

unsigned long emptystrdeque() {
   if (debug_mode()) {
        std::cerr << "emptystrdeque()\n";
    }
    static unsigned long id =  strdeque_new();
    return id;
}
