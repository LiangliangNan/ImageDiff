#ifndef IMAGE_LABEL_H
#define IMAGE_LABEL_H

#include <QLabel>

enum class ImageLabelType {
    Input,
    Output
};

class ImageLabel : public QLabel {
Q_OBJECT
public:
    ImageLabel(QWidget *parent = 0);

    void updatePixmap();

    void setType(ImageLabelType type) {
        this->type = type;
        updateLabelProperties();
    }

    void updateLabelProperties();

    const QImage *getOriginalImage() const { return &originalImage; }

    void setOriginalImage(QImage image) {
        originalImage = image;
        updatePixmap();
    }

    void loadImage(QString filePath);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;

    void dropEvent(QDropEvent *event) override;

    void resizeEvent(QResizeEvent *) override;

    void mouseDoubleClickEvent(QMouseEvent *event) override;

public slots:

    void clear();

signals:

    void changed();

private:
    QImage originalImage;
    ImageLabelType type = ImageLabelType::Input;
};

#endif // IMAGE_LABEL_H
