#include <iostream>
#include <cassert>
//#include <cstddef>
#include <cstring>
#include "../cstrdeque"
#include "../cstrdequeconst"

int main() {
    unsigned long id1 = ::jnp1::strdeque_new();
    unsigned long id2 = jnp1::emptystrdeque();
    jnp1::strdeque_insert_at(id1, 1, "aa");
    jnp1::strdeque_insert_at(id1, 1, NULL);
    jnp1::strdeque_insert_at(id1, 1, "bb");
    jnp1::strdeque_insert_at(id1, 1, "cc");
    assert(jnp1::strdeque_size(id1)==3);
    assert(strcmp(jnp1::strdeque_get_at(id1, 0),"aa")==0);
    assert(strcmp(jnp1::strdeque_get_at(id1, 1),"cc")==0);
    assert(strcmp(jnp1::strdeque_get_at(id1, 2),"bb")==0);
    jnp1::strdeque_remove_at(id1, 3);
    assert(jnp1::strdeque_size(id1)==3);
    jnp1::strdeque_remove_at(id1, 0);
    assert(strcmp(jnp1::strdeque_get_at(id1, 0), "cc")==0);
    assert(jnp1::strdeque_get_at(id1, 2)==NULL);
    assert(jnp1::strdeque_get_at(id1+1, 0)==NULL);
    assert(jnp1::strdeque_comp(id1, id2)==1);

    jnp1::strdeque_insert_at(id2, 2, "aa");
    jnp1::strdeque_insert_at(id2, 0, "cc");
    jnp1::strdeque_insert_at(id2, 99, NULL);
    assert(jnp1::strdeque_size(id2)==0);
    jnp1::strdeque_clear(id1);
    assert(jnp1::strdeque_comp(id1, id2)==0);
    jnp1::strdeque_insert_at(id1, 0, "aa");
    assert(jnp1::strdeque_size(id1)==1);
    jnp1::strdeque_delete(id1);
    assert(jnp1::strdeque_size(id1)==0);
    jnp1::strdeque_remove_at(id2, 0);
    jnp1::strdeque_clear(id2);
    jnp1::strdeque_delete(id2);
    assert(jnp1::strdeque_comp(id1, id2)==0);

    return 0;

}

