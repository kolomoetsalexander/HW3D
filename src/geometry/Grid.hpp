#pragma once
#include "render/Geometry.hpp"
#include <cstddef>
#include <unordered_map>
#include <utility>
#include <vector>
class Grid {
public:
    explicit Grid(const std::vector<Triangle>& triangles);
    std::vector<std::pair<std::size_t, std::size_t>> candidatePairs() const;
private:
    struct Box{
        glm::vec3 min;
        glm::vec3 max;
    };
    //border boxes for every thiangle (x, y, z)
    struct CellRange{
        int low[3];
        int high[3];
    };
    // coordinates (x, y, z) to uniq key
    long long cellKey(int x, int y, int z) const;
    //every box with id i
    std::vector<Box> boxes;
    //diapazone for AABB
    std::vector<CellRange> ranges;
    //origin of coordinates
    glm::vec3 origin;
    //length of one square box
    float cellSize;
    //quantity for every side (x, y, z)
    int dims[3];
    //from kooridnates to id
    // cell - triangulars' id
    std::unordered_map<long long, std::vector<int>> cells;
};