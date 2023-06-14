#pragma once

#include "C:\\Users\\adria\\source\\repos\\Lab8-9_oop\\Lab8-9_oop\\service.h"
#include "C:\\Users\\adria\\source\\repos\\Lab8-9_oop\\Lab8-9_oop\\domain.h"
#include <QtWidgets/QMainWindow>
#include "Main_Window.h"
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/QPushButton>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qgridlayout.h>
#include <QtWidgets/qmessagebox>
#include <QTextEdit>
#include <QtWidgets/QListWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QImage>
#include <QRandomGenerator>


class Adaugare : public QWidget
{
    Q_OBJECT
public:
    Adaugare(Magazin& service);

private:
    Magazin& srv;
    QFormLayout* layout;
    QLabel* label_nume;
    QLabel* label_tip;
    QLabel* label_pret;
    QLabel* label_prod;
    QLineEdit* text_nume;
    QLineEdit* text_tip;
    QLineEdit* text_pret;
    QLineEdit* text_prod;
    QPushButton* submit_button;

signals:

private slots:
    void submit_button_clicked();
};

////////////////////////////////////////////////////////////

class Stergere : public QWidget
{
    Q_OBJECT
public:
    Stergere(Magazin& service);

private:
    Magazin& srv;
    QFormLayout* layout;
    QLabel* label_nume;
    QLabel* label_tip;
    QLineEdit* text_nume;
    QLineEdit* text_tip;
    QPushButton* submit_button;

signals:

private slots:
    void submit_button_clicked();
};

////////////////////////////////////////////////////

class Modificare : public QWidget
{
    Q_OBJECT
public:
    Modificare(Magazin& service);

private:
    Magazin& srv;
    QFormLayout* layout;
    QLabel* label_nume;
    QLabel* label_tip;
    QLabel* label_pret;
    QLineEdit* text_nume;
    QLineEdit* text_tip;
    QLineEdit* text_pret;
    QPushButton* submit_button;

signals:

private slots:
    void submit_button_clicked();
};


//////////////////////////////////////////////////////


class FiltrarePret : public QWidget
{
    Q_OBJECT
public:
    FiltrarePret(Magazin& service);
    vector<Produs> produse;
    

private:
    Magazin& srv;
    QFormLayout* layout;
    QLabel* label_pret;
    QLineEdit* text_pret;
    QPushButton* submit_button;
    QListWidget* listP;
    

signals:

private slots:
    void submit_button_clicked();

};

/////////////////////////////////////////////////////


class FiltrareNume : public QWidget
{
    Q_OBJECT
public:
    FiltrareNume(Magazin& service);
    vector<Produs> produse;


private:
    Magazin& srv;
    QFormLayout* layout;
    QLabel* label_nume;
    QLineEdit* text_nume;
    QPushButton* submit_button;
    QListWidget* listP;


signals:

private slots:
    void submit_button_clicked();

};

///////////////////////////////////////////////

class Cos_Desen : public QWidget
{
    Q_OBJECT
public:
    Cos_Desen(int size);
private:
    int size_c;

    void paintEvent(QPaintEvent* ev) override {

        QPainter p{ this };
        if (size_c == 0) {
            QColor color(255, 187, 153);
            p.setPen(color);
            p.setBrush(color);

            p.drawEllipse(100, 200, 200, 200);
            p.drawEllipse(300, 200,  200, 200);
            p.drawEllipse(220, 0, 150, 350);

        }
        

        for (int i = 1;i <= size_c;i++) {

            int red = QRandomGenerator::global()->bounded(256);
            int green = QRandomGenerator::global()->bounded(256);
            int blue = QRandomGenerator::global()->bounded(256);

            // Set the random color for drawing the circle
            QColor color(red, green, blue);
            p.setPen(color);
            p.setBrush(color);

            int w= QRandomGenerator::global()->bounded(100,width());
            int h = QRandomGenerator::global()->bounded(100, height());
            if (i % 3 == 1)
            {
                int x1 = w / 2;
                int y1 = h / 4;
                int x2 = w / 4;
                int y2 = h * 3 / 4;
                int x3 = w * 3 / 4;
                int y3 = h * 3 / 4;

                // Create a polygon and add the triangle vertices
                QPolygon triangle;
                triangle << QPoint(x1, y1);
                triangle << QPoint(x2, y2);
                triangle << QPoint(x3, y3);

                // Draw the triangle
                p.drawPolygon(triangle);
            }
            else if (i % 3 == 0) {

                // Calculate the size and position of the square
                int size = qMin(w, h) * 0.8; // Adjust the scale of the square
                int x = (w - size) / 2;
                int y = (h - size) / 2;

                // Draw the square
                p.drawRect(x, y, size, size);
            }
            else {

                // Calculate the center and radius of the circle
                int centerX = w;
                int centerY = h;
                int radius = qMin(w, h) /2;

                // Draw the circle using the calculated values
                p.drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);
            }
               
        }
        /*
        int x = 0;
        QImage image("C:\\Users\\adria\\source\\repos\\Lab10-11_oop\\Lab10-11_oop\\image.jpg");
        if (!image.isNull()) {
            QPoint imagePosition(x, 0);
            p.drawImage(imagePosition, image);
        }
        */
    }
};
//////////////////////////////////////////////////////

class Cos_Window : public QWidget, public Observer
{
    Q_OBJECT

public:
    Cos_Window(Magazin& srv, CosService& srv_c);
    void update() override;

private:
    QFormLayout* layout;
    Magazin& service;
    CosService& service_c;
    std::vector<Produs> cos;

    QListWidget* list_cos;

    QPushButton* generare_button;
    QPushButton* golire_button;
    QPushButton* desenare_button;


signals:

private slots:
    void reload_cos();
    void golire_cos();
    void generare_cos();
    void desenare_cos();
    


};

//////////////////////////////////////////////////////

class Main_Window : public QWidget, public Observer
{
    Q_OBJECT

public:
    Main_Window(Magazin& srv, CosService& srv_c);
    void update() override;


private:

    QVBoxLayout* layout;
    Magazin& service;
    CosService& service_c;
    QPushButton* add_button;
    QPushButton* del_button;
    QPushButton* edit_button;
    QPushButton* filtrarePret_button;
    QPushButton* filtrareNume_button;
    QPushButton* cos_button;

    QListWidget* listP;
    
    Adaugare* adauga;
    Stergere* sterge;
    Modificare* modifica;
    FiltrarePret* filtrareP;
    FiltrareNume* filtrareN;
private slots:
    void reload();
    void cos();
};