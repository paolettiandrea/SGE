#ifndef SGE_PHYSICSMANAGER_CONSTRUCTIONDATA_HPP
#define SGE_PHYSICSMANAGER_CONSTRUCTIONDATA_HPP
namespace sge::cd {
    struct PhysicsManager_ConstructionData {
        double fixed_delta_time = 1/60.f;
        std::vector<std::string> collision_layer_ids;
    };
}
#endif //SGE_PHYSICSMANAGER_CONSTRUCTIONDATA_HPP
