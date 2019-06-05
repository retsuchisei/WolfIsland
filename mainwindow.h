#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <vector>
#include "field.h"
#include "rabbit.h"
#include "wolf.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *mouseEvent);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QPainter *painter;

    QImage *rabbitImg;
    QImage *wolfImg;
    QImage *island;

    Field * field;
    vector<Wolf> * wolfs;
    vector<Rabbit> * rabbits;

protected:
    void paintEvent(QPaintEvent *);
};

#endif // MAINWINDOW_H
