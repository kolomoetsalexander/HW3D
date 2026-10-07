#include "Intersection.hpp"
#include <cmath>
#include <algorithm>






// const for pixel
float EPS = 1e-6f;
// вообще необходимо расмотреть случай, когда треугольники лежат в 1 пплоскости в 2D
float cross2(const glm::vec2& a, const glm::vec2& b){
    return a.x * b.y - a.y * b.x;
}

// Пересекаются ли отрезки (p1,p2) и (p3,p4) в 2D (без учёта коллинеарного наложения)
bool segmentsIntersect2D(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, const glm::vec2& p4){
    float d1 = cross2(p4 - p3, p1 - p3);
    float d2 = cross2(p4 - p3, p2 - p3);
    float d3 = cross2(p2 - p1, p3 - p1);
    float d4 = cross2(p2 - p1, p4 - p1);

    bool straddle1 = (d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0);
    bool straddle2 = (d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0);
    return straddle1 && straddle2;
}
// Лежит ли точка p внутри треугольника (a,b,c) в 2D
bool pointInTriangle2D(const glm::vec2& p, const glm::vec2& a, const glm::vec2& b, const glm::vec2& c){
    float d1 = cross2(b - a, p - a);
    float d2 = cross2(c - b, p - b);
    float d3 = cross2(a - c, p - c);
    bool hasNeg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool hasPos = (d1 > 0) || (d2 > 0) || (d3 > 0);
    return !(hasNeg && hasPos);
}

// перевод
glm::vec2 project(const glm::vec3& v, int dropAxis){
    if (dropAxis == 0) 
        return glm::vec2(v.y, v.z);
    if (dropAxis == 1) 
        return glm::vec2(v.x, v.z);
    else
        return glm::vec2(v.x, v.y);
}
// Треугольники копланарны 
bool coplanarTrianglesIntersect(const Triangle& t1, const Triangle& t2, const glm::vec3& normal){
    glm::vec3 absN = glm::abs(normal);
    int dropAxis = 0; // 0=x, 1=y, 2=z
    if (absN.y >= absN.x && absN.y >= absN.z) 
        dropAxis = 1;
    else if (absN.z >= absN.x && absN.z >= absN.y) 
        dropAxis = 2;

    glm::vec2 a0 = project(t1.A, dropAxis), a1 = project(t1.B, dropAxis), a2 = project(t1.C, dropAxis);
    glm::vec2 b0 = project(t2.A, dropAxis), b1 = project(t2.B, dropAxis), b2 = project(t2.C, dropAxis);

    glm::vec2 edgesA[3][2] = { {a0, a1}, {a1, a2}, {a2, a0} };
    glm::vec2 edgesB[3][2] = { {b0, b1}, {b1, b2}, {b2, b0} };

    for (const auto& ea : edgesA)
        for (const auto& eb : edgesB)
            if (segmentsIntersect2D(ea[0], ea[1], eb[0], eb[1]))
                return true;

    // Рёбра не пересекаются — но один треугольник может лежать целиком внутри другого
    if (pointInTriangle2D(a0, b0, b1, b2)) 
        return true;
    if (pointInTriangle2D(b0, a0, a1, a2)) 
        return true;
    else
        return false;
}





// Индекс вершины треугольника, чей знак расстояния до другой плоскости
// отличается от двух остальных ("изолированная" вершина).
// Предполагает, что d0,d1,d2 не все одного знака (иначе early-reject сработал бы раньше).
int isolatedVertex(float d0, float d1, float d2){
    bool s0 = d0 >= 0.0f, s1 = d1 >= 0.0f, s2 = d2 >= 0.0f;
    if (s1 == s2 && s0 != s1) 
        return 0;
    if (s0 == s2 && s1 != s0) 
        return 1;
    else
        return 2;
}


