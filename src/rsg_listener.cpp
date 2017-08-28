#include "spectracom_rsg/SpectracomGsg6_rsg.hpp"

float x_ECEF;
float y_ECEF;
float z_ECEF;

void chatterCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
  x_ECEF = msg->pose.pose.position.x;
  y_ECEF = msg->pose.pose.position.y;
  z_ECEF = msg->pose.pose.position.z;

  ROS_INFO("I heard: x[%f] y[%f] z[%f]", x_ECEF, y_ECEF, z_ECEF);

}

// void chatterCallback(const std_msgs::String::ConstPtr& msg)
// {
//   ROS_INFO("I heard: [%s]", msg->data.c_str());
// }

int main(int argc, char **argv)
{

  string scenarioName = "WoltoszStatic.scen";

  if(argc < 3) {
      std::cerr << "Usage: sim_controller_example <ip address> <port number>" << std::endl;
      return 0;
  }

  spectracom::Spectracom_rsg * device = new spectracom::Spectracom_rsg;
  
  std::string ip(argv[1]);
  int port=5025;
  istringstream(argv[2]) >> port;

  if (!device->connect(ip,port)) {return -1;}

  device->startScenario("name");
 // cout<<"Exited startScenario"<<endl;
  device->waitForScenarioToStart();
  device->sendRsgCommand();
  device->queryPosition();

  // Listen to rsg_talker
  // ros::init(argc, argv, "listener");
  // ros::NodeHandle n;
  // ros::Subscriber sub = n.subscribe("/novatel_front/odom", 1000, chatterCallback);
  // // ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
  // ros::spin();
  
  return 0;
}
