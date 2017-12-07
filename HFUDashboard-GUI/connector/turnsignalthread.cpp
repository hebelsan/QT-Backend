#include "turnsignalthread.h"
#include "connector.h"

TurnSignalThread::TurnSignalThread() {}

void TurnSignalThread::run() {
    Connector *creader = Connector::getInstance();
    creader->setTurnSignalState(true);

    if(creader->getTurnSignalDirection() == "left"){
        for(int i = 0; i < 10; i++){
            usleep(500000);
            emit creader->turnSignalLeftFrameReceived(true);
            usleep(500000);
            emit creader->turnSignalLeftFrameReceived(false);
        }
        creader->setTurnSignalState(false);
    }
    else if(creader->getTurnSignalDirection() == "right"){
        for(int i = 0; i < 10; i++){
            usleep(500000);
            emit creader->turnSignalRightFrameReceived(true);
            usleep(500000);
            emit creader->turnSignalRightFrameReceived(false);
        }
        creader->setTurnSignalState(false);
    }
    else if(creader->getTurnSignalDirection() == "both"){
        for(;;){
            usleep(500000);
            emit creader->turnSignalRightFrameReceived(true);
            emit creader->turnSignalLeftFrameReceived(true);
            usleep(500000);
            emit creader->turnSignalRightFrameReceived(false);
            emit creader->turnSignalLeftFrameReceived(false);
        }
        creader->setTurnSignalState(false);
    }
}

