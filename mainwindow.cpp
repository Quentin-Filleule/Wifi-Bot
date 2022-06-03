#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->load(QUrl(QString("http://192.168.1.106:8080/?action=stream")));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    robot.doConnect();

}

//Appel de la fontion pour realiser la tache lorsque l'on press le bouton
void MainWindow::on_pushButton_2_pressed()
{
    robot.gauche();
}

//le Robot s'arrete lorsque l'on relache le bouton
void MainWindow::on_pushButton_2_released()
{
    robot.stop();
}

//Appel de la fontion pour realiser la tache lorsque l'on press le bouton
void MainWindow::on_pushButton_3_pressed()
{
    robot.droite();
}

//le Robot s'arrete lorsque l'on relache le bouton
void MainWindow::on_pushButton_3_released()
{
    robot.stop();
}


void MainWindow::on_pushButton_4_pressed()
{
    robot.avant();
}


void MainWindow::on_pushButton_4_released()
{
    robot.stop();
}


void MainWindow::on_pushButton_5_pressed()
{
    robot.arriere();

}


void MainWindow::on_pushButton_5_released()
{
    robot.stop();


}




void MainWindow::on_pushButton_6_clicked()
{
    robot.disConnect();

}


void MainWindow::on_textBrowser_historyChanged()
{
     robot.afficherBat();
}



void MainWindow::on_pushButton_7_clicked()
{
     robot.afficherBat();
}



void MainWindow::on_verticalSlider_valueChanged(int value)
{
   robot.setSpeed(value);
   float tmp = ((robot.getSpeed())*0.1872);
   ui->lcdNumber -> display(tmp);


}







void MainWindow::on_pushButton_6_clicked()
{

    manager.get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=200")));
}


void MainWindow::on_pushButton_7_clicked()
{
    manager.get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-200")));
}


void MainWindow::on_pushButton_8_clicked()
{
    manager.get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-200")));

}


void MainWindow::on_pushButton_9_clicked()
{
    manager.get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=200")));

}


void MainWindow::on_pushButton_10_clicked()
{
    robot.disConnect();
}


