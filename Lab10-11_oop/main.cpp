#include "Main_Window.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>

void adaugaCateva(Magazin& ctr) {

    ctr.addProdus("aaa", "vvv", 10, "eee");
    ctr.addProdus("bbb", "xxx", 80, "fff");
    ctr.addProdus("ccc", "yyy", 50, "ggg");
    ctr.addProdus("ddd", "zzz", 70, "hhh");
}

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    ProdusRepo rep;
    CosRepo rep_c;
    
    ProdusValidator val;

    Magazin srv{ rep, val };
    CosService srv_c{ rep_c };

    adaugaCateva(srv);

    Main_Window w(srv, srv_c);
    w.setWindowTitle("  Meniu");
    w.show();
    return a.exec();
}