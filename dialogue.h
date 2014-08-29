#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <QMainWindow>
#include <QDialog>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>


namespace Ui {
class dialogue;
}

class dialogue : public QMainWindow
{
    Q_OBJECT

public:
    explicit dialogue(QWidget *parent = 0);
    ~dialogue();

private slots:
    void on_pushButton_clicked();

private:
    Ui::dialogue *ui;
    cv::VideoCapture capWebCam;
    cv::Mat matOriginal;
    cv::Mat matProcessed;
    QImage qimgOriginal;
    QImage qimgProcessed;
    std::vector<cv::Vec3f> vecCircles;
    std::vector<cv::Vec3f> itrCircles;
    QTimer* tmrTimer;
public slots:
    void processFrameAndUpdateGUI();
};

#endif // DIALOGUE_H
