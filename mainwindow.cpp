#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QImage"
#include "QFile"
#include "QPixmap"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString filename =  QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C:\\",
                "Image File(*.jpg);; Image File(*.png);;"
                );
    QFile file = filename;
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0,"Error!",file.errorString());
    }
   QImage Qimg;
   Qimg.load(filename);


   //QImage fitImage = Qimg.scaled(inputWidth.toUInt(),inputHeight.toUInt(), Qt::KeepAspectRatio);
   QImage fitImage;
   fitImage = Qimg.scaled(QSize(ui->sourceImage->width(), ui->sourceImage->height()), Qt::KeepAspectRatio, Qt::SmoothTransformation);
   QPixmap pixmapOrig;
   //pixmapOrig = QPixmap::fromImage(Qimg);
   pixmapOrig = QPixmap::fromImage(fitImage);

   ui->sourceImage->setPixmap(pixmapOrig);
   ui->sourceImage->setMask(pixmapOrig.mask());
   ui->sourceImage->show();
   //OPENCV
   string opencvFileName = filename.toStdString();
   Mat inp = imread(opencvFileName,CV_LOAD_IMAGE_GRAYSCALE);
   Mat out;
   if (inp.empty())
   {
       QMessageBox::information(0,"Error!","Error loading Image in OpenCV");
       return ;
   }
   Mat padded;
   int m = getOptimalDFTSize(inp.rows);
   int n = getOptimalDFTSize(inp.cols);
   copyMakeBorder(inp, padded,0,m-inp.rows,0, n-inp.cols,BORDER_CONSTANT,Scalar::all(0));
   Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
   Mat complexI;
   merge(planes, 2, complexI);
   dft(complexI, complexI);
   //computing magnitude and switch to logarithmic scale
   split(complexI, planes);
   magnitude(planes[0], planes[1], planes[0]);
   Mat magI = planes[0];
   magI += Scalar::all(1);
   log(magI, magI);
   magI = magI(Rect(0,0, magI.cols & -2, magI.rows & -2));
   int cx = magI.cols/2;
   int cy = magI.rows/2;
   Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
   Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
   Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
   Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

   Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
   q0.copyTo(tmp);
   q3.copyTo(q0);
   tmp.copyTo(q3);

   q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
   q2.copyTo(q1);
   tmp.copyTo(q2);

   normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a
                                           // viewable image form (float between values 0 and 1).

   QImage fourier((uchar*)magI.data,magI.cols, magI.rows, magI.step, QImage::Format_RGB32);

   QPixmap pixmapFourier;
   QImage fitFourier;
   fitFourier = fourier.scaled(QSize(ui->fourierImage->width(), ui->fourierImage->height()),Qt::KeepAspectRatio, Qt::SmoothTransformation);
   pixmapFourier = QPixmap::fromImage(fitFourier);
   //pixmapFourier = QPixmap::fromImage(fourier);

   ui->fourierImage->setPixmap(pixmapFourier);
   //cvNamedWindow("Fourier Image",1);
   //imshow("Fourier Image", magI);


   //ui->sourceImage->show();

}
