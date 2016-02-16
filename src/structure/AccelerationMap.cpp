#include "structure/AccelerationMap.hpp"

AccelerationMap::AccelerationMap(double l, int64_t n): l(l), n(n) {
    console->debug("<HASH> Construct a new acceleration structure");
    console->debug("<HASH>  * --> number of particles : {} ", n);
    console->debug("<HASH>  * --> size of a grid element: {} ", l);
    console->debug("<HASH> Generating a primegenerator object");
    Prime primegen;
    console->debug("<HASH>  * --> calling next prime ");
    n_h = primegen.next(2 * n);
    console->debug("<HASH>  * --> pirme generated: {} ", n_h);
    console->debug("<HASH> Reserving some space");
    auto space = n * (sizeof(set<shared_ptr<Particle>>));
    console->debug("<HASH>  * --> size of the space reserved: {} ", space);
    map.reserve(space);
}

int64_t AccelerationMap::get(vec3 vec) {
    console->debug("<HASH> Computing ap, bp, cp and hashes");
    int64_t ap = (int64_t) floor(vec[0]/this->l) * this->p1;
    int64_t bp = (int64_t) floor(vec[1]/this->l) * this->p2;
    int64_t cp = (int64_t) floor(vec[2]/this->l) * this->p3;
    console->debug("<HASH>  * --> ap: {}, bp: {}, cp {} ", ap, bp, cp);
    auto hash = (ap ^ bp ^ cp) % this->n_h;
    console->debug("<HASH>  * --> hash generated: {} ", hash);
    return hash;
}

void AccelerationMap::add(shared_ptr<Particle> ptr) {
    int64_t hash = get(ptr->curr_pos);

    // on recupère l'iterateur sur le pointeur
    unordered_map<int64_t, SetParticle>::iterator got = map.find(hash);
    if (got == map.end()) {
        SetParticle bucket{ ptr };
        map.insert({{hash, bucket}});
    } else {
        SetParticle& bucket = got->second;
        bucket.insert(ptr);
    }
}

void AccelerationMap::remove(shared_ptr<Particle> ptr) {
    int64_t hash = get(ptr->curr_pos);

    // on recupère l'iterateur sur le pointeur
    unordered_map<int64_t, SetParticle>::iterator got = map.find(hash);
    if (got == map.end()) {
        throw std::exception();
    } else {
        SetParticle bucket = got->second;
        bucket.erase(std::find(bucket.begin(), bucket.end(), ptr));
        /*if (bucket.empty())
            map.erase(got);*/
    }
}

Particle AccelerationMap::query(ino64_t hash) {

}
