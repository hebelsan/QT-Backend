#include "inputthread.h"
#include "../connector/connector.h"
#include "smooththread.h"
#include "turnsignalthread.h"

#include <iostream>
#include <QDebug>
#include <stdio.h>


InputThread::InputThread() {}

void InputThread::run() {
    Connector *creader = Connector::getInstance();

    SmoothThread smoothThread;
    smoothThread.start();



    char buffer[1024]; unsigned int identifier; int value;
    while(1){
        if(fgets(buffer, sizeof(buffer), stdin) == NULL){
            continue;
        }
        if(sscanf(buffer, "? %u %d", &identifier, &value)==2){
            switch(identifier){
            case 0:{
                emit creader->speedFrameReceived(value);
                break;
            }
            case 1:{
                creader->setNewRpm(value);
                break;
            }
            case 2:{
                emit creader->turnSignalLeftFrameReceived();
                break;
            }
            case 3:{
                emit creader->turnSignalRightFrameReceived();
                break;
            }
            case 4:{
                emit creader->dashboardMenuRightFrameReceived();
                emit creader->menuStateFrameReceived();
                break;
            }
            case 5:{
                emit creader->dashboardMenuLeftFrameReceived();
                emit creader->menuStateFrameReceived();
                break;
            }
            case 6:{
                emit creader->dashboardRollerUpFrameReceived();
                break;
            }
            case 7:{
                emit creader->dashboardRollerDownFrameReceived();
                break;
            }
            case 8:{
                emit creader->gearFrameReceived(value);
                break;
            }
            case 9:{
                emit creader->temperatureFrameReceived(value);
                break;
            }
            case 10:{
                emit creader->warningFrameReceived();
                break;
            }
            case 11:{
                emit creader->switchUsbMediaMode();
                break;
//                std::cout << "ID: " << identifier << std::endl;
//                if(!turnSignalState){
//                    turnSignalDirection = "both";
//                    pthread_create(&turnSignal_thread, NULL, turnSignal, NULL);
//                }
//                else if((turnSignalState && turnSignalDirection == "left") || (turnSignalState && turnSignalDirection == "right")){
//                    turnSignalDirection = "both";
//                    pthread_cancel(turnSignal_thread);
//                    emit creader->turnSignalLeftFrameReceived(false);
//                    emit creader->turnSignalRightFrameReceived(false);
//                    pthread_create(&turnSignal_thread, NULL, turnSignal, NULL);
//                }
//                else if(turnSignalState && turnSignalDirection == "both"){
//                    pthread_cancel(turnSignal_thread);
//                    emit creader->turnSignalLeftFrameReceived(false);
//                    emit creader->turnSignalRightFrameReceived(false);
//                    turnSignalState = false;
//                }
                break;
            }
            case 12:{
                emit creader->fuelFrameReceived(value);
                break;
            }
            case 13:{
                emit creader->volumeDownFrameReceived();
                break;
            }
            case 14:{
                emit creader->volumeUpFrameReceived();
                break;
            }
            case 20:{
                // wheel turned left
                if (value < 0) {
                    emit creader->audioWheelTurnedLeft();
                } else {
                    emit creader->audioWheelTurnedRight();
                }
                break;
            }
            case 21:{
                // wheel direction left
                if (value == 7)
                    emit creader -> musicBackwardButtonPressed();
                // wheel direction right
                if (value == 3)
                    emit creader -> musicForwardButtonPressed();
                // wheel direction normal
                if (value == 0)
                    emit creader -> musicWheelDirectionNormal();
                break;
            }
            case 22:{
                // Check if pressed, sonst doppelte auslösung des Buttons
                if(value == 1)
                    emit creader->musicPlayButtonPressed();
                 break;
            }
          }
        }
        else{

            for(int i = 0; buffer[i] != '\n'; i++){
                std::cout << buffer[i];
            }
            std::cout << std::endl;
        }
        usleep(10);
    }
}
