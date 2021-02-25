#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>

enum class MyImageLabelType {
    Input,
    Output
};

class MyImageLabel : public QLabel
{
    Q_OBJECT
public:
    MyImageLabel(QWidget *parent = 0);

    void updatePixmap();

    void setType(MyImageLabelType type) { this->type = type; updateLabelProperties(); }

    void updateLabelProperties();

    const QImage* getOriginalImage() const { return &originalImage; }
    void setOriginalImage(QImage image) { originalImage = image; updatePixmap(); }

    void loadImage(QString filePath);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

    void resizeEvent(QResizeEvent*) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;

public slots:
    void clear();

signals:
    void changed();

private:
    QImage originalImage;
    MyImageLabelType type = MyImageLabelType::Input;
};

#endif // IMAGELABEL_H
