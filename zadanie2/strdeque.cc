#include <cstddef>
#include <map>
#include <deque>
#include <iostream>
#include <cassert>
#include "strdeque.h"
#include "strdequeconst.h"

#ifndef NDEBUG
static const bool debug = true;
#else
static const bool debug = false;
#endif

namespace {

    typedef std::deque<std::string> string_deq;
    typedef std::map<unsigned long, string_deq> deq_map;

    unsigned long &const_id() {
        static unsigned long id = jnp1::emptystrdeque();
        return id;
    }


    deq_map &deques() {
        static deq_map *deques = new deq_map;
        return *deques;
    }

    unsigned long next_id() {
        static unsigned long next_id = 0;
        next_id++;
        assert(next_id != 0);
        return next_id;
    }

    string_deq &find_deq(unsigned long id, bool &success) {
        deq_map::iterator it;
        it = deques().find(id);
        if (it == deques().end()) {
            success = false;
            return *(new string_deq);
        }
        success = true;
        return it->second;
    }
}

unsigned long jnp1::strdeque_new() {
    if (debug) {
        std::cerr << "strdeque_new()\n";
    }
    string_deq new_deq;
    unsigned long id = next_id();
    std::pair<unsigned long, string_deq> new_entry = std::make_pair(id, new_deq);
    deques().insert(new_entry);
    if (debug) {
        std::cerr << "deque " << id << " created\n";
    }
    return id;
}

void jnp1::strdeque_delete(unsigned long id) {
    if (id == const_id()) {
        if (debug) {
            std::cerr << "strdeque_delete(the Empty Deque)\n";
        }
        return;
    }
    deques().erase(id);
    if (debug) {
        std::cerr << "strdeque_delete: deque " << id << " deleted\n";
    }
}

size_t jnp1::strdeque_size(unsigned long id) {
    bool found = false;
    string_deq &deq = find_deq(id, found);
    if (!found) {
        if (debug) {
            std::cerr << "strdeque_size: deque does not exist\n";
        }
        return 0;
    }
    if (debug) {
        std::cerr << "strdeque_size: " << deq.size() << "\n";
    }
    return (deq.size());
}


void jnp1::strdeque_insert_at(unsigned long id, size_t pos, const char *value) {
    if (id == const_id()) {
        if (debug) {
            std::cerr << "strdeque_insert_at: attempt to insert into the Empty Deque\n";
        }
        return;
    }
    if (value == NULL) {
        if (debug) {
            std::cerr << "strdeque_insert_at: element is NULL\n";
        }
        return;
    }
    bool found = false;
    string_deq &deq = find_deq(id, found);
    if (!found) {
        if (debug) {
            std::cerr << "strdeque_insert_at: deque " << id << " does not exist\n";
        }
        return;
    }
    if (pos > deq.size()) {
        deq.insert(deq.end(), value);
        if (debug) {
            std::cerr << "strdeque_insert_at: deque " << id << ", element " << value << " inserted at the end\n";
        }
    } else {
        std::string str(value);
        deq.insert(deq.begin() + pos, str);
        if (debug) {
            std::cerr << "strdeque_insert_at: deque " << id << ", element " << value << " inserted at " << pos << "\n";
        }
    }
}

void jnp1::strdeque_remove_at(unsigned long id, size_t pos) {
    if (id == const_id()) {
        if (debug) {
            std::cerr << "strdeque_remove_at: attempt to remove the Empty Deque\n";
        }
        return;
    }
    bool found = false;
    string_deq &deq = find_deq(id, found);
    if (!found || pos >= deq.size()) {
        if (debug) {
            if (!found) {
                std::cerr << "strdeque_remove_at: deque " << id << " does not exist\n";
            } else if (pos >= deq.size()) {
                std::cerr << "strdeque_remove_at: position " << pos << " in deque " << id << " does not exist\n";
            }
        }
        return;
    }
    deq.erase(deq.begin() + pos);
    if (debug) {
        std::cerr << "strdeque_remove_at: deque " << id << ", element at " << pos << " removed\n";
    }
}

const char *jnp1::strdeque_get_at(unsigned long id, size_t pos) {
    bool found = false;
    string_deq &deq = find_deq(id, found);
    if (!found) {
        if (debug) {

            std::cerr << "strdeque_get_at: deque " << id << " does not exist\n";
        }
        return NULL;
    }

    if (pos >= deq.size()) {
        if (debug) {
            std::cerr << "strdeque_get_at: position " << pos << " does not exist in deque " << id << "\n";
        }
        return NULL;
    }
    if (debug) {
        std::cerr << "strdeque_get_at: deque " << id << ", element at " << pos << " is " << (deq[pos]).c_str() << "\n";
    }
    return (deq[pos]).c_str();
}

void jnp1::strdeque_clear(unsigned long id) {
    if (id == const_id()) {
        if (debug) {
            std::cerr << "strdeque_clear: attempt to clear the Empty Deque\n";
        }
        return;
    }
    bool found = false;
    string_deq &deq = find_deq(id, found);
    if (!found) {
        if (debug) {
            std::cerr << "strdeque_clear: deque does not exist\n";
        }
        return;
    }
    deq.clear();
    if (debug) {
        std::cerr << "strdeque_clear: deque " << id << " cleared\n";
    }
}

int jnp1::strdeque_comp(unsigned long id1, unsigned long id2) {
    bool found1 = false, found2 = false;
    string_deq &deq1 = find_deq(id1, found1);
    string_deq &deq2 = find_deq(id2, found2);
    if (!found1) {
        if (!found2) {
            if (debug) {
                std::cerr << "strdeque_comp: deque " << id1 << " and deque " << id2 << " do not exist\n";
            }
            return 0;
        }
        if (deq2.size() == 0) {
            if (debug) {
                std::cerr << "strdeque_comp: deque " << id1 << " does not exist and deque " << id2 << " has size 0\n";
            }
            return 0;
        }
        if (debug) {
            std::cerr << "strdeque_comp: deque " << id1 << " does not exist\n";
        }
        return -1;
    }
    if (!found2) {
        if (deq1.size() == 0) {
            if (debug) {
                std::cerr << "strdeque_comp: deque " << id2 << " does not exist and deque " << id1 << " has size 0\n";
            }
            return 0;
        }
        if (debug) {
            std::cerr << "strdeque_comp: deque " << id2 << " does not exist\n";
        }
        return 1;
    }
    if (deq1 > deq2) {
        if (debug) {
            std::cerr << "deque " << id1 << " is bigger\n";
        }
        return 1;
    }

    if (deq1 < deq2) {
        if (debug) {
            std::cerr << "deque " << id2 << " is bigger\n";
        }
        return -1;
    }
    if (debug) {
        std::cerr << "deques " << id1 << " and " << id2 << " are equal\n";
    }
    return 0;
}

