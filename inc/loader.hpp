#pragma once
#include "vertex.hpp"
#include <vector>
#include <iostream>

class Loader {
public:
    static MeshData loadOBJ(const std::string& filePath);
};
