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

void AccelerationMap::add(shared_ptr<Particle> part) {
    int64_t hash = get(part->curr_pos);

    // on recupère l'iterateur sur le pointeur
    unordered_map<int64_t, SetParticle>::iterator got = map.find(hash);
    if (got == map.end()) {
        SetParticle bucket{ part };
        map.insert({{hash, bucket}});
    } else {
        SetParticle& bucket = got->second;
        bucket.insert(part);
    }
}

void AccelerationMap::remove(shared_ptr<Particle> part) {
    int64_t hash = get(part->curr_pos);

    // on recupère l'iterateur sur le pointeur
    unordered_map<int64_t, SetParticle>::iterator got = map.find(hash);
    if (got == map.end()) {
        throw std::exception();
    } else {
        SetParticle bucket = got->second;
        bucket.erase(std::find(bucket.begin(), bucket.end(), part));
        /*if (bucket.empty())
            map.erase(got);*/
    }
}

SetParticle AccelerationMap::query(int64_t hash) {
    unordered_map<int64_t, SetParticle>::iterator got = map.find(hash);
    if (got == map.end()) {
        return SetParticle();
    } else {
        return got->second;
    }
}

SetParticle AccelerationMap::neighbour(shared_ptr<Particle> part, double radius) {
    SetParticle neighbour;
    vec3 pos = part->curr_pos;
    for (int i = pos(0) - radius; i <= pos(0) + radius; i += l) {
        for (int j = pos(1) - radius; j <= pos(1) + radius; j += l) {
            for (int k = pos(0) - radius; k <= pos(0) + radius; k += l) {
                vec3 p = {(double)i, (double)j, (double)k};
                int64_t hash = get(p);
                SetParticle candidates = query(hash);
                for (auto i: candidates) {
                    if (norm(pos - i->curr_pos) <= radius) {
                        neighbour.insert(i);
                    }
                }
            }
        }
    }

    return neighbour;
}
