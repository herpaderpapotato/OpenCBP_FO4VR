#pragma once

#include <vector>
#define _SILENCE_AMP_DEPRECATION_WARNINGS 1
#include "amp.h"
#include <ppl.h>

#include "f4se/GameReferences.h"
#include "Thing.h"
#include "config.h"

#define NINODE_CHILDREN(ninode) ((NiTArray <NiAVObject *> *) ((char*)(&(ninode->m_children))))

class SimObj
{

public:
    enum class Gender
    {
        Male,
        Female,
        Unassigned
    };

    float actorDistSqr;
    concurrency::concurrent_unordered_map<std::string, Thing> things;
    concurrency::concurrent_unordered_map<std::string, Collision> actorColliders;
    concurrency::concurrent_unordered_map<std::string, NiPoint3> NodeCollisionSync;

    SimObj(Actor* actor);
    SimObj() {}
    ~SimObj();
    bool AddBonesToThings(Actor* actor, std::vector<std::string>& boneNames);
    bool Bind(Actor* actor, std::vector<std::string>& boneNames, config_t& config);
    UInt64 GetActorKey();
    Gender GetGender();
    std::string GetRaceEID();
    void Reset();
    void SetActorKey(UInt64 key);
    void Update(Actor* actor, bool collisionsEnabled);
    void Update(Actor* actor);
    bool UpdateConfigs(config_t& config);
    bool IsBound() { return bound; }
private:
    UInt32 id = 0;
    bool bound = false;
    Gender gender;
    std::string raceEid;
    UInt64 currentActorKey;
    
    // Ground Collision Data
    bool GroundCollisionEnabled = false;
    float groundPos = -10000.0f;
};

extern std::vector<std::string> boneNames;