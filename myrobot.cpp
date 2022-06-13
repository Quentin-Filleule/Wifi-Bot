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
    odometrieL();
    odometrieR();

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
    DataToSend[2] = speed;
    DataToSend[3] = 0x0;
    DataToSend[4] = speed;
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
    DataToSend[2] = speed;
    DataToSend[3] = 0x0;
    DataToSend[4] = speed;
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
    DataToSend[2] = speed;
    DataToSend[3] = 0x0;
    DataToSend[4] = speed;
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
    DataToSend[2] = speed;
    DataToSend[3] = 0x0;
    DataToSend[4] = speed;
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

//setter pour modifier la vitesse avec
void MyRobot::setSpeed(int _speed){
speed = _speed;
}

int MyRobot::getSpeed(){
return speed;}

 void MyRobot::afficherBat(){
     qDebug()<< "coucou" << DataReceived[2]  << "coucou";
 }


void MyRobot::video()
{



}

unsigned char MyRobot::capateur_AVgauche()
{
    unsigned char cp = DataReceived[3];         //11 et 3 avnt
    qDebug() << "capteur :  " << cp;
    return cp;
}

unsigned char MyRobot::capateur_AVdroit()
{
    unsigned char cp = DataReceived[11];         //11 et 3 avnt
    qDebug() << "capteur :  " << cp;
    return cp;
}


void MyRobot::checkColisionAV()
{
    unsigned char cpAVG = DataReceived[3];
    unsigned char cpAVD = DataReceived[11];

    if(cpAVD >100 || cpAVG >100)          //PBM AVG
    {
        stop();
    }

}

void MyRobot::checkColisionAR()
{
    //unsigned char cpARD = DataReceived[12];       capteur casser arriere droit
    unsigned char cpARG = DataReceived[4];

    if(cpARG >100)          //PBM AVG
    {
        stop();
    }

}

long MyRobot::odometrieL()
{

    long odo1 = DataReceived[8] << 24;
    long odo2 = DataReceived[7] << 16;
    long odo3 = DataReceived[6] << 8;
    long odo4 = DataReceived[5];

    long odo = odo1 + odo2 + odo3 + odo4;

    qDebug() << "odoL = "<<odo;

    return odo;


}

long MyRobot::odometrieR()
{

    long odo1 = DataReceived[16] << 24;
    long odo2 = DataReceived[15] << 16;
    long odo3 = DataReceived[14] << 8;
    long odo4 = DataReceived[13];

    long odo = odo1 + odo2 + odo3 + odo4;

    qDebug() << "odoR = "<<odo;

    return odo;


}

void MyRobot::diagonaldroite(bool sens){
     DataToSend.resize(9);
     DataToSend[0] = 0xFF;
     DataToSend[1] = 0x07;
     //roue gauche
     DataToSend[2] = (speed*240)/200;
     DataToSend[3] = 0x0;
     //roue droite
     DataToSend[4] = (speed*240)/400;
     DataToSend[5] = 0x0;
     if(sens==true){
        DataToSend[6] = 80;//(0+64+0+16)
     }
     else
         DataToSend[6] = 0;//(0+64+0+16)
     short mycrc = Crc16();
     DataToSend[7] = mycrc;
     DataToSend[8] = mycrc >> 8;
 }

 void MyRobot::diagonalgauche(bool sens){
     DataToSend.resize(9);
     DataToSend[0] = 0xFF;
     DataToSend[1] = 0x07;
     //roue gauche
     DataToSend[2] = (speed*240)/400;
     DataToSend[3] = 0x0;
     //roue droite
     DataToSend[4] = (speed*240)/200;
     DataToSend[5] = 0x0;
     if(sens==true){
        DataToSend[6] = 80;//(0+64+0+16)
     }
     else
         DataToSend[6] = 0;//(0+64+0+16)
     short mycrc = Crc16();
     DataToSend[7] = mycrc;
     DataToSend[8] = mycrc >> 8;
 }





