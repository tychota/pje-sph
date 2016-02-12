#include "structure/proximityHash.hh"

proximityHash::proximityHash(double l, int64_t n): l(l), n(n) {
    console->debug("<HASH> Construct a new acceleration structure");
    console->debug("<HASH>  * --> number of particles : {} ", n);
    console->debug("<HASH>  * --> size of a grid element: {} ", l);
    console->debug("<HASH> Generating a primegenerator object");
    prime primegen;
    console->debug("<HASH>  * --> calling next prime ");
    n_h = primegen.next(2 * n);
    console->debug("<HASH>  * --> pirme generated: {} ", n_h);
    console->debug("<HASH> Reserving some space");
    auto space = n * (sizeof(particle) + sizeof(set<shared_ptr<particle>>));
    console->debug("<HASH>  * --> size of the space reserved: {} ", space);
    map.reserve(space);
}

int64_t proximityHash::get(vec3d vec) {
    console->debug("<HASH> Computing ap, bp, cp and hashes");
    int64_t ap = (int64_t) floor(vec.v[0]/this->l) * this->p1;
    int64_t bp = (int64_t) floor(vec.v[1]/this->l) * this->p2;
    int64_t cp = (int64_t) floor(vec.v[2]/this->l) * this->p3;
    console->debug("<HASH>  * --> ap: {}, bp: {}, cp {} ", ap, bp, cp);
    return  (ap ^ bp ^ cp) % this->n_h;
}

void proximityHash::add(shared_ptr<particle> ptr) {
    int64_t hash = get(ptr->curr_pos);

    // on recupère l'iterateur sur le pointeur
    unordered_map<int64_t, listParticle>::iterator got = map.find(hash);
    if (got == map.end()) {
        listParticle bucket{ ptr };
        map.insert({{hash, bucket}});
    } else {
        listParticle& bucket = got->second;
        bucket.insert(ptr);
    }
}

void proximityHash::remove(shared_ptr<particle> ptr) {
    int64_t hash = get(ptr->curr_pos);

    // on recupère l'iterateur sur le pointeur
    unordered_map<int64_t, listParticle>::iterator got = map.find(hash);
    if (got == map.end()) {
        throw std::exception();
    } else {
        listParticle bucket = got->second;
        bucket.erase(std::find(bucket.begin(), bucket.end(), ptr));
        /*if (bucket.empty())
            map.erase(got);*/
    }
}
