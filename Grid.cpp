#include "Grid.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
//const for AABB borders
const float GRID_EPS = 1e-5f;
//max cell quantity
const int MAX_DIM = 128;

long long Grid::cellKey(int x, int y, int z) const{
    //key = (idx*qy + idy)*qz + idz
    //idx - cell id by x
    //qy - cell quantity by y
    return (static_cast<long long>(x) * dims[1] + y) * dims[2] + z;
}
//make spatial grid and distribute triangulars
Grid::Grid(const std::vector<Triangle>& triangles) : origin(0.0f), cellSize(1.0f){
    dims[0] = 1;
    dims[1] = 1;
    dims[2] = 1;
    const std::size_t n = triangles.size();
    //if there no triangulars
    if (n == 0){
        return;
    }
// AABB for every triangule
    boxes.resize(n);
    glm::vec3 sceneMin(std::numeric_limits<float>::infinity());
    glm::vec3 sceneMax(-std::numeric_limits<float>::infinity());
    float sumSize = 0.0f;
    for (std::size_t i = 0; i < n; i++){
        const Triangle& t = triangles[i];
        boxes[i].min = glm::min(glm::min(t.A, t.B), t.C) - glm::vec3(GRID_EPS);
        boxes[i].max = glm::max(glm::max(t.A, t.B), t.C) + glm::vec3(GRID_EPS);
        sceneMin = glm::min(sceneMin, boxes[i].min);
        sceneMax = glm::max(sceneMax, boxes[i].max);
        glm::vec3 extent = boxes[i].max - boxes[i].min;
        float maxSize = std::max(extent.x, std::max(extent.y, extent.z));
        sumSize += maxSize;
    }
//cell and grid sizes
    origin = sceneMin;
    glm::vec3 sceneExtent = sceneMax - sceneMin;
    float maxExtent = std::max(sceneExtent.x, std::max(sceneExtent.y, sceneExtent.z));
    float averageSize = sumSize / static_cast<float>(n);
    cellSize = std::max(averageSize, maxExtent / MAX_DIM);
    for (int axis = 0; axis < 3; axis++){
        dims[axis] = std::min(MAX_DIM, static_cast<int>(sceneExtent[axis] / cellSize) + 1);
    }
//cells for every triangualar
    ranges.resize(n);
    for (std::size_t i = 0; i < n; i++){
        CellRange& range = ranges[i];
        for (int axis = 0; axis < 3; axis++){
            int low = static_cast<int>((boxes[i].min[axis] - origin[axis]) / cellSize);
            int high = static_cast<int>((boxes[i].max[axis] - origin[axis]) / cellSize);
            range.low[axis] = std::clamp(low, 0, dims[axis] - 1);
            range.high[axis] = std::clamp(high, 0, dims[axis] - 1);
        }
        for (int x = range.low[0]; x <= range.high[0]; x++){
            for (int y = range.low[1]; y <= range.high[1]; y++){
                for (int z = range.low[2]; z <= range.high[2]; z++){
                    cells[cellKey(x, y, z)].push_back(static_cast<int>(i));
                }
            }
        }
    }
}
//pairs of candidates
std::vector<std::pair<std::size_t, std::size_t>> Grid::candidatePairs() const{
    std::vector<std::pair<std::size_t, std::size_t>> result;
    //all no empty
    for (const auto& cell : cells){
        const std::vector<int>& ids = cell.second;
        //restore cell coordinate by key
        long long key = cell.first;
        int x = static_cast<int>(key % dims[2]);
        key /= dims[2];
        int y = static_cast<int>(key % dims[1]);
        int z = static_cast<int>(key / dims[1]);
        //all pairs in cell
        for (std::size_t p = 0; p < ids.size(); p++){
            for (std::size_t q = p + 1; q < ids.size(); q++){
                int i = ids[p];
                int j = ids[q];
                bool isReferenceCell = true;
                int cellCoordinates[3] = {x, y, z};
                for (int axis = 0; axis < 3; axis++){
                    int firstCommonCell = std::max(ranges[i].low[axis], ranges[j].low[axis]);

                    if (cellCoordinates[axis] != firstCommonCell){
                        isReferenceCell = false;
                        break;
                    }
                }
                // in another cell not check pair
                if (!isReferenceCell){
                    continue;
                }
                //is AABB 
                const Box& a = boxes[i];
                const Box& b = boxes[j];

                if (a.min.x > b.max.x || b.min.x > a.max.x || a.min.y > b.max.y || b.min.y > a.max.y ||
                    a.min.z > b.max.z || b.min.z > a.max.z){
                    continue;
                }
                //save pair i < j
                result.emplace_back(static_cast<std::size_t>(std::min(i, j)), static_cast<std::size_t>(std::max(i, j)));
            }
        }
    }
    return result;
}