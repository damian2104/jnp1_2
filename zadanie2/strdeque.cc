#include <cstddef>
#include <map>
#include <deque>
#include <iostream>
#include<assert.h>
#include "strdeque.h"
#include "strdequeconst.h"

static bool debug_mode = true;

#ifdef DNDEBUG
#define NDEBUG
debug_mode = false;
#endif // DNDEBUG

namespace {

    typedef std::deque<std::string> my_deq;
    typedef std::map <unsigned long, my_deq> my_map;

    unsigned long& const_id(){
        static unsigned long id = emptystrdeque();
        return id;
    }

    my_map& strings() {
        static my_map* strings = new my_map;
        return *strings;
    }

    unsigned long next_id() {
        static unsigned long next_id=0;
        next_id++;
        assert(next_id != 0);
        return next_id;
    }

    my_deq& find_deq(unsigned long id, bool &success) {
        my_map::iterator it;
        it = strings().find(id);
        if (it == strings().end()) {
            success = false;
            return *(new my_deq);
        }
        success = true;
        return it->second;
    }

    int comp_not_null(my_deq& deq1, my_deq& deq2){
        my_deq::iterator dit1=deq1.begin(), dit2=deq2.begin();
        while (dit1 != deq1.end() && dit2 != deq2.end()) {
            int c= (*dit1).compare(*dit2);
            if (c < 0)
                return -1;
            if (c > 0)
                return 1;
            dit1++;
            dit2++;
        }
        if (dit1 != deq1.end())
            return 1;
        if (dit2 != deq2.end())
            return -1;
        return 0;
    }
}
unsigned long strdeque_new() {
    if (debug_mode) {
        std::cerr << "strdeque_new()\n";
    }
    my_deq new_deq;
    unsigned long id = next_id();
    std:: pair<unsigned long, my_deq> new_entry = std::make_pair (id, new_deq);
    strings().insert(new_entry);
    if (debug_mode) {
        std::cerr << "deque " << id << " created\n";
    }
    return id;
}

void strdeque_delete(unsigned long id) {
    if (id == const_id()) {
        if (debug_mode) {
            std::cerr << "strdeque_delete(the Empty Deque)\n";
        }
        return;
    }
    strings().erase(id);
    std::cerr << "strdeque_delete: deque " << id << " deleted\n";
}

size_t strdeque_size(unsigned long id) {
    bool success = false;
    my_deq& deq = find_deq(id, success);
    if(!success) {
        if (debug_mode) {
            std::cerr << "strdeque_size: deque does not exist\n";
        }
        return 0;
    }
    if (debug_mode) {
        std::cerr << "strdeque_size: " << deq.size() << "\n";
    }
    return (deq.size());
}


void strdeque_insert_at(unsigned long id, size_t pos, const char* value) {
    if (id == const_id() || value == NULL) {
        if (debug_mode) {
            if (id == const_id()) {
                std::cerr << "strdeque_insert_at: attempt to insert into the Empty Deque\n";
            }
            if (value == NULL) {
                std::cerr << "strdeque_insert_at: element is NULL\n";
            }
        }
        return;
    }
    bool success = false;
    my_deq& deq = find_deq(id, success);
    if(!success) {
        if (debug_mode) {
            std::cerr << "strdeque_insert_at: deque " << id << " does not exist\n";
        }
        return;
    }
    if (pos > deq.size()) {
        deq.insert(deq.end(), value);
        if (debug_mode) {
            std::cerr << "strdeque_insert_at: deque " << id << ", element " << value << " inserted at the end\n";
        }
    }
    else {
        std::string str(value);
        deq.insert(deq.begin()+pos, str);
        if (debug_mode) {
            std::cerr << "strdeque_insert_at: deque " << id << ", element " << value << " inserted at " << pos << "\n";
        }
    }
}

void strdeque_remove_at(unsigned long id, size_t pos){
    if(id == const_id()) {
        if (debug_mode) {
            std::cerr << "strdeque_remove_at: attempt to remove the Empty Deque\n";
        }
        return;
    }
    bool success = false;
    my_deq& deq = find_deq(id, success);
    if(!success || pos >= deq.size()) {
        if (debug_mode) {
            if (!success) {
                std::cerr << "strdeque_remove_at: deque " << id << " does not exist\n";
            }
            else if (pos >= deq.size()) {
                std::cerr << "strdeque_remove_at: position " << pos << " in deque " << id << " does not exist\n";
            }
        }
        return;
    }
    deq.erase(deq.begin()+pos);
    if (debug_mode) {
        std::cerr << "strdeque_remove_at: deque " << id << ", element at " << pos << " removed\n";
    }
}

const char* strdeque_get_at(unsigned long id, size_t pos){
    bool success = false;
    my_deq& deq = find_deq(id, success);
    if (!success || pos >= deq.size()) {
        if (debug_mode) {
            if (!success) {
                std::cerr << "strdeque_get_at: deque " << id << " does not exist\n";
            }
            if (pos >= deq.size()) {
                std::cerr << "strdeque_get_at: position " << pos << " does not exist in deque " << id << "\n";
            }
        }
        return NULL;
    }
    if (debug_mode) {
        std::cerr << "strdeque_get_at: deque " << id << ", element at " << pos << " is " << (deq[pos]).c_str() << "\n";
    }
    return (deq[pos]).c_str();
}

void strdeque_clear(unsigned long id){
    if (id == const_id()) {
        if (debug_mode) {
            std::cerr << "strdeque_clear: attempt to clear the Empty Deque\n";
        }
        return;
    }
    bool success = false;
    my_deq& deq = find_deq(id, success);
    if (!success) {
        if (debug_mode) {
            std::cerr << "strdeque_clear: deque does not exist\n";
        }
        return;
    }
    deq.clear();
    if (debug_mode) {
            std::cerr << "strdeque_clear: deque " << id << " cleared\n";
        }
}

int strdeque_comp(unsigned long id1, unsigned long id2){
    bool success1 = false, success2 = false;
    my_deq& deq1 = find_deq(id1, success1);
    my_deq& deq2 = find_deq(id2, success2);
    if(!success1) {
        if (!success2) {
            if (debug_mode) {
                std::cerr << "strdeque_comp: deque " << id1 << " and deque " << id2 << " do not exist\n";
            }
            return 0;
        }
        if (deq2.size() == 0) {
            if (debug_mode) {
                std::cerr << "strdeque_comp: deque " << id1 << " does not exist and deque " << id2 << " has size 0\n";
            }
            return 0;
        }
        if (debug_mode) {
            std::cerr << "strdeque_comp: deque " << id1 << " does not exist\n";
        }
        return -1;
    }
    if (!success2) {
        if (deq1.size() == 0) {
            if (debug_mode) {
                std::cerr << "strdeque_comp: deque " << id2 << " does not exist and deque " << id1 << " has size 0\n";
            }
            return 0;
        }
        if (debug_mode) {
            std::cerr << "strdeque_comp: deque " << id2 << " does not exist\n";
        }
        return 1;
    }
    int comp = comp_not_null (deq1, deq2);
    if (debug_mode) {
        std::cerr << "strdeque_comp: result of comparing deque " << id1 << " to " << "deque " << id2 << " is " << comp << "\n";
    }
    return comp;
}

