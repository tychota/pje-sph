#pragma once

#include <unordered_map>
#include <set>
#include <algorithm>
#include <memory>

#include "common/Particle.hpp"
#include "utils/Vec3.hpp"
#include "utils/Prime.hpp"

#include "spdlog/spdlog.h"
namespace spd = spdlog;

using namespace std;
typedef set<shared_ptr<Particle>> SetParticle;

class AccelerationMap {
public:
    AccelerationMap(double l, int64_t n);
    int64_t get(vec3 vec);
    void add(shared_ptr<Particle>  p);
    void remove(shared_ptr<Particle>  p);
    SetParticle query(int64_t hash);
    SetParticle neighbour(shared_ptr<Particle> part, double radius);

    std::unordered_map<int64_t, SetParticle> map;
protected:
    shared_ptr<spdlog::logger> console = spd::get("console");


private:
    double l;
    int64_t n;
    int64_t n_h;
    int64_t p1 = 111;
    int64_t p2 = 19349663;
    int64_t p3 = 83492791;
};
