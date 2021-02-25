#include "main_window.h"
#include "ui_main_window.h"

#include <math.h>
#include <algorithm>

#include <QImage>
#include <QDebug>
#include <QRgb>


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->image_diff->setType(ImageLabelType::Output);

    connect(ui->image_1, &ImageLabel::changed, this, &MainWindow::onImageChanged);
    connect(ui->image_2, &ImageLabel::changed, this, &MainWindow::onImageChanged);


    auto iml1 = reinterpret_cast<ImageLabel *>(ui->image_1);
    auto iml2 = reinterpret_cast<ImageLabel *>(ui->image_2);

    if (qApp->arguments().size() > 1)
        iml1->loadImage(qApp->arguments()[1]);
    if (qApp->arguments().size() > 2)
        iml2->loadImage(qApp->arguments()[2]);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onImageChanged() {
    auto iml1 = reinterpret_cast<ImageLabel *>(ui->image_1);
    auto iml2 = reinterpret_cast<ImageLabel *>(ui->image_2);
    auto iml_diff = reinterpret_cast<ImageLabel *>(ui->image_diff);

    auto im1 = iml1->getOriginalImage();
    auto im2 = iml2->getOriginalImage();

    if (im1->isNull() || im2->isNull())
        return;

    const auto diffImageSize = QSize(qMax(im1->width(), im2->width()), qMax(im1->height(), im2->height()));

    auto diffImage = QImage(diffImageSize, im1->format());

    bool identicalImages = true;

    for (int x = 0; x < diffImageSize.width(); x++) {
        for (int y = 0; y < diffImageSize.height(); y++) {
            if (im1->width() <= x || im2->width() <= x || im1->height() <= y || im2->height() <= y) {
                diffImage.setPixel(x, y, qRgb(255, 0, 0));
                identicalImages = false;
            } else {
                const QColor ca = im1->pixelColor(x, y);
                const QColor cb = im2->pixelColor(x, y);
                float dr = std::abs(ca.red() - cb.red());
                float dg = std::abs(ca.green() - cb.green());
                float db = std::abs(ca.blue() - cb.blue());
                float diff = sqrt(dr * dr + dg * dg + db * db);
                if (diff >= 100) {
                    diffImage.setPixel(x, y, qRgb(0, 255, 0));
                    identicalImages = false;
                } else {
                    diffImage.setPixel(x, y, im1->pixel(x, y));
                }
            }
        }
    }
    if (identicalImages) {
        ui->image_diff->setText("Images are identical");
    } else {
        iml_diff->setOriginalImage(diffImage);
    }
}

void MainWindow::on_actionExit_triggered() {
    qApp->exit();
}
