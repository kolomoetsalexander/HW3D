#pragma once
#include "Geometry.hpp"
#include <cstddef>
#include <unordered_map>
#include <utility>
#include <vector>
class Grid {
public:
    explicit Grid(const std::vector<Triangle>& triangles);
    std::vector<std::pair<std::size_t, std::size_t>>
    candidatePairs() const;
private:
    struct Box {
        glm::vec3 min;
        glm::vec3 max;
    };
    struct CellRange {
        int low[3];
        int high[3];
    };
    // coordinates to uniq key
    long long cellKey(int x, int y, int z) const;
    //AABB of all
    std::vector<Box> boxes;
    //diapazone for AABB
    std::vector<CellRange> ranges;
    glm::vec3 origin;
    float cellSize;
    //quantity for every side
    int dims[3];
    // cell - triangulars' id
    std::unordered_map<long long, std::vector<int>> cells;
};