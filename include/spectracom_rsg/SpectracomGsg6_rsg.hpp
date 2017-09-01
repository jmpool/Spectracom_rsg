#ifndef SPECTRACOM_GSG6_RSG_HPP
#define SPECTRACOM_GSG6_RSG_HPP

#include "spectracom/SpectracomGsg6.hpp"
#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "std_msgs/String.h"
#include <string>
#include <stdlib.h>

namespace spectracom {

  class Spectracom_rsg : public Spectracom {
  public:

    Spectracom_rsg() : Spectracom() {}

    bool startScenario(string scenarioName);

    bool waitForScenarioToStart();

    bool sendRsgCommand(float x_pos, float y_pos, float z_pos);

    bool queryPosition();

  };

}

#endif // SPECTRACOM_GSG6_RSG_HPP
