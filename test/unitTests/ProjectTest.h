#ifndef PROJECTTEST_H
#define PROJECTTEST_H

#include "catch.hpp"
#include "../../src/OpenSidescan/project.h"


TEST_CASE("Test read Project") {

    Project * project = new Project();

    std::string filename = "../data/projects/TestProject5Files.ssp";

    std::cout << "Reading project: " << filename << std::endl;
    std::cout << "This takes a while." << std::endl;

    project->read(filename);

    REQUIRE(project->getFiles().size() == 5);
}

TEST_CASE("Test set and get lever arm Project") {

    Project * project = new Project();

    Eigen::Vector3d leverArm;
    leverArm << 1.0, 2.0, 3.0;

    project->setAntenna2TowPointLeverArm(leverArm);

    double eps = 1e-9;
    REQUIRE(std::abs(project->getAntenna2TowPointLeverArm()[0] - leverArm[0]) < eps);
    REQUIRE(std::abs(project->getAntenna2TowPointLeverArm()[1] - leverArm[1]) < eps);
    REQUIRE(std::abs(project->getAntenna2TowPointLeverArm()[2] - leverArm[2]) < eps);
}

#endif // PROJECTTEST_H
