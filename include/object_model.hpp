#pragma once

// C headers
#include <cstdio>

// C++ headers
#include <stdexcept>
#include <vector>

// Load object headers
#include "tiny_obj_loader.h"

// Local headers
#include "scene_object.hpp"
#include "matrices.h"
#include "globals.hpp"


class ObjectModel{
    public:
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    ObjectModel(const char* filename, const char* basepath = NULL, bool triangulate = true);
    void BuildTrianglesAndAddToVirtualScene();
    void ComputeNormals();
    void PrintObjModelInfo();

    private:

};

void DrawVirtualObject(const char* object_name);
