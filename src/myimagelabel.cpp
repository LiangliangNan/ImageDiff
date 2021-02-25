#include "myimagelabel.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QImageReader>
#include <QPixmap>
#include <QPainter>
#include <QFileDialog>

void MyImageLabel::updateLabelProperties()
{
    setAcceptDrops(type == MyImageLabelType::Input);
}

MyImageLabel::MyImageLabel(QWidget *parent):
    QLabel(parent)
{
    setMinimumSize(200, 200);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAlignment(Qt::AlignCenter);

    updateLabelProperties();
    clear();
}

void MyImageLabel::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        // One file only
        auto urlList = event->mimeData()->urls();
        if (urlList.size() != 1)
            return;

        // Only images
        auto filePath = urlList[0].toLocalFile();
        auto imageFormat = QImageReader::imageFormat(filePath);
        if (imageFormat.isNull())
            return;

        event->acceptProposedAction();
    }
}

void MyImageLabel::loadImage(QString filePath)
{
    QImageReader imageReader(filePath);
    imageReader.read(&originalImage);
    updatePixmap();

    emit changed();
}

void MyImageLabel::dropEvent(QDropEvent *event)
{
    auto filePath = event->mimeData()->urls()[0].toLocalFile();

    loadImage(filePath);
}


void MyImageLabel::updatePixmap()
{
    if (!originalImage.isNull())
    {
        auto scaledImage = originalImage.scaled(size(), Qt::KeepAspectRatio);
        auto pixmap = QPixmap::fromImage(scaledImage);
        setPixmap(pixmap);
    }
}

void MyImageLabel::resizeEvent(QResizeEvent * /*event*/)
{
    updatePixmap();
}

void MyImageLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (type == MyImageLabelType::Output)
        return;

    auto formats = QImageReader::supportedImageFormats();
    QStringList fileExtension;
    for (auto& format : formats)
    {
        fileExtension.push_back(QString("*.%1").arg(QString(format.toLower())));
    }
    auto fileDialogFilter = QString("Image Files (%1)").arg(fileExtension.join(' '));

    auto fileName = QFileDialog::getOpenFileName(this, "Open Image", QString(), fileDialogFilter);

    if (!fileName.isNull())
        loadImage(fileName);

    event->accept();
}


void MyImageLabel::clear()
{
    setText("Drop image here or double click for file dialog");
}

