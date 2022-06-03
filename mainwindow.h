#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <myrobot.h>
#include <QEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_Connexion_clicked();

    void on_btn_Gauche_pressed();

    void on_btn_Gauche_released();

    void on_btn_Droite_pressed();

    void on_btn_Droite_released();

    void on_btn_Avant_pressed();

    void on_btn_Avant_released();

    void on_btn_Arriere_pressed();

    void on_btn_Arriere_released();
    void on_btn_CamGauche_clicked();


    void on_textBrowser_historyChanged();

    void on_btn_CamDroite_clicked();


    void on_verticalSlider_valueChanged(int value);


    void on_btn_CamHaut_clicked();

    void on_btn_CamBas_clicked();

    void on_btn_Deconnexion_clicked();

private:
    Ui::MainWindow *ui;
    MyRobot robot;

    QNetworkAccessManager manager;
};
#endif // MAINWINDOW_H
