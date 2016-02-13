#include <iostream>

#include "spdlog/spdlog.h"
namespace spd = spdlog;

#include "common/Particle.hh"
#include "structure/AccelerationMap.hh"



using namespace std;
int main() {
    auto console = spd::stdout_logger_mt("console");
    spd::set_level(spd::level::debug);

    console->info("Bienvenu dans PJE SPH");
    AccelerationMap hash1(1, 100);
    Fluid fluid1(1000, 0.1, 0.001, 0.2, 2, 0.1, 0.7);
    shared_ptr<Force> gravity = make_shared<Force>(uniform(Vec3d(0, 0, -9.8)));
    listForces forces{gravity};
    shared_ptr<Particle> p1 = make_shared<Particle>(0.1, fluid1, forces);
    shared_ptr<Particle> p2 = make_shared<Particle>(0.1, fluid1, forces);
    p1->curr_pos = Vec3d(0, 0, 0);
    p2->curr_pos = Vec3d(0.1, 0, 0);
    hash1.add(p1);
    hash1.add(p2);
    // Check if map got the 0 key
    unordered_map<int64_t, set<shared_ptr<Particle>>>::iterator it1 = hash1.map.find(0);
    console->info(it1 != hash1.map.end());
    // Check if the vector in map 0 contains p1 and p2
    set<shared_ptr<Particle>> *s = &it1->second;
    console->info(s->find(p1) != s->end());
    console->info(s->find(p2) != s->end());

}