#include <iostream>
#include <cmath>
#include <array>
#include <vector>

struct Vec2 {
    float x, y;

    Vec2 operator+(const Vec2& rhs) const { return { x + rhs.x, y + rhs.y }; }
    Vec2 operator-(const Vec2& rhs) const { return { x - rhs.x, y - rhs.y }; }
    Vec2 operator*(float scalar) const { return { x * scalar, y * scalar }; }

    float dot(const Vec2& rhs) const { return x * rhs.x + y * rhs.y; }
};

struct OBB {
    Vec2 center;
    Vec2 halfExtents;
    float rotationDeg;
    std::array<Vec2, 2> axes;
    std::vector<Vec2> vertices;

    // 초기화 시 회전 축과 꼭짓점 미리 계산
    void initialize() {
        float rad = rotationDeg * (3.142856f / 180.0f);
        float cos_r = std::cos(rad), sin_r = std::sin(rad);

        axes[0] = { cos_r, sin_r };    // x축
        axes[1] = { -sin_r, cos_r };   // y축

        vertices.clear();
        for (int dx : {-1, 1}) 
        {
            for (int dy : {-1, 1}) 
            {

                Vec2 offset = 
                    (axes[0] * (dx * halfExtents.x)) + 
                    (axes[1] * (dy * halfExtents.y));
                vertices.push_back(center + offset);
            }
        }
    }
};

// 축에 투영하여 최소/최대 범위 계산
void project(const std::vector<Vec2>& verts, const Vec2& axis, float& min, float& max) {
    min = max = verts[0].dot(axis);
    for (const Vec2& v : verts) {
        float proj = v.dot(axis);
        if (proj < min) min = proj;
        if (proj > max) max = proj;
    }
}

bool isSeparated(const std::vector<Vec2>& verts1, const std::vector<Vec2>& verts2, const Vec2& axis) {
    float minA, maxA, minB, maxB;
    project(verts1, axis, minA, maxA); //정점별로 축 기준 양끝을 구한다.
    project(verts2, axis, minB, maxB);
    return maxA < minB || maxB < minA;
}

// 충돌 판정 (SAT 기반)
bool checkCollision(OBB& obb1, OBB& obb2) {
    obb1.initialize();
    obb2.initialize();

    for (const Vec2& axis : obb1.axes) { //obb1의 2변의 방향
        if (isSeparated(obb1.vertices, obb2.vertices, axis)) return false;
    }
    for (const Vec2& axis : obb2.axes) { //obb2의 2변의 방향
        if (isSeparated(obb1.vertices, obb2.vertices, axis)) return false;
    }
    return true;
}

int main() {
    OBB obb1{ {0, 0}, {1.7f, 1}, 45 };
    OBB obb2{ {3, 1}, {0.7f, 2}, 50 };

    std::cout << "충돌 여부: " << (checkCollision(obb1, obb2) ? "충돌함" : "충돌하지 않음") << std::endl;
    return 0;
}