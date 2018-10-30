#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "camerawindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    CameraWindow camera;

private:
    Ui::MainWindow *ui;

    QString savePath;

private slots:
    void StartCamera();
    void StopCamera();

    void TakePicture();

    void SetSaveLocation();

    void About();
    void Developer();
    void Framework();
};

#endif // MAINWINDOW_H
