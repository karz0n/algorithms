#include "KdTree.hpp"

#include <algorithm>

#include <ThreeWayQuick.hpp>

namespace algorithms {

KdTree::KdTree()
    : _root{nullptr}
{
}

KdTree::~KdTree()
{
    clear();
}

void
KdTree::create(Points points)
{
    if (!empty()) {
        clear();
    }
    _root = create(std::move(points), 0 /* Start from vertical splitting */);
}

KdTree::BestPointAndDistance
KdTree::nearestTo(const Point& queryPoint)
{
    Point bestPoint;
    float bestDistance{std::numeric_limits<float>::max()};
    nearestTo(_root, queryPoint, bestPoint, bestDistance);
    return std::make_tuple(bestPoint, bestDistance);
}

void
KdTree::clear()
{
    clear(_root);
}

bool
KdTree::empty() const
{
    return !_root;
}

void
KdTree::nearestTo(Node* node, const Point& queryPoint, Point& bestPoint, float& bestDistance)
{
    if (!node) {
        return;
    }

    findBestPoint(queryPoint, node->points, bestPoint, bestDistance);

    const float value = (node->direction == Directions::vertical) ? queryPoint.x : queryPoint.y;

    const bool isLeftFirst = (value <= node->value);
    if (isLeftFirst) {
        if (value - bestDistance <= node->value) {
            nearestTo(node->lh, queryPoint, bestPoint, bestDistance);
        }
        if (value + bestDistance > node->value) {
            nearestTo(node->rh, queryPoint, bestPoint, bestDistance);
        }
    }
    else {
        if (value + bestDistance > node->value) {
            nearestTo(node->rh, queryPoint, bestPoint, bestDistance);
        }
        if (value - bestDistance <= node->value) {
            nearestTo(node->lh, queryPoint, bestPoint, bestDistance);
        }
    }
}

void
KdTree::clear(Node* node)
{
    if (!node) {
        return;
    }

    clear(node->lh);
    clear(node->rh);

    delete node;
}

KdTree::Node*
KdTree::create(Points points, int depth)
{
    if (points.empty()) {
        return nullptr;
    }

    // Get direction of split line
    const auto direction = getDirection(depth);

    if (points.size() == 1 /* Leaf case */) {
        Node* node = new Node;
        node->direction = direction;
        node->value = (direction == Directions::vertical) ? points[0].x : points[0].y;
        node->points = std::move(points);
        return node;
    }

    // Sort all points (needed to get split value)
    sortBy(points, direction);

    // Get split value (median)
    const auto median = getMedian(points, direction);

    // Partition sorted sequence using split value
    const auto [lit, git] = partitionBy(median, points, direction);
    Points lt(points.cbegin(), lit); // Points which are located on the left side of split line
    Points eq(lit, git);             // Points which lie on split line
    Points gt(git, points.cend());   // Points which are located on the right side of split line

    Node* node = new Node;
    node->direction = direction;
    node->value = median;
    node->points = std::move(eq);
    node->lh = create(std::move(lt), depth + 1 /* Round robin of direction */);
    node->rh = create(std::move(gt), depth + 1 /* Round robin of direction */);
    return node;
}

float
KdTree::getMedian(const Points& points, Directions direction)
{
    const std::size_t count = points.size();
    const bool isOdd = (count % 2);
    if (isOdd) {
        /* Median equals of middle value of sequence */
        const std::size_t index = (count + 1) / 2;
        return (direction == Directions::vertical) ? points[index - 1].x : points[index - 1].y;
    }
    else {
        /* Median equals of average value of two middle elements of sequence */
        const std::size_t index1 = (count / 2);
        const std::size_t index2 = (count + 2) / 2;
        return (direction == Directions::vertical)
                   ? (points[index1 - 1].x + points[index2 - 1].x) / 2
                   : (points[index1 - 1].y + points[index2 - 1].y) / 2;
    }
}

KdTree::Directions
KdTree::getDirection(int depth)
{
    return (depth % K) ? Directions::horizontal : Directions::vertical;
}

void
KdTree::sortBy(Points& points, Directions direction)
{
    if (direction == Directions::vertical) {
        ThreeWayQuick::sort(points.begin(), points.end(), [](const Point& lh, const Point& rh) {
            return lh.x < rh.x;
        });
    }
    else {
        ThreeWayQuick::sort(points.begin(), points.end(), [](const Point& lh, const Point& rh) {
            return lh.y < rh.y;
        });
    }
}

std::tuple<Points::const_iterator, Points::const_iterator>
KdTree::partitionBy(float median, Points& points, Directions direction)
{
    /** Find first greater or equal element than given median value */
    const auto lit = std::find_if(points.cbegin(), points.cend(), [&](const Point& p) {
        return (direction == Directions::vertical) ? p.x >= median : p.y >= median;
    });

    /** Find first greater element than given median value */
    const auto git = std::find_if(lit, points.cend(), [&](const Point& p) {
        return (direction == Directions::vertical) ? p.x > median : p.y > median;
    });

    return std::make_tuple(lit, git);
}

void
KdTree::findBestPoint(const Point& queryPoint,
                      const Points& points,
                      Point& bestPoint,
                      float& bestDistance)
{
    for (const auto& p : points) {
        float d = getDistance(queryPoint, p);
        if (d < bestDistance) {
            bestDistance = d;
            bestPoint = p;
        }
    }
}
} // namespace algorithms
