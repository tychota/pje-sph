#pragma once

#include <unordered_map>
#include <set>
#include <algorithm>
#include <memory>

#include "common/particle.hh"
#include "utils/vec3.hh"
#include "utils/prime.hh"

#include "spdlog/spdlog.h"
namespace spd = spdlog;

typedef std::set<std::shared_ptr<Particle>> SetParticle;

using namespace std;
class ProximityHash {
public:
    ProximityHash(double l, int64_t n);
    int64_t get(Vec3d vec);
    void add(shared_ptr<Particle>  p);
    void remove(shared_ptr<Particle>  p);
    Particle query(ino64_t hash);
    std::unordered_map<int64_t, SetParticle> map;

protected:
    std::shared_ptr<spdlog::logger> console = spd::get("console");

private:
    double l;
    int64_t n;
    int64_t n_h;
    int64_t p1 = 111;
    int64_t p2 = 19349663;
    int64_t p3 = 83492791;
};
