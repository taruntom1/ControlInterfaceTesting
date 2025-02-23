
#include <iostream>
#include <unistd.h> // Required for usleep
#include "ControlInterface.hpp"
#include "print.hpp"
#include "ReadJSON.hpp"

int main()
{
    ProtocolConfig config;
    config.portName = "/dev/ttyUSB0";
    ControllerData controllerData;
    ControlInterface controlInterface(config, controllerData);

    controllerData.motorData = new MotorData[2];

    printControllerData(controllerData);

    loadControllerDataFromJson("../controller_data.json", controllerData);
    printControllerData(controllerData);

    while (true)
    {

        int dummy;
        std::cin >> dummy;
        if (controlInterface.Ping())
            std::cout << "Ping send and recieved successfully" << std::endl;
        else
            std::cout << "Ping failed" << std::endl;

        // std::cin >> dummy;
        // if (controlInterface.SetControllerData())
        //	std::cout << "Controller data set successfully" << std::endl;
        // else
        //	std::cout << "Set failed for controller data" << std::endl;

        std::cin >> dummy;
        if (controlInterface.SetControllerProperties())
            std::cout << "Controller properties set successfully" << std::endl;
        else
            std::cout << "set failed failed" << std::endl;

        std::cin >> dummy;
        if (controlInterface.SetMotorData(0))
            std::cout << "Motor data set successfully for motor 0" << std::endl;
        else
            std::cout << "Set failed for motor 0" << std::endl;
        if (controlInterface.SetMotorData(1))
            std::cout << "Motor data set successfully for motor 1" << std::endl;
        else
            std::cout << "Set failed for motor 1" << std::endl;

        std::cin >> dummy;
        if (controlInterface.SetMotorControlMode())
            std::cout << "Motor control mode set successfully" << std::endl;
        else
            std::cout << "Set failed for motor control mode" << std::endl;

        std::cin >> dummy;
        controllerData.motorData[0].pwmValue = 500;
        controllerData.motorData[1].pwmValue = 600;
        controlInterface.SetMotorPWMs();
        std::cout << "PWMs set" << std::endl;

        std::cin >> dummy;
        controllerData.motorData[0].odoBroadcastStatus.angleBroadcast = true;
        controllerData.motorData[0].odoBroadcastStatus.speedBroadcast = false;
        controllerData.motorData[0].odoBroadcastStatus.pwmBroadcast = true;
        controllerData.motorData[1].odoBroadcastStatus.angleBroadcast = true;
        controllerData.motorData[1].odoBroadcastStatus.speedBroadcast = false;
        controllerData.motorData[1].odoBroadcastStatus.pwmBroadcast = true;

        if (controlInterface.SetOdoBroadcastStatus(0))
            std::cout << "Odometer broadcast status set successfully for motor 0" << std::endl;
        else
            std::cout << "Set failed for motor 0" << std::endl;
        if (controlInterface.SetOdoBroadcastStatus(1))
            std::cout << "Odometer broadcast status set successfully for motor 1" << std::endl;
        else
            std::cout << "Set failed for motor 1" << std::endl;

        std::cin >> dummy;

        // char quit = 'a';
        // while (quit != 'q')
        //{
        //	//std::cin >> quit;
        //	controlInterface.Run();
        //	std::cout << "Encoder Count A: " << controllerData.motorData[0].odometryData.angle
        //			  << " Encoder Count B: " << controllerData.motorData[1].odometryData.angle << std::endl;
        // }
        controllerData.motorData[0].odoBroadcastStatus.angleBroadcast = false;
        controllerData.motorData[0].odoBroadcastStatus.speedBroadcast = false;
        controllerData.motorData[0].odoBroadcastStatus.pwmBroadcast = false;
        controllerData.motorData[1].odoBroadcastStatus.angleBroadcast = false;
        controllerData.motorData[1].odoBroadcastStatus.speedBroadcast = false;
        controllerData.motorData[1].odoBroadcastStatus.pwmBroadcast = false;

        if (controlInterface.SetOdoBroadcastStatus(0))
            std::cout << "Odometer broadcast status set successfully for motor 0" << std::endl;
        else
            std::cout << "Set failed for motor 0" << std::endl;
        if (controlInterface.SetOdoBroadcastStatus(1))
            std::cout << "Odometer broadcast status set successfully for motor 1" << std::endl;
        else
            std::cout << "Set failed for motor 1" << std::endl;

        std::cin >> dummy;

        while (true)
        {
            for (int16_t i = 0; i < 1000; i += 50)
            {
                controllerData.motorData[0].pwmValue = i;
                controlInterface.SetMotorPWMs();
                usleep(100000); // usleep takes microseconds
            }
            usleep(1000000);
            for (int16_t i = 1000; i > -1000; i -= 50)
            {
                controllerData.motorData[0].pwmValue = i;
                controlInterface.SetMotorPWMs();
                usleep(100000);
            }
            usleep(1000000);
        }
    }
}
