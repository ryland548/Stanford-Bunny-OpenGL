#include "../inc/loader.hpp"
#include <glad/glad.h>
#include "tiny_obj_loader.h"

MeshData Loader::loadOBJ(const std::string& filePath) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    bool success = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filePath.c_str());
    if (!warn.empty()) {
        std::cout << "Loader warning " << warn << '\n';
    }
    if (!success) {
        std::cout << "Loader Error " << err << '\n';
    }

    MeshData mesh;
    GLuint vertexCounter = 0;

    for (const auto& shape : shapes) {
        size_t indexOffset = 0;

        for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); ++f) {
            size_t fv = shape.mesh.num_face_vertices[f];

            for (size_t v = 0; v < fv; ++v) {
                tinyobj::index_t idx = shape.mesh.indices[indexOffset + v];
                Vertex vertex{};

                vertex.pos.x = attrib.vertices[3 * idx.vertex_index + 0];
                vertex.pos.y = attrib.vertices[3 * idx.vertex_index + 1];
                vertex.pos.z = attrib.vertices[3 * idx.vertex_index + 2];

                if (idx.normal_index >= 0) {
                    vertex.normal.x = attrib.normals[3 * idx.normal_index + 0];
                    vertex.normal.y = attrib.normals[3 * idx.normal_index + 1];
                    vertex.normal.z = attrib.normals[3 * idx.normal_index + 2];
                } else {
                    tinyobj::index_t idx0 = shape.mesh.indices[indexOffset + 0];
                    tinyobj::index_t idx1 = shape.mesh.indices[indexOffset + 1];
                    tinyobj::index_t idx2 = shape.mesh.indices[indexOffset + 2];

                    glm::vec3 p0(attrib.vertices[3 * idx0.vertex_index + 0], attrib.vertices[3 * idx0.vertex_index + 1], attrib.vertices[3 * idx0.vertex_index + 2]);
                    glm::vec3 p1(attrib.vertices[3 * idx1.vertex_index + 0], attrib.vertices[3 * idx1.vertex_index + 1], attrib.vertices[3 * idx1.vertex_index + 2]);
                    glm::vec3 p2(attrib.vertices[3 * idx2.vertex_index + 0], attrib.vertices[3 * idx2.vertex_index + 1], attrib.vertices[3 * idx2.vertex_index + 2]);

                    glm::vec3 edge1 = p1 - p0;
                    glm::vec3 edge2 = p2 - p0;
                    vertex.normal = glm::normalize(glm::cross(edge1, edge2));
                }

                if (idx.texcoord_index >= 0) {
                    vertex.texCoords.x = attrib.texcoords[2 * idx.texcoord_index + 0];
                    vertex.texCoords.y = attrib.texcoords[2 * idx.texcoord_index + 1];
                } else {
                    vertex.texCoords = glm::vec2(0.0f, 0.0f);
                }

                mesh.vertices.push_back(vertex);
                mesh.indices.push_back(vertexCounter++);
            }
            indexOffset += fv;
        }
    }
    return mesh;
}
