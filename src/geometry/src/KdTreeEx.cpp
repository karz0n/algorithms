#include "KdTreeEx.hpp"

#include <queue>
#include <stack>
#include <set>

#include <Sequence.hpp>
#include <Select.hpp>

namespace algorithms {

KdTreeEx::KdTreeEx()
    : _root{nullptr}
{
}

KdTreeEx::~KdTreeEx()
{
    clear();
}

void
KdTreeEx::create(Points points)
{
    using Handle = std::tuple<int, Points, Node*>;

    if (!empty()) {
        clear();
    }
    _root = new Node;

    const std::size_t leafSize = std::max<std::size_t>(points.size() / 1000, 1);
    std::queue<Handle> handles;
    handles.emplace(0, std::move(points), _root);
    while (!handles.empty()) {
        auto& [depth, points, node] = handles.front();

        // Get direction of split line
        const auto direction = getDirection(depth);

        if (points.size() <= leafSize) {
            node->direction = direction;
            node->points = std::move(points);
            handles.pop();
            continue;
        }

        // Get split value (median)
        const auto median = getMedian(points, direction);

        // Partition sequence using split value
        const auto [lit, git] = partitionBy(median, points, direction);
        Points lt(points.begin(), lit); // Points which are located on the left side of split line
        Points eq(lit, git);            // Points which lie on split line
        Points gt(git, points.end());   // Points which are located on the right side of split line

        node->direction = direction;
        node->value = median;
        node->points = std::move(eq);

        if (!lt.empty()) {
            node->lh = new Node;
            handles.emplace(depth + 1, std::move(lt), node->lh);
        }

        if (!gt.empty()) {
            node->rh = new Node;
            handles.emplace(depth + 1, std::move(gt), node->rh);
        }

        handles.pop();
    }
}

KdTreeEx::BestPointAndDistance
KdTreeEx::nearestTo(const Point& queryPoint)
{
    Point bestPoint;
    float bestDistance = std::numeric_limits<float>::max();

    std::stack<Node*> nodes;
    nodes.push(_root);

    std::set<Node*> visited;
    while (!nodes.empty()) {
        Node* node = nodes.top();
        nodes.pop();
        if (!node) {
            continue;
        }

        if (visited.count(node) > 0) {
            continue;
        }
        visited.insert(node);

        findBestPoint(queryPoint, node->points, bestPoint, bestDistance);
        if (!node->lh && !node->rh) {
            // Leaf case
            continue;
        }

        const float value = (node->direction == Directions::vertical) ? queryPoint.x : queryPoint.y;

        const bool leftFirst = (value <= node->value);
        if (leftFirst) {
            if (value - bestDistance <= node->value) {
                nodes.push(node->lh);
            }
            if (value + bestDistance > node->value) {
                nodes.push(node->rh);
            }
        }
        else {
            if (value + bestDistance > node->value) {
                nodes.push(node->rh);
            }
            if (value - bestDistance <= node->value) {
                nodes.push(node->lh);
            }
        }
    }

    return std::make_tuple(bestPoint, bestDistance);
}

void
KdTreeEx::clear()
{
    clear(_root);
}

bool
KdTreeEx::empty() const
{
    return !_root;
}

void
KdTreeEx::clear(Node* node)
{
    if (!node) {
        return;
    }

    clear(node->lh);
    clear(node->rh);

    delete node;
}

float
KdTreeEx::getMedian(Points points, KdTreeEx::Directions direction)
{
    const auto comparator = [direction](const Point& p1, const Point& p2) {
        return (direction == Directions::vertical) ? p1.x < p2.x : p1.y < p2.y;
    };

    const std::size_t count = points.size();
    const bool isOdd = (count % 2);
    if (isOdd) {
        /* Median equals of middle value of sequence */
        const std::size_t index = (count + 1) / 2;
        auto point = Select::get<Point>(points.begin(), points.end(), comparator, index - 1);
        return (direction == Directions::vertical) ? point.x : point.y;
    }
    else {
        /* Median equals of average value of two middle elements of sequence */
        const std::size_t index1 = (count / 2);
        const std::size_t index2 = (count + 2) / 2;
        auto point1 = Select::get<Point>(points.begin(), points.end(), comparator, index1 - 1);
        auto point2 = Select::get<Point>(points.begin(), points.end(), comparator, index2 - 1);
        return (direction == Directions::vertical) ? (point1.x + point2.x) / 2
                                                   : (point1.y + point2.y) / 2;
    }
}

KdTreeEx::Directions
KdTreeEx::getDirection(int depth)
{
    return (depth % K) ? Directions::horizontal : Directions::vertical;
}

std::tuple<Points::iterator, Points::iterator>
KdTreeEx::partitionBy(float median, Points& points, Directions direction)
{
    return Sequence::partition(points.begin(), points.end(), [&](const Point& p) -> int {
        auto v = (direction == Directions::vertical) ? p.x : p.y;
        return (v > median) ? +1 : (v < median) ? -1 : 0;
    });
}

void
KdTreeEx::findBestPoint(const Point& queryPoint,
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
