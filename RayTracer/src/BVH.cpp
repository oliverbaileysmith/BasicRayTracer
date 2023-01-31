#include "BVH.h"
#include <algorithm>

BVHNode::BVHNode(const HittableObjectList &list, double time0, double time1)
	: BVHNode(list.m_HittableObjects, 0, list.m_HittableObjects.size(), time0, time1)
{ }

BVHNode::BVHNode(const std::vector<std::shared_ptr<HittableObject>> &sourceObjects, size_t start, size_t end, double time0, double time1) {
    std::vector<std::shared_ptr<HittableObject>> objects = sourceObjects;

    int axis = randomInt(0, 2);
    auto comparator = (axis == 0) ? boxXCompare : (axis == 1) ? boxYCompare : boxZCompare;

    size_t objectSpan = end - start;

    if (objectSpan == 1) {
        m_Left = m_Right = objects[start];
    } else if (objectSpan == 2) {
        if (comparator(objects[start], objects[start + 1])) {
            m_Left = objects[start];
            m_Right = objects[start + 1];
        } else {
            m_Left = objects[start + 1];
            m_Right = objects[start];
        }
    } else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        auto mid = start + objectSpan / 2;
        m_Left = make_shared<BVHNode>(objects, start, mid, time0, time1);
        m_Right = make_shared<BVHNode>(objects, mid, end, time0, time1);
    }

    AABB boxLeft, boxRight;

    if (!m_Left->buildAABB(time0, time1, boxLeft) || !m_Right->buildAABB(time0, time1, boxRight))
        std::cout << "No bounding box in BVHNode constructor." << std::endl;

    m_AABB = buildSurroundingAABB(boxLeft, boxRight);
}



bool BVHNode::Hit(const Ray &ray, double tMin, double tMax, HitRecord &hitRecord) const {
    if (!m_AABB.Hit(ray, tMin, tMax))
        return false;

    bool hitLeft = m_Left->Hit(ray, tMin, tMax, hitRecord);
    bool hitRight = m_Right->Hit(ray, tMin, hitLeft ? hitRecord.m_T : tMax, hitRecord);

    return hitLeft || hitRight;
}

bool BVHNode::buildAABB(double time0, double time1, AABB &outputAABB) const {
    outputAABB = m_AABB;
    return true;
}