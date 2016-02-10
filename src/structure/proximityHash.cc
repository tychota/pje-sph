#include "structure/proximityHash.hh"

proximityHash::proximityHash(double l, int64_t n): l(l), n(n) {
    prime primegen;
    n_h = primegen.next(2 * n);
    map.reserve(n * sizeof(particle));
}

int64_t proximityHash::get(vec3d vec) {
    int64_t ap = (int64_t) floor(vec.v[0]/this->l) * this->p1;
    int64_t bp = (int64_t) floor(vec.v[1]/this->l) * this->p2;
    int64_t cp = (int64_t) floor(vec.v[2]/this->l) * this->p3;
    return  (ap ^ bp ^ cp) % this->n_h;
}

void proximityHash::add(particle p) {
    int64_t hash = get(p.curr_pos);

    shared_ptr<particle> ptr;
    ptr.reset(&p);

    // on recupère l'iterateur sur le pointeur
    unordered_map<int64_t, listParticle>::iterator got = map.find(hash);
    if (got == map.end()) {
        listParticle bucket{ ptr };
        map.insert({{hash, bucket}});
    } else {
        listParticle bucket = got->second;
        bucket.push_back(ptr);
    }
}

