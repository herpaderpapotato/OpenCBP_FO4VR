#pragma once
#include <f4se/NiObjects.h>
#include <f4se/NiTypes.h>
#include <f4se/GameReferences.h>
#include <time.h>
#include "CollisionHub.h"
#include "config.h"
#include <shared_mutex>

//using std::shared_mutex;

typedef concurrency::concurrent_unordered_map<const char*, concurrency::concurrent_unordered_map<UInt32, NiPoint3>> pos_map;
typedef concurrency::concurrent_unordered_map<const char*, concurrency::concurrent_unordered_map<UInt32, NiMatrix43>> rot_map;

inline void RefreshNode(NiAVObject* node)
{
    if (node == nullptr || node->m_name == nullptr)
        return;

    NiAVObject::NiUpdateData npd;
    npd.unk00 = nullptr;
    npd.pCamera = nullptr;
    npd.flags = 0;
    npd.unk14 = 0;
    npd.unk18 = 0;
    npd.unk20 = 0;
    npd.unk28 = 0;
    npd.unk30 = 0;
    npd.unk38 = 0;
    node->UpdateWorldData(&npd);
}

class Thing
{
    NiPoint3 oldWorldPos;
    NiPoint3 oldWorldPosRot;
    //NiPoint3 oldLocalDiff;
    float oldRotZ;
    NiPoint3 velocity;
    clock_t time;
    NiAVObject* thingObj;
    bool IsBreastBone;
    NiMatrix43 firstWorldRot;
    NiMatrix43 origWorldRot;
    bool rightSide;
    Actor* m_actor;

public:
    BSFixedString boneName;
    bool isEnabled;

    float stiffness = 0.5f;
    float stiffness2 = 0.0f;
    float damping = 0.2f;
    float maxOffsetX = 5.0f;
    float maxOffsetY = 5.0f;
    float maxOffsetZ = 5.0f;
    float cogOffsetX = 0.0f;
    float cogOffsetY = 0.0f;
    float cogOffsetZ = 0.0f;

    float gravityBias = 0.0f;
    float gravityCorrection = 0.0f;
    float timeTick = 4.0f;
    float linearX = 0.0f;
    float linearY = 0.0f;
    float linearZ = 0.0f;
    float rotationalX = 0.0f;
    float rotationalY = 0.0f;
    float rotationalZ = 0.0f;

    float rotateLinearX = 0.0f;
    float rotateLinearY = 0.0f;
    float rotateLinearZ = 0.0f;

    float rotateRotationX = 0.0f;
    float rotateRotationY = 0.0f;
    float rotateRotationZ = 0.0f;

    float scaleMultiplierX = 1.0f;
    float scaleMultiplierY = 1.0f;
    float scaleMultiplierZ = 1.0f;

    float posOffsetX = 0.0f;
    float posOffsetY = 0.0f;

    float timeStep = 0.016f;

    bool absRotX = 0;

    float linearSpreadforceXtoY = 0.0f;
    float linearSpreadforceXtoZ = 0.0f;
    float linearSpreadforceYtoX = 0.0f;
    float linearSpreadforceYtoZ = 0.0f;
    float linearSpreadforceZtoX = 0.0f;
    float linearSpreadforceZtoY = 0.0f;

    float gravitySupineX = 0.0f;
    float gravitySupineY = 0.0f;
    float gravitySupineZ = 0.0f;
    
    float collisionFriction = 0.02f;
    float collisionPenetration = 1.0f;
    float collisionMultipler = 1.0f;
    float collisionMultiplerRot = 1.0f;

    bool collisionElastic = false;
    bool collisionElasticConstraints = false;

    static pos_map origLocalPos;
    static rot_map origLocalRot;
    static rot_map origChestWorldRot;

    // Maps are sorted every edit time, so if it is parallel processing then a high probability of overloading
    //static shared_mutex thing_map_lock;

    Thing(NiAVObject* obj, BSFixedString& name, Actor* actor);
    ~Thing();

    NiAVObject* IsThingActorValid(Actor* actor);
    void Reset(Actor* actor);
    NiPoint3 CalculateGravitySupine(Actor* actor);
    void StoreOriginalTransforms(Actor* actor);
    void UpdateThing(Actor* actor);
    void UpdateConfig(configEntry_t& centry);

    void ShowPos(NiPoint3& p);
    void ShowRot(NiMatrix43& r);

    int skipFramesCount = 0;

    bool ActorCollisionsEnabled = true;
    bool GroundCollisionEnabled = true;
    bool VirtualCollisionEnabled = false;

	bool collisionOnLastFrame = false;

    std::vector<std::string> IgnoredCollidersList;
    std::vector<std::string> IgnoredSelfCollidersList;
    bool IgnoreAllSelfColliders = false;

	NiPoint3 lastColliderPosition = NiPoint3(0, 0, 0);

	std::vector<Sphere> thingCollisionSpheres;
    std::vector<Capsule> thingCollisionCapsules;

	std::vector<Collision> ownColliders;


    std::vector<Sphere> CreateThingCollisionSpheres(Actor* actor, std::string nodeName);
    std::vector<Capsule> CreateThingCollisionCapsules(Actor* actor, std::string nodeName);


    static inline bool ContainsNoCase(std::string str, std::string ministr)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        std::transform(ministr.begin(), ministr.end(), ministr.begin(), ::tolower);

        if (str.find(ministr) != std::string::npos)
        {
            return true;
        }
        else
            return false;
    }
    
    static float remap(float value, float start1, float stop1, float start2, float stop2)
    {
        return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
    }

    //Extra variables
    float groundPos = -10000.0f;
    NiPoint3 collisionBuffer = emptyPoint;
    NiPoint3 collisionSync = emptyPoint;
    NiPoint3 collisionInertia = emptyPoint;
    NiPoint3 collisionInertiaRot = emptyPoint;
    float multiplerInertia = 0.0f;
    float multiplerInertiaRot = 0.0f;
    CollisionConfigs CollisionConfig;

};