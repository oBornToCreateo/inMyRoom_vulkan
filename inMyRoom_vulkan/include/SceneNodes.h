#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include "glm/mat4x4.hpp"

#include "misc/memory_allocator.h"
#include "misc/buffer_create_info.h"
#include "wrappers/device.h"
#include "wrappers/buffer.h"

#include "tiny_gltf.h"

#include "NodesMeshes.h"

struct Node
{
    bool isMesh;

    union
    {
        struct
        {
            uint32_t nodeAndChildrenSize;
            uint32_t childrenCount;
        };

        struct
        {
            uint32_t meshIndex;
            uint32_t meshID;
        };
    };

    glm::mat4 globalTRSmatrix;
};

class SceneNodes
{
public:
    SceneNodes(const tinygltf::Model& in_model, const tinygltf::Scene& in_scene, Anvil::BaseDevice* in_device_ptr);
    ~SceneNodes();

    void BindSceneMeshes(NodesMeshes* in_nodesMeshes);
    void Draw(size_t in_primitivesSet_index, Anvil::PrimaryCommandBuffer* in_cmd_buffer_ptr,
              std::vector<Anvil::DescriptorSet*> in_low_descriptor_sets_ptrs);

    Anvil::BufferUniquePtr globalTRSmatrixesBuffer;
    size_t globalTRSmatrixesCount;

private:
    uint32_t AddNode(const tinygltf::Model& in_model, const tinygltf::Node& in_node, glm::mat4 parentTRSmatrix,
                     std::vector<glm::mat4>& meshesByIdTRS);
    Anvil::BufferUniquePtr CreateBufferForTRSmatrixesAndCopy(const std::vector<glm::mat4>& meshesByIdTRS);

    glm::mat4 CreateTRSmatrix(const tinygltf::Node& in_node) const;

    std::vector<Node> nodes;

    NodesMeshes* nodesMeshes_ptr;

    Anvil::BaseDevice* device_ptr;
};