bool trianglesIntersect(const Triangle& t1, const Triangle& t2){
    glm::vec3 N2 = glm::cross(t2.B - t2.A, t2.C - t2.A);
    float d2 = -glm::dot(N2, t2.A);
    float dist0 = glm::dot(N2, t1.A) + d2;
    float dist1 = glm::dot(N2, t1.B) + d2;
    float dist2 = glm::dot(N2, t1.C) + d2;
    if (std::fabs(dist0) < EPS) 
        dist0 = 0.0f;
    if (std::fabs(dist1) < EPS) 
        dist1 = 0.0f;
    if (std::fabs(dist2) < EPS) 
        dist2 = 0.0f;
    if (dist0 != 0.0f && dist1 != 0.0f && dist2 != 0.0f &&
        (dist0 > 0.0f) == (dist1 > 0.0f) && (dist0 > 0.0f) == (dist2 > 0.0f)){
        return false;
    }

    glm::vec3 N1 = glm::cross(t1.B - t1.A, t1.C - t1.A);
    float d1 = -glm::dot(N1, t1.A);
    float ddist0 = glm::dot(N1, t2.A) + d1;
    float ddist1 = glm::dot(N1, t2.B) + d1;
    float ddist2 = glm::dot(N1, t2.C) + d1;
    if (std::fabs(ddist0) < EPS) 
        ddist0 = 0.0f;
    if (std::fabs(ddist1) < EPS) 
        ddist1 = 0.0f;
    if (std::fabs(ddist2) < EPS) 
        ddist2 = 0.0f;
    if (ddist0 != 0.0f && ddist1 != 0.0f && ddist2 != 0.0f &&
        (ddist0 > 0.0f) == (ddist1 > 0.0f) && (ddist0 > 0.0f) == (ddist2 > 0.0f)){
        return false;
    }

    // а если плоскости совпали идем в 2D
    if (dist0 == 0.0f && dist1 == 0.0f && dist2 == 0.0f){
        return coplanarTrianglesIntersect(t1, t2, N2);
    }
    //пересечение плоскостей
    glm::vec3 D = glm::cross(N1, N2);

    //отрезок пересечения плоск
    // 2 - 1
    float dist[3] = { dist0, dist1, dist2 };

    glm::vec3 V[3] = { t1.A, t1.B, t1.C };

    int iso1 = isolatedVertex(dist0, dist1, dist2);
    int a1idx = (iso1 + 1) % 3;
    int b1idx = (iso1 + 2) % 3;
    
    float ta = dist[iso1] / (dist[iso1] - dist[a1idx]);
    glm::vec3 P1 = V[iso1] + ta * (V[a1idx] - V[iso1]);
    float tb = dist[iso1] / (dist[iso1] - dist[b1idx]);
    glm::vec3 P2 = V[iso1] + tb * (V[b1idx] - V[iso1]);

    // 1 - 2
    float ddist[3] = { ddist0, ddist1, ddist2 };
    glm::vec3 U[3] = { t2.A, t2.B, t2.C };
    int iso2 = isolatedVertex(ddist0, ddist1, ddist2);
    int a2idx = (iso2 + 1) % 3;
    int b2idx = (iso2 + 2) % 3;
    float tc = ddist[iso2] / (ddist[iso2] - ddist[a2idx]);
    glm::vec3 Q1 = U[iso2] + tc * (U[a2idx] - U[iso2]);
    float td = ddist[iso2] / (ddist[iso2] - ddist[b2idx]);
    glm::vec3 Q2 = U[iso2] + td * (U[b2idx] - U[iso2]);

    //проецируем на линию пересечения и сравниваем интервалы
    float tP1 = glm::dot(D, P1);
    float tP2 = glm::dot(D, P2);
    float tQ1 = glm::dot(D, Q1);
    float tQ2 = glm::dot(D, Q2);
    float minP = std::min(tP1, tP2), maxP = std::max(tP1, tP2);
    float minQ = std::min(tQ1, tQ2), maxQ = std::max(tQ1, tQ2);

    return minP <= maxQ && minQ <= maxP;
}
