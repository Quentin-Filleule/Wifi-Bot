#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QtGamepad/QGamepad>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->EcranCam->load(QUrl(QString("http://192.168.1.106:8080/?action=stream")));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_Connexion_clicked()
{
    robot.doConnect();

}

//Appel de la fontion pour realiser la tache lorsque l'on press le bouton
void MainWindow::on_btn_Gauche_pressed()
{
    robot.gauche();
    robot.checkColisionAR();
    robot.checkColisionAV();
}

//le Robot s'arrete lorsque l'on relache le bouton
void MainWindow::on_btn_Gauche_released()
{
    robot.stop();

}

//Appel de la fontion pour realiser la tache lorsque l'on press le bouton
void MainWindow::on_btn_Droite_pressed()
{
    robot.droite();
    robot.checkColisionAR();
    robot.checkColisionAV();
}

//le Robot s'arrete lorsque l'on relache le bouton
void MainWindow::on_btn_Droite_released()
{
    robot.stop();

}


void MainWindow::on_btn_Avant_pressed()
{
    robot.avant();
    robot.checkColisionAV();
}


void MainWindow::on_btn_Avant_released()
{
    robot.stop();
}


void MainWindow::on_btn_Arriere_pressed()
{
    robot.arriere();
    robot.checkColisionAR();

}


void MainWindow::on_btn_Arriere_released()
{
    robot.stop();


}




/*void MainWindow::on_pushButton_6_clicked()
{
    robot.disConnect();

}*/


void MainWindow::on_textBrowser_historyChanged()
{
     robot.afficherBat();
}



/*void MainWindow::on_pushButton_7_clicked()
{
     robot.afficherBat();
}*/



void MainWindow::on_verticalSlider_valueChanged(int value)
{
   robot.setSpeed(value);
   float tmp = ((robot.getSpeed())*0.1872);
   ui->lcdNumber -> display(tmp);


}


void MainWindow::on_btn_CamGauche_clicked()
{

    manager.get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=200")));
}


void MainWindow::on_btn_CamDroite_clicked()
{
    manager.get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-200")));
}


void MainWindow::on_btn_CamHaut_clicked()
{
    manager.get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-200")));

}


void MainWindow::on_btn_CamBas_clicked()
{
    manager.get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=200")));

}


void MainWindow::on_btn_Deconnexion_clicked()
{
    robot.disConnect();
}



void MainWindow::on_manette_clicked()
{


}


void MainWindow::on_capteur_clicked()
{

   unsigned char cpAVG = robot.capateur_AVgauche();
    QString b;
    unsigned char cpAVD = robot.capateur_AVdroit();
     QString a;
    b.setNum(cpAVG);
    ui->textEdit->setText(b);
    b.setNum(cpAVD);
    ui->textEdit->setText(a);

}

