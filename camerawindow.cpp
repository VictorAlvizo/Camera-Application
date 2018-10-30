#include "camerawindow.h"
#include "ui_camerawindow.h"

CameraWindow::CameraWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraWindow)
{
    ui->setupUi(this);
    SetupCamera(); //Set everthing needed for camera including getting the camera
}

CameraWindow::~CameraWindow()
{
    delete ui;
}

void CameraWindow::SetupCamera(){
    QList<QCameraInfo> cameraList = QCameraInfo::availableCameras();

    if(cameraList.count() <= 0){ //If there is no camera available send error message and return
        QMessageBox::critical(this, "Camera Error", "No camera has been found");
        return;
    }

    camera = new QCamera(cameraList[0]);
}

bool CameraWindow::StartFeed(){
    if(camera == nullptr){ //Null camera means there was no camera found
        QMessageBox::critical(this, "Error", "No camera detected");
        return false;
    }

    videoFeed = new QCameraViewfinder;
    camera->setViewfinder(videoFeed); //Configure the camera and viewfinder.
    videoFeed->resize(350, 350);

    videoFeed->show();
    camera->start();

    return true;
}

void CameraWindow::CaptureImage(QString filePath){
    QCameraImageCapture imageCapture(camera); //Datatype needed to save image
    QImageEncoderSettings imageSettings;

    imageSettings.setCodec("image/jpeg"); //Section sets the settings for the saving of the image
    imageSettings.setQuality(QMultimedia::HighQuality);
    imageSettings.setResolution(500, 500);

    imageCapture.setEncodingSettings(imageSettings); //Set the settings for saving
    camera->setCaptureMode(QCamera::CaptureStillImage);

    camera->searchAndLock(); //Focus and lock camera from other use
    imageCapture.capture(filePath); //Take the image and save it in the wanted file path
    camera->unlock(); //Unlock the camera so other applications can use it

    QMessageBox::information(this, "Image Saved", "Image has been captured and saved");
}

void CameraWindow::StopFeed(){ //Shut off camera and viewfinder widget
    videoFeed->hide();
    camera->stop();
}
