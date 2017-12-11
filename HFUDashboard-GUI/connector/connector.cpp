#include "connector.h"
#include "inputthread.h"

#include <Qt>
#include <QDebug>
#include <QSettings>
#include <QMessageLogger>
#include <QFile>
#include <QDataStream>
#include <QString>

#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <stdio.h>

InputThread inputThread;

bool Connector::instanceflag = false;
Connector* Connector::instance = NULL;

int Connector::rpm = 660;
int Connector::rpm_new = 660;

//------------------------------------------------------------------------------
//functions for testing out some functionality
//such as rpm, turnSignal and menu

//void *Connector::rpm_test(void *){
//    int i = 0;
//    while(1){
//        for(; i <= 6000; i=i+100){
//            usleep(100000);
//            rpm_new = i;
//        }

//        for(; i >= 0; i=i-100){
//            usleep(100000);
//            rpm_new = i;
//        }
//    }
//}

//void Connector::turnSignalTest(std::string direction){
//    pthread_t turnSignal_thread;
//    turnSignalDirection = direction;
//    pthread_create(&turnSignal_thread, NULL, turnSignal, NULL);
//}

//void Connector::menuTest(){
//    Connector *creader = Connector::getInstance();
//    pthread_t menu_thread;
//    emit creader->menuStateFrameReceived(true);
//    pthread_create(&menu_thread, NULL, menu, NULL);
//}

void Connector::setRpm(float rpm){
    rpm_new = rpm;
}

float Connector::getRpm(){
    return rpm;
}

void Connector::setNewRpm(float newRpm){
    rpm_new = newRpm;
}

float Connector::getNewRpm(){
    return rpm_new;
}

//--------------------------------------------------------------------------------

/**
 * @brief Connector::currentDate
 * @return current Date
 *
 * gets the current system time and returns the date
 */
//QString Connector::currentDate() {

//    QDateTime dt = QDateTime::currentDateTime();

//    return dt.toString("dd.MM.yyyy");
//}

/**
 * @brief Connector::currentTime
 * @return current Time
 *
 * gets the current system time and returns the time
 */
//QString Connector::currentTime() {

//    QDateTime dt = QDateTime::currentDateTime();

//    return dt.toString("HH:mm:ss");
//}

/**
 * @brief Connector::time
 * @return
 *
 * sends periodically the current system time and date to the GUI
 */
//void *Connector::time(void *){
//    Connector *creader = Connector::getInstance();

//    while(1){
//        emit creader->dateFrameReceived(currentDate());
//        emit creader->timeFrameReceived(currentTime());
//        usleep(1000000);
//    }
//}

/**
 * @brief Connector::menu
 * @return
 *
 * Waits for 2 seconds and then turns of the menu if not cancelled before
 */
//void *Connector::menu(void *){
//    menuState = true;
//    Connector *creader = Connector::getInstance();

//    usleep(2000000);

//    emit creader->menuStateFrameReceived(false);
//    menuState = false;
//}

/**
 * @brief Connector::turnSignal
 * @return
 *
 * Thread for the Turn Signal
 */
//void *Connector::turnSignal(void *){
//    turnSignalState = true;
//    Connector *creader = Connector::getInstance();

//    if(turnSignalDirection == "left"){
//        for(int i = 0; i < 10; i++){
//            usleep(500000);
//            emit creader->turnSignalLeftFrameReceived(true);
//            usleep(500000);
//            emit creader->turnSignalLeftFrameReceived(false);
//        }
//        turnSignalState = false;
//    }
//    else if(turnSignalDirection == "right"){
//        for(int i = 0; i < 10; i++){
//            usleep(500000);
//            emit creader->turnSignalRightFrameReceived(true);
//            usleep(500000);
//            emit creader->turnSignalRightFrameReceived(false);
//        }
//        turnSignalState = false;
//    }
//    else if(turnSignalDirection == "both"){
//        for(;;){
//            usleep(500000);
//            emit creader->turnSignalRightFrameReceived(true);
//            emit creader->turnSignalLeftFrameReceived(true);
//            usleep(500000);
//            emit creader->turnSignalRightFrameReceived(false);
//            emit creader->turnSignalLeftFrameReceived(false);
//        }
//        turnSignalState = false;
//    }
//}


/**
 * @brief Smoothing of rpm
 * @param id
 * @return
 *
 * rpm is 1/8 of new RPM value and 7/8 of old RPM value
 *
 * Initializes the time Thread
 */
//void *Connector::smooth_rpm(void *){
//    Connector *creader = Connector::getInstance();

//    pthread_t time_thread;
//    pthread_create(&time_thread, NULL, time, NULL);
//    pthread_detach(time_thread);

//    while(1){
//        usleep(50000);
//        rpm = (rpm*7+rpm_new*1)/8;
//        emit creader->rpmFrameReceived(rpm);
//    }
//}

/**
 * @brief input data from Control
 * @param id
 * @return
 *
 * gets the data from the Crontrol class and sends it to the GUI
 *
 * initializes the smoothing thread who intializes the time thread
 *
 * id 0     :   speed
 * id 1     :   rpm
 * id 2     :   turnSignal left
 * id 3     :   turnSignal right
 * id 4     :   menu up
 * id 5     :   menu down
 * id 6     :   left side up (phone)
 * id 7     :   left side down (phone)
 * id 8     :   gear
 * id 9     :   temperature
 * id 10    :   all warnings on
 * id 11    :   turn Signal warning (both on)
 * id 12    :   fuel
 */
