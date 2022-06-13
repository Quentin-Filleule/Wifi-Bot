#ifndef MYROBOT_H
#define MYROBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>
#include <QWebEngineView>

//capteur 3/4/11/12

class MyRobot : public QObject {
    Q_OBJECT
public:
    explicit MyRobot(QObject *parent = 0);
    void doConnect();
    void disConnect();
    QByteArray DataToSend;
    QByteArray DataReceived;
    QMutex Mutex;
    short Crc16();
    int speed;
signals:
    void updateUI(const QByteArray Data);
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void MyTimerSlot();
    //fonctions de deplacement:
    void gauche();
    void droite();
    void avant();
    void arriere();
    //fonction pour arreter le robot
    void stop();

    void afficherBat();
    //getter et setter de Speed
    void setSpeed(int _speed);
    int getSpeed();

    void video();

    //information capteur
    unsigned char capateur_AVgauche();
    unsigned char capateur_AVdroit();


    void checkColisionAV();
    void checkColisionAR();


private:
    QTcpSocket *socket;
    QTimer *TimerEnvoi;
};

#endif // MYROBOT_H
