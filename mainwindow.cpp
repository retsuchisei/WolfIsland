#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "field.h"
#include "rabbit.h"
#include "wolf.h"
#include <vector>
#include <qmath.h>
#include <QDateTime>
#include <QImage>
#include <QtGui>
#include <QDebug>
#include <QPainter>
#include <QString>
#include <QPaintEvent>
#include <QMouseEvent>
#include <exception>

#define PLATZ_COUNT 20


void start(Field * field, std::vector<Wolf> * wolfs, std::vector<Rabbit> * rabbits) {
    int x, y;
    qsrand(QDateTime::currentMSecsSinceEpoch());
    for (int i = 0; i < 3; ++i) {
        do {
            x = qrand() % 20;
            y = qrand() % 20;
        } while (field->get_animal(x, y) != 0);
        (*wolfs).push_back(Wolf(x, y));
        field->set_animal(x, y, 1);
    }
    for (int i = 0; i < 3; ++i) {
        do {
            x = qrand() % 20;
            y = qrand() % 20;
        } while (field->get_animal(x, y) != 0);
        rabbits->push_back(Rabbit(x, y));
        field->set_animal(x, y, 2);
    }
}

void move_rabbits(Field * field, vector<Rabbit> * rabbits) {
    qDebug() << "move rabbits" << ' ' << rabbits->empty();
    int size = rabbits->size();
    qDebug() << size << " RABBITS";
    for (int i = 0; i < size; ++i) {
        (*rabbits)[i].move(field, rabbits);
    }
}

void move_wolfs(Field * field, vector<Wolf> * wolfs, vector<Rabbit> * rabbits) {
    int size = wolfs->size();
    for (int i = 0; i < size; ++i) {
        (*wolfs)[i].move(field, wolfs, rabbits, (wolfs->begin() + i));
    }
}


void MainWindow::paintEvent(QPaintEvent *) {
    painter->begin(this);
    painter->drawImage(0, 0, *island);
    for (int i = 0; i < PLATZ_COUNT; ++i) {
        for (int j = 0; j < PLATZ_COUNT; ++j) {
            if (field->get_animal(i, j) == 1 || field->get_animal(i, j) == 3)
                painter->drawImage(i * 32 + 50, j * 32 + 50, *wolfImg);
            else if (field->get_animal(i, j) == 2) {
                painter->drawImage(i * 32 + 50, j * 32 + 50, *rabbitImg);
            }
        }
    }
    painter->end();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    painter = new QPainter(this);

    wolfImg = new QImage(":/resources/img/wolf.png");
    rabbitImg = new QImage(":/resources/img/rabbit.png");
    island = new QImage(":/resources/img/island.png");
    ui->gridLayout->setGeometry(QRect(0, 0, island->width(), island->height()));

    field = new Field();
    wolfs = new vector<Wolf>();
    rabbits = new vector<Rabbit>();
    //start(field, wolfs, rabbits);
    qreal width = 550.0;
    qreal height = 550.0;
    /*for (int i = 0; i < PLATZ_COUNT; ++i) {
        animals.push_back(vector<AnimalRect*>());
        for (int j = 0; j < PLATZ_COUNT; ++j) {
            AnimalRect * animal = new AnimalRect(0, 0, width / PLATZ_COUNT, height / PLATZ_COUNT, field->get_animal(i, j));
            animal->setPos(i * width / PLATZ_COUNT, j * height / PLATZ_COUNT);
            animals[i].push_back(animal);
        }
    }*/

}

MainWindow::~MainWindow()
{
    delete ui;
    delete painter;
    delete field;
    delete wolfs;
    delete rabbits;

    delete wolfImg;
    delete rabbitImg;
    delete island;
}

void MainWindow::mousePressEvent(QMouseEvent *mouseEvent) {
    if (mouseEvent->button() == Qt::LeftButton) {
        float x = (mouseEvent->x() - 50) / 32;
        float y = (mouseEvent->y() - 50) / 32;
        if (x > 19 || y > 19)
            return;
        if (wolfs->size() < 3) {
            wolfs->push_back(Wolf(x, y));
            field->set_animal(x, y, (*wolfs)[wolfs->size() - 1].get_gender() ? 1 : 3);

        } else if (rabbits->size() < 3) {
            rabbits->push_back(Rabbit(x, y));
            field->set_animal(x, y, 2);
        }

    }
    update();
}


void MainWindow::on_pushButton_clicked()
{
    qDebug() << "Clicked";
    move_rabbits(field, rabbits);
    move_wolfs(field, wolfs, rabbits);
    try{
        update();
    } catch (std::exception& e) {
        qDebug() << e.what();
    }


}