void *Connector::input(void *) {
//    Connector *creader = Connector::getInstance();

//    pthread_t smooth_thread;
//    pthread_t turnSignal_thread;
//    pthread_t menu_thread;
//    pthread_create(&smooth_thread, NULL, smooth_rpm, NULL);

//    char buffer[1024]; unsigned int identifier; unsigned int value;
//    while(1){
//        if(fgets(buffer, sizeof(buffer), stdin) == NULL){
//            continue;
//        }
//        if(sscanf(buffer, "? %u %u", &identifier, &value)==2){
//            switch(identifier){

//                case 0:{
//                    emit creader->speedFrameReceived(value);
//                    break;
//                }
//                case 1:{
//                    rpm_new = value;
//                    break;
//                }
//                case 2:{
//                    if(!turnSignalState){
//                        turnSignalDirection = "left";
//                        pthread_create(&turnSignal_thread, NULL, turnSignal, NULL);
//                    }
//                    else if(turnSignalState && turnSignalDirection == "right"){
//                        turnSignalDirection = "left";
//                        pthread_cancel(turnSignal_thread);
//                        emit creader->turnSignalRightFrameReceived();
//                        pthread_create(&turnSignal_thread, NULL, turnSignal, NULL);
//                    }
//                    break;
//                }
//                case 3:{
//                    if(!turnSignalState){
//                        turnSignalDirection = "right";
//                        pthread_create(&turnSignal_thread, NULL, turnSignal, NULL);
//                    }
//                    else if(turnSignalState && turnSignalDirection == "left"){
//                        turnSignalDirection = "right";
//                        pthread_cancel(turnSignal_thread);
//                        emit creader->turnSignalLeftFrameReceived();
//                        pthread_create(&turnSignal_thread, NULL, turnSignal, NULL);
//                    }
//                    break;
//                }
//                case 4:{
//                    if(menuState){
//                        pthread_cancel(menu_thread);
//                        emit creader->dashboardMenuRightFrameReceived();
//                        pthread_create(&menu_thread, NULL, menu, NULL);
//                    }
//                    else{
//                        emit creader->menuStateFrameReceived(true);
//                        emit creader->dashboardMenuRightFrameReceived();
//                        pthread_create(&menu_thread, NULL, menu, NULL);
//                    }
//                    break;
//                }
//                case 5:{
//                    if(menuState){
//                        pthread_cancel(menu_thread);
//                        emit creader->dashboardMenuLeftFrameReceived();
//                        pthread_create(&menu_thread, NULL, menu, NULL);
//                    }
//                    else{
//                        emit creader->menuStateFrameReceived(true);
//                        emit creader->dashboardMenuLeftFrameReceived();
//                        pthread_create(&menu_thread, NULL, menu, NULL);
//                    }
//                    break;
//                }
//                case 6:{
//                    emit creader->dashboardRollerUpFrameReceived();
//                    break;
//                }
//                case 7:{
//                    emit creader->dashboardRollerDownFrameReceived();
//                    break;
//                }
//                case 8:{
//                    emit creader->gearFrameReceived(value);
//                    break;
//                }
//                case 9:{
//                    emit creader->temperatureFrameReceived(value);
//                    break;
//                }
//                case 10:{
//                    emit creader->warningFrameReceived();
//                    break;
//                }
//                case 11:{
//                    std::cout << "ID: " << identifier << std::endl;
//                    if(!turnSignalState){
//                        turnSignalDirection = "both";
//                        pthread_create(&turnSignal_thread, NULL, turnSignal, NULL);
//                    }
//                    else if((turnSignalState && turnSignalDirection == "left") || (turnSignalState && turnSignalDirection == "right")){
//                        turnSignalDirection = "both";
//                        pthread_cancel(turnSignal_thread);
//                        emit creader->turnSignalLeftFrameReceived(false);
//                        emit creader->turnSignalRightFrameReceived(false);
//                        pthread_create(&turnSignal_thread, NULL, turnSignal, NULL);
//                    }
//                    else if(turnSignalState && turnSignalDirection == "both"){
//                        pthread_cancel(turnSignal_thread);
//                        emit creader->turnSignalLeftFrameReceived(false);
//                        emit creader->turnSignalRightFrameReceived(false);
//                        turnSignalState = false;
//                    }
//                    break;
//                }
//                case 12:{
//                    emit creader->fuelFrameReceived(value);
//                    break;
//                }
//            }
//        }
//        else{

//            for(int i = 0; buffer[i] != '\n'; i++){
//                std::cout << buffer[i];
//            }
//            std::cout << std::endl;
//        }
//    }
}

/**
 * @brief Constructor for Connector
 * @param parent
 *
 * Initializes the Thread for the data input from the control class
 *
 * The data input Thread starts the smooth thread and the smooth thread starts the time Thread
 * if created together and simulteanously starting the control/model class they block the getInstance function and the program won't start
 * another way might be a delay after creating the thread, so the threads don't use the getInstance function at the same time
 *
 */
Connector::Connector(QObject *parent) : QObject(parent)
{

    // input thread
//    pthread_t input_thread;
//    pthread_create(&input_thread, NULL, input, NULL);
//    pthread_detach(input_thread);

    // media thread
    inputThread.start();
}

/**
 * @brief Connector::getInstance
 * @return Instance of the Connector Class
 *
 * Singleton Pattern: only one instance of the Connector class can be present
 */
Connector* Connector::getInstance(){

    if(!instanceflag){
        instanceflag = true;
        instance = new Connector();
    }

    return instance;
}
