#include "structure/AccelerationMap.hpp"

AccelerationMap::AccelerationMap(double l, int64_t n): l(l) {
    Prime primegen;
    n_h = primegen.next(2 * n);
}

int64_t AccelerationMap::get(vec v) {
    int64_t ap = (int64_t) floor(v[0]/this->l) * this->p1;
    int64_t bp = (int64_t) floor(v[1]/this->l) * this->p2;
    int64_t cp = (int64_t) floor(v[2]/this->l) * this->p3;
    auto hash = (ap ^ bp ^ cp) % this->n_h;
    return hash;
}

void AccelerationMap::add(Particle& part) {
    int64_t hash = get(part.curr_pos);

    // on recupère l'iterateur sur le pointeur
    unordered_map<int64_t, ListParticle>::iterator got = _map.find(hash);
    if (got == _map.end()) {
        ListParticle bucket{ part };
        _map.insert({{hash, bucket}});
    } else {
        ListParticle& bucket = got->second;
        bucket.insert(part);
    }
}

void AccelerationMap::remove(Particle& part) {
    int64_t hash = get(part.curr_pos);

    // on recupère l'iterateur sur le pointeur
    unordered_map<int64_t, ListParticle>::iterator got = _map.find(hash);
    if (got == _map.end()) {
        throw std::exception();
    } else {
        ListParticle bucket = got->second;
        bucket.erase(std::find(bucket.begin(), bucket.end(), part));
    }
}

ListParticle AccelerationMap::query(int64_t hash) {
    unordered_map<int64_t, ListParticle>::iterator got = _map.find(hash);
    if (got == _map.end()) {
        return ListParticle();
    } else {
        return got->second;
    }
}

ListParticle AccelerationMap::neighbour(shared_ptr<Particle> part) {
    ListParticle neighbour;
    double radius = l;

    for (double i=-radius; i <= radius; i += l) {
        for (double j=-radius; j <= radius; j += l) {
            for (double k=-radius; k <= radius; k += l) {
                VEC v1 = {i, j, k};
                int64_t hash(AccelerationMap::get(v1));
                ListParticle bucket= query(hash);
                for (auto& p: bucket) {
                    if (norm(p.curr_pos - part->curr_pos) < radius && !(*part == p)) {
                        shared_ptr<Particle> ptr = make_shared<Particle>(p);
                        neighbour.insert(p);
                    }
                }
            }
        }
    }

    return neighbour;
}
