#ifndef CAMERAWINDOW_H
#define CAMERAWINDOW_H

#include <QWidget>
#include <QCamera>
#include <QCameraInfo> //Used to get camera also include other camera information
#include <QCameraViewfinder> //Used for video feed/Video widget
#include <QCameraImageCapture> //Contains datatype to save image
#include <QImageEncoderSettings> //Format in which image will be saved
#include <QMessageBox>
#include <QFileDialog>

namespace Ui {
class CameraWindow;
}

class CameraWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CameraWindow(QWidget *parent = nullptr);
    ~CameraWindow();

    bool StartFeed(); //Start viewfinder widget

    void CaptureImage(QString filePath); //Take photo
    void StopFeed(); //Shut camera off and viewfinder

private:
    Ui::CameraWindow *ui;

    void SetupCamera();

    QCamera * camera;

    QCameraViewfinder * videoFeed;
};

#endif // CAMERAWINDOW_H
