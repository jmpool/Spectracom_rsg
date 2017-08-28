#include "spectracom_rsg/SpectracomGsg6_rsg.hpp"

namespace spectracom {

  
  bool Spectracom_rsg::startScenario(string scenarioName)
  {
    // cout<<"Entered startScenario"<<endl;
    Spectracom::commandLoadScenario(scenarioName);
    // Set Parameters
    // device->commandTransmitPower(-130);
    // device->commandCarrierToNoise(50);
    // Start scenario
    Spectracom::commandStartScenario();
    return true;
  }

  bool Spectracom_rsg::waitForScenarioToStart()
  {
    cout<<"Entered waitForScenarioToStart"<<endl;
    string queryString = "SOUR:SCEN:CONT";
    string responseString = "nothing";
    string started = "START\n";

    while(responseString.compare(started) != 0)
    {
      sleep(1);
      Spectracom::query(queryString, responseString);
      // cout<<"Got query response: "<<responseString;
    }
    
    cout<<"Scenario started successfully!"<<endl;
    return true;
  }



  bool Spectracom_rsg::sendRsgCommand()
  {
    string rsgCommand = "SOUR:SCEN:ECEFPOS IMM,1000.0,2000.0,3000.0";
    Spectracom::send(rsgCommand);
    Spectracom::commandWaitToContinue();
    cout<<"Sent: "<<rsgCommand<<endl;
    return true;
  }



  bool Spectracom_rsg::queryPosition()
  {
    string queryString = "SOUR:SCEN:ECEFPOS";
    string responseString;
    Spectracom::query(queryString, responseString);
    cout<<"Received: "<<responseString;
    return true;
  }

  

}