#pragma once

#include <unordered_map>
#include <vector>
#include <vector>
#include <memory>

#include "common/particle.hh"
#include "utils/vec3.hh"
#include "utils/prime.hh"

typedef std::vector<std::shared_ptr<particle>> listParticle;

using namespace std;
class proximityHash {
public:
    proximityHash(double l, int64_t n);
    int64_t get(vec3d vec);
    void add(particle p);
    void remove(particle p);
    particle query(ino64_t hash);

    std::unordered_map<int64_t, listParticle> map;

private:
    double l;
    int64_t n;
    int64_t n_h;
    int64_t p1 = 111;
    int64_t p2 = 19349663;
    int64_t p3 = 83492791;

};
