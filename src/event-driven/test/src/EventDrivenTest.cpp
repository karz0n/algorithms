#include "CollisionSystem.hpp"

using namespace algorithms;

int
main(int argc, char* argv[])
{
    DrawArea::Ptr area = std::make_shared<CollisionSystem>(5 /* Number of particles */,
                                                           std::numeric_limits<double>::infinity());

    area->setInstance(area);
    area->show(argc, argv);

    return 0;
}
