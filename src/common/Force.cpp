#include "common/Force.hpp"

Force::Force(vec3 dir) : val(dir) { }

vec3 Force::F() {
    return val;
}

vec3 Force::F(vec3 pos) {
    return F();
}
