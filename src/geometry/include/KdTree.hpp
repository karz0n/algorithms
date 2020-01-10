#pragma once

#include <tuple>

#include "Point.hpp"

namespace algorithms {

/**
 * Basic canonical k-d tree implementation
 */
class KdTree {
public:
    static const int K = 2; /** The number of dimensions to work with */

public:
    KdTree();

    ~KdTree();

    void
    create(Points points);

    std::tuple<Point, float>
    nearestTo(const Point& point);

    void
    clear();

private:
    /**
     * The list of possible directions of split line according to possible directions.
     */
    enum class Directions {
        vertical,  /// Split line perpendicular to the X axis
        horizontal /// Split line perpendicular to the Y axis
    };

    /**
     * The node data struct.
     */
    struct Node {
        Node()
            : direction{Directions::vertical}
            , value{0.0}
            , lh{nullptr}
            , rh{nullptr}
        {
        }

        Directions direction;
        float value;
        Points points;
        Node* lh;
        Node* rh;
    };

private:
    Node*
    create(Points points, int depth);

    void
    nearestTo(Node* node, const Point& queryPoint, Point& bestPoint, float& bestDistance);

    void
    clear(Node* node);

    static float
    getMedian(const Points& points, Directions direction);

    static Directions
    getDirection(int depth);

    static void
    sortBy(Points& points, Directions direction);

    static std::tuple<Points::const_iterator, Points::const_iterator>
    partitionBy(float median, Points& points, Directions direction);

    void
    findBestPoint(const Point& queryPoint, const Points& points, Point& bestPoint, float& bestDistance);

private:
    Node* _root;
};

} // namespace algorithms
