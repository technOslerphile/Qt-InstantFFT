#include "dialogue.h"
#include "ui_dialogue.h"
#include "QtCore"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv/cv.h>

dialogue::dialogue(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dialogue)
{
    ui->setupUi(this);
    capWebCam.open(0);
    if (capWebCam.isOpened()==false)
    {
        ui->textEdit->append("Error: Can't Open WebCam");
        return;
    }
    tmrTimer = new QTimer(this);
    connect(tmrTimer, SIGNAL(timeout()), this, SLOT(processFrameAndUpdateGUI()));
    tmrTimer->start(20);
}

dialogue::~dialogue()
{
    delete ui;
}

void dialogue::processFrameAndUpdateGUI()
{
    //capWebCam.open(0);
    int height = capWebCam.get(CV_CAP_PROP_FRAME_HEIGHT);
    int width = capWebCam.get(CV_CAP_PROP_FRAME_WIDTH);
    double fps = capWebCam.get(CV_CAP_PROP_FPS);

    QString str2;
    str2.sprintf("Resolution: %d * %d\nFrame Rate:", width, height, fps);
    ui->textEdit->append(str2);



    capWebCam.read(matOriginal);
    if (matOriginal.empty()==true) return;
    cv::cvtColor(matOriginal, matProcessed, CV_BGR2GRAY);
    //for (itrCircles=vecCircles.begin(); itrCircles!=vecCircles.end(); itrCircles++)
    //{
      // ui->textEdit->append(QString("ball position x=")+QString::number((*itrCircles)[0]).rightJustified(4,'')+
            //   QString(", y=")+QString::number((*itrCircles)[1]).rightJustified(4,''));
       cv::cvtColor(matOriginal, matOriginal, CV_BGR2RGB);
       QImage qimgOriginal((uchar*)matOriginal.data, matOriginal.cols, matOriginal.rows, matOriginal.step, QImage::Format_RGB888);
       QImage qimgProcessed((uchar*)matProcessed.data,matProcessed.cols, matProcessed.rows, matProcessed.step, QImage::Format_Indexed8);
       ui->label_3->setPixmap(QPixmap::fromImage(qimgOriginal));
       ui->label->setPixmap(QPixmap::fromImage(qimgProcessed));
    }




void dialogue::on_pushButton_clicked()
{
    if(tmrTimer->isActive()==true)
    {
        tmrTimer->stop();
        ui->pushButton->setText("Resume");
    }
    else
    {
        tmrTimer->start(20);
        ui->pushButton->setText("Pause");

    }
}
