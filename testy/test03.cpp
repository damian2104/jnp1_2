#include<cassert>
//#include <cstddef>
#include <iostream>
#include "../cstrdeque"
#include "../cstrdequeconst"

int main() {
    unsigned long id1=jnp1::strdeque_new(), id2=jnp1::strdeque_new(), id3=jnp1::emptystrdeque();
    for (unsigned int i=0; i<1000; i++) {
        jnp1::strdeque_insert_at(id1, i, "a");
        jnp1::strdeque_insert_at(id2, i, "a");
    }
    assert(jnp1::strdeque_comp(id1, id2)==0);
    jnp1::strdeque_insert_at(id1, 1000, "a");
    assert(jnp1::strdeque_comp(id1, id2)==1);
    jnp1::strdeque_insert_at(id2, 1000, "b");
    assert(jnp1::strdeque_comp(id1, id2)==-1);
    jnp1::strdeque_remove_at(id2, 0);
    assert(jnp1::strdeque_comp(id1, id2)==-1);
    assert(jnp1::strdeque_comp(id1, id1+id2+id3)==1);
    assert(jnp1::strdeque_comp(id1, id3)==1);
    return 0;
}