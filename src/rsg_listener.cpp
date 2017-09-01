#include "spectracom_rsg/SpectracomGsg6_rsg.hpp"

float x_ECEF;
float y_ECEF;
float z_ECEF;

void chatterCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
  x_ECEF = msg->pose.pose.position.x;
  y_ECEF = msg->pose.pose.position.y;
  z_ECEF = msg->pose.pose.position.z;

  ROS_INFO("x[%f] y[%f] z[%f]", x_ECEF, y_ECEF, z_ECEF);

}

// void chatterCallback(const std_msgs::String::ConstPtr& msg)
// {
//   ROS_INFO("I heard: [%s]", msg->data.c_str());
// }

int main(int argc, char **argv)
{

  // string scenarioName = "WoltoszStatic.scen";
  string scenarioName = "blah";

  if(argc < 3) {
      std::cerr << "Usage: sim_controller_example <ip address> <port number>" << std::endl;
      return 0;
  }

  spectracom::Spectracom_rsg * device = new spectracom::Spectracom_rsg;
  
  std::string ip(argv[1]);
  int port=5025;
  istringstream(argv[2]) >> port;



  if (!device->connect(ip,port)) {return -1;}

  string queryString = "SOUR:SCEN:CONT";
  string responseString = "nothing";
  string started = "START\n";

  device->query(queryString, responseString);
  // cout<<responseString<<endl;
  if (responseString.compare(started) != 0)
  {
    device->startScenario(scenarioName);
   // // cout<<"Exited startScenario"<<endl;
    device->waitForScenarioToStart();
  }
  else
  {
    cout<< "Scenario already running"<<endl;
  }
  // Listen to rsg_talker
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/Odometry", 1, chatterCallback);
  // ros::Subscriber sub = n.subscribe("/novatel_front/odom", 1000, chatterCallback);
  // ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
  ros::Rate r(1); // Run at 10 Hz
  while (ros::ok())
  {
    
    ros::spinOnce();
    cout << x_ECEF << endl;
    device->sendRsgCommand(x_ECEF, y_ECEF, z_ECEF);
    device->send("*OPC?");
    // device->commandWaitToContinue();
    device->queryPosition();
    r.sleep();
  }
  
  
  return 0;
}
