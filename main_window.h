#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

protected slots:

    void onImageChanged();

private slots:

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAIN_WINDOW_H
