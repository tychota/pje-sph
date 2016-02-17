#pragma once

#include <unordered_map>
#include <set>
#include <algorithm>
#include <memory>

#include "utils/macros.hpp"
#include "utils/Prime.hpp"
#include "sph/Particle.hpp"

#include "spdlog/spdlog.h"
namespace spd = spdlog;

using namespace std;

typedef set<Particle> ListParticle;
typedef pair<int64_t, ListParticle> ListParticlePair;
typedef unordered_map<int64_t, ListParticle> ListParticleMap;


class AccelerationMap {
public:
    AccelerationMap(double l, int64_t n);
    int64_t get(vec v);
    void add(Particle& part);
    void remove(Particle& part);
    ListParticle query(int64_t hash);
    ListParticle neighbour(shared_ptr<Particle> part);

    std::unordered_map<int64_t, ListParticle> _map;
protected:
    shared_ptr<spdlog::logger> console = spd::get("console");

private:
    double l;
    int64_t n_h;
    int64_t p1 = 111;
    int64_t p2 = 19349663;
    int64_t p3 = 83492791;
};
