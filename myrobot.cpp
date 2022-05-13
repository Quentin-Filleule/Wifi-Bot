// myrobot.cpp

#include "myrobot.h"

MyRobot::MyRobot(QObject *parent) : QObject(parent) {
       DataToSend[0] = 0xFF;
       DataToSend[1] = 0x07;
       DataToSend[2] = 0x0;
       DataToSend[3] = 0x0;
       DataToSend[4] = 0x0;
       DataToSend[5] = 0x0;
       DataToSend[6] = 0x0;
       DataToSend[7] = 0x0;
       DataToSend[8] = 0x0;
    DataReceived.resize(21);
    TimerEnvoi = new QTimer();
    // setup signal and slot
    connect(TimerEnvoi, SIGNAL(timeout()), this, SLOT(MyTimerSlot())); //Send data to wifibot timer
}


void MyRobot::doConnect() {
    socket = new QTcpSocket(this); // socket creation
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    qDebug() << "connecting..."; // this is not blocking call
    //socket->connectToHost("LOCALHOST", 15020);
    socket->connectToHost("192.168.1.106", 15020); // connection to wifibot
    // we need to wait...
    if(!socket->waitForConnected(5000)) {
        qDebug() << "Error: " << socket->errorString();
        return;
    }
    TimerEnvoi->start(75);

}

void MyRobot::disConnect() {
    TimerEnvoi->stop();
    socket->close();
}

void MyRobot::connected() {
    qDebug() << "connected..."; // Hey server, tell me about you.
}

void MyRobot::disconnected() {
    qDebug() << "disconnected...";
}

void MyRobot::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}

void MyRobot::readyRead() {
    qDebug() << "reading..."; // read the data from the socket
    DataReceived = socket->readAll();
    emit updateUI(DataReceived);
    qDebug() << DataReceived[0] << DataReceived[1] << DataReceived[2];
}

void MyRobot::MyTimerSlot() {
    qDebug() << "Timer...";
    while(Mutex.tryLock());
    socket->write(DataToSend);
    Mutex.unlock();
}

short MyRobot::Crc16()
{

//passage de datatosend(QByteArray) en data(char)
unsigned char *data =(unsigned char*)DataToSend.constData();

unsigned int Crc = 0xFFFF;
unsigned int Polynome = 0xA001;
unsigned int CptOctet = 0;
unsigned int CptBit = 0;
unsigned int Parity= 0;
 Crc = 0xFFFF;
 Polynome = 0xA001;

 //boucle de 1 à 6 car on ne doit pas commencer à 255
for ( CptOctet= 1 ; CptOctet < 7
      ; CptOctet++)
 {
 Crc ^= *(data + CptOctet);
 for ( CptBit = 0; CptBit <= 7 ; CptBit++)
 {
 Parity= Crc;
 Crc >>= 1;
 if (Parity%2 == true) Crc ^= Polynome;
 }
 }
return(Crc);
}




void MyRobot::gauche(){
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 200;
    DataToSend[3] = 0x0;
    DataToSend[4] = 200;
    DataToSend[5] = 0x0;
    //changement les roues droite vont en avant (16) et les roues gauche en arriere(0).
    DataToSend[6] = 16;//(0+0+0+16)
    short mycrc = Crc16();
    DataToSend[7] = mycrc;
    DataToSend[8] = mycrc >> 8;
}

void MyRobot::droite(){
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 200;
    DataToSend[3] = 0x0;
    DataToSend[4] = 200;
    DataToSend[5] = 0x0;
    //changement les roues droite vont en arriere (0) et les roues gauche en avant(64).
    DataToSend[6] = 64;//(0+64+0+0)
    short mycrc = Crc16();
    DataToSend[7] = mycrc;
    DataToSend[8] = mycrc >> 8;
}

void MyRobot::avant(){
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 200;
    DataToSend[3] = 0x0;
    DataToSend[4] = 200;
    DataToSend[5] = 0x0;
    //changement les roues droite vont en avant (16) et les roues gauche en avant(64).
    DataToSend[6] = 80;//(0+64+0+16)
    short mycrc = Crc16();
    DataToSend[7] = mycrc;
    DataToSend[8] = mycrc >> 8;
}

void MyRobot::arriere(){
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 200;
    DataToSend[3] = 0x0;
    DataToSend[4] = 200;
    DataToSend[5] = 0x0;
    //changement les roues droite vont en arriere (0) et les roues gauche en arriere(0).
    DataToSend[6] = 0;//(0+0+0+0)
    short mycrc = Crc16();
    DataToSend[7] = mycrc;
    DataToSend[8] = mycrc >> 8;
}


void MyRobot::stop(){
    //on réinitialise les paramètres de base du constructeur pour que les roues ne tournent plus
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0x0;
    DataToSend[3] = 0x0;
    DataToSend[4] = 0x0;
    DataToSend[5] = 0x0;
    DataToSend[6] = 0x0;
    DataToSend[7] = 0x0;
    DataToSend[8] = 0x0;
}
