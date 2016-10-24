#include <cstddef>
#include <map>
#include <deque>
#include <iostream>
#include "strdeque.h"

namespace {

    typedef std::deque<std::string> my_deq;
    typedef std::map <unsigned long, my_deq> my_map;

    my_map& strings() {
        static my_map* strings = new my_map;
        return *strings;
    }

    unsigned long next_id() {
        static unsigned long next_id=0;
        next_id++;
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
    my_deq new_deq;
    unsigned long id = next_id();
    std:: pair<unsigned long, my_deq> new_entry = std::make_pair (id, new_deq);
    strings().insert(new_entry);
    return id;
}

void strdeque_delete(unsigned long id) {
    strings().erase(id);
}

size_t strdeque_size(unsigned long id) {

    bool success = false;
    my_deq& deq = find_deq(id, success);
    if(!success)
        return 0;
    return (deq.size());
}


void strdeque_insert_at(unsigned long id, size_t pos, const char* value) {
    bool success = false;
    my_deq& deq = find_deq(id, success);
    if(!success || value == NULL)
        return;
    if (pos > deq.size())
        deq.insert(deq.end(), value);
    else {
        std::string str(value);
        deq.insert(deq.begin()+pos, str);
    }
}

void strdeque_remove_at(unsigned long id, size_t pos){
    bool success = false;
    my_deq& deq = find_deq(id, success);
    if(!success || pos >= deq.size())
        return;
    deq.erase(deq.begin()+pos);
}

const char* strdeque_get_at(unsigned long id, size_t pos){
    bool success = false;
    my_deq& deq = find_deq(id, success);
    if(!success || pos >= deq.size())
        return NULL;
    return (deq[pos]).c_str();
}

void strdeque_clear(unsigned long id){
    bool success = false;
    my_deq& deq = find_deq(id, success);
    if (!success)
        return;
    deq.clear();
}

int strdeque_comp(unsigned long id1, unsigned long id2){
    bool success1 = false, success2 = false;
    my_deq& deq1 = find_deq(id1, success1);
    my_deq& deq2 = find_deq(id2, success2);
    if(!success1) {
        if (!success2)
            return 0;
        if(deq2.size() == 0)
            return 0;
        return -1;
    }
    if(!success2) {
        if (deq1.size() == 0)
            return 0;
        return 1;
    }
    return comp_not_null (deq1, deq2);
}

