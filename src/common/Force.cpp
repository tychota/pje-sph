#include "common/Force.hpp"

Force::Force(VEC dir) : val(dir) { }

VEC Force::F() {
    return val;
}

VEC Force::F(VEC pos) {
    return F();
}
