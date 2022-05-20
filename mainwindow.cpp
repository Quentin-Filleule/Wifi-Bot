#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

