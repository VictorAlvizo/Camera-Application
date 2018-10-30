#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("CamCam");
    ui->saveEdit->setReadOnly(true);

    connect(ui->startButton, SIGNAL(released()), this, SLOT(StartCamera())); //Section for buttons
    connect(ui->stopButton, SIGNAL(released()), this, SLOT(StopCamera()));
    connect(ui->pictureButton, SIGNAL(released()), this, SLOT(TakePicture()));
    connect(ui->changeButton, SIGNAL(released()), this, SLOT(SetSaveLocation()));

    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(About())); //Section for QActions
    connect(ui->actionCredit, SIGNAL(triggered()), this, SLOT(Developer()));
    connect(ui->actionFramework, SIGNAL(triggered()), this, SLOT(Framework()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::StartCamera(){
    if(camera.StartFeed()){ //Camera feed works, disable/enable certin buttons
        ui->startButton->setEnabled(false);
        ui->stopButton->setEnabled(true);
        ui->pictureButton->setEnabled(true);
    }
}

void MainWindow::StopCamera(){
    camera.StopFeed(); //Stop video finder

    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
    ui->pictureButton->setEnabled(false);
}

void MainWindow::TakePicture(){
    if(savePath.isEmpty()){
        QMessageBox::critical(this, "No Save Path", "You must first designate a file path before taking an image");
        return;
    }

    camera.CaptureImage(savePath);

    QPixmap thumbnail(savePath + ".jpg"); //Get image of last picture
    ui->lastImage->setPixmap(thumbnail.scaled(ui->lastImage->width(), ui->lastImage->height(), Qt::KeepAspectRatio));
}

void MainWindow::SetSaveLocation(){
    savePath = QFileDialog::getSaveFileName(this, "Choose Location"); //Get future location to save path
    ui->saveEdit->setText(savePath); //Put file path to editline
}

void MainWindow::About(){
    QMessageBox::information(this, "About", "Simple image capturing software which is easy to use.");
}

void MainWindow::Developer(){
    QMessageBox::information(this, "Developer", "This software was created by Victor Alvizo");
}

void MainWindow::Framework(){
    QMessageBox::aboutQt(this, "Qt Framework");
}
