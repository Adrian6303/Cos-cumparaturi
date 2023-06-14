#include "Main_Window.h"
#include <random>



Main_Window::Main_Window(Magazin& srv, CosService& srv_c) : service{ srv }, service_c { srv_c }
{
    QFont font("Courier");
    font.setStyleHint(QFont::Monospace);
    Main_Window::setFont(font);

    layout = new QVBoxLayout(this);
    service.add_observer(this);
    add_button = new QPushButton("Adauga");
    del_button = new QPushButton("Sterge");
    edit_button = new QPushButton("Modifica");
    filtrarePret_button = new QPushButton("Filtrare Pret");
    filtrareNume_button = new QPushButton("Filtrare Nume");
    cos_button = new QPushButton("Cos");

    adauga = new Adaugare(service);
    sterge = new Stergere(service);
    modifica = new Modificare(service);
    filtrareP = new FiltrarePret(service);
    filtrareN = new FiltrareNume(service);

    adauga->setWindowTitle("Adaugare");
    sterge->setWindowTitle("Stergere");
    modifica->setWindowTitle("Modifica");
    filtrareP->setWindowTitle("Filtrare Pret");
    filtrareN->setWindowTitle("Filtrare Nume");

    layout->addWidget(add_button);
    layout->addWidget(del_button);
    layout->addWidget(edit_button);
    layout->addWidget(filtrarePret_button);
    layout->addWidget(filtrareNume_button);
    layout->addWidget(cos_button);

    this->connect(add_button, SIGNAL(clicked()), adauga, SLOT(show()));
    this->connect(del_button, SIGNAL(clicked()), sterge, SLOT(show()));
    this->connect(edit_button, SIGNAL(clicked()), modifica, SLOT(show()));
    this->connect(filtrarePret_button, SIGNAL(clicked()), filtrareP, SLOT(show()));
    this->connect(filtrareNume_button, SIGNAL(clicked()), filtrareN, SLOT(show()));
    this->connect(cos_button, SIGNAL(clicked()), this, SLOT(cos()));


    listP = new QListWidget();
    std::vector<Produs> produse = service.getAll();
    QString message = QString("%1  %2 %3 %4").arg("Nume", -7).arg("Tip", -7).arg("Pret", -5).arg("Producator", -7);
    listP->addItem(message);
    for (const auto& prod : produse) {
        QString nume_str = QString::fromStdString(prod.get_nume());
        QString tip_str = QString::fromStdString(prod.get_tip());
        QString pret_str = QString::number(prod.get_pret());
        QString producator_str = QString::fromStdString(prod.get_producator());
        QString prod_string = QString("%1  %2 %3 %4").arg(nume_str, -7).arg(tip_str, -7).arg(pret_str, -5).arg(producator_str, -7);
        listP->addItem(prod_string);

    }
    layout->addWidget(listP);
    
}

void Main_Window::cos() {
    Cos_Window* fereastra_cos;
    fereastra_cos = new Cos_Window(service, service_c);
    service_c.add_observer(fereastra_cos);
    fereastra_cos->show();
}

void Main_Window::update()
{
    reload();
}

void Main_Window::reload() {
    listP->clear();
    std::vector<Produs> produse = service.getAll();
    QString message = QString("%1  %2 %3 %4").arg("Nume", -7).arg("Tip", -7).arg("Pret", -5).arg("Producator", -7);
    listP->addItem(message);
    for (const auto& prod : produse) {
        QString nume_str = QString::fromStdString(prod.get_nume());
        QString tip_str = QString::fromStdString(prod.get_tip());
        QString pret_str = QString::number(prod.get_pret());
        QString producator_str = QString::fromStdString(prod.get_producator());
        QString prod_string = QString("%1  %2 %3 %4").arg(nume_str, -7).arg(tip_str, -7).arg(pret_str, -5).arg(producator_str, -7);
        listP->addItem(prod_string);

    }

}

////////////////////////////////////////////////////////////////

Cos_Window::Cos_Window(Magazin& srv, CosService& srv_c) : service { srv }, service_c { srv_c }
{
    QFont font("Courier");
    font.setStyleHint(QFont::Monospace);
    Cos_Window::setFont(font);
    this->setWindowTitle("Cos");

    layout = new QFormLayout(this);

    list_cos = new QListWidget(this);
    layout->addWidget(list_cos);
    reload_cos();

    generare_button = new QPushButton("Generare Cos");
    layout->addWidget(generare_button);
    this->connect(generare_button, SIGNAL(clicked()), this , SLOT(generare_cos()));

    golire_button = new QPushButton("Golire Cos");
    layout->addWidget(golire_button);
    this->connect(golire_button, SIGNAL(clicked()), this, SLOT(golire_cos()));

    //desen = new Desenare(service_c);
    desenare_button = new QPushButton("Desenare Cos");
    layout->addWidget(desenare_button);
    this->connect(desenare_button, SIGNAL(clicked()), this, SLOT(desenare_cos()));

}

void Cos_Window::desenare_cos() {

    Cos_Desen* fereastra_cos_desen;


    std::vector<Produs> cos = service_c.get_all();
    int size = cos.size();

    fereastra_cos_desen = new Cos_Desen(size);
    fereastra_cos_desen->show();
}

void Cos_Window::reload_cos() {
    list_cos->clear();
    cos = service_c.get_all();
    QString message = QString("%1  %2 %3 %4").arg("Nume", -7).arg("Tip", -7).arg("Pret", -5).arg("Producator", -7);
    list_cos->addItem(message);
    for (const auto& prod : cos) {
        QString nume_str = QString::fromStdString(prod.get_nume());
        QString tip_str = QString::fromStdString(prod.get_tip());
        QString pret_str = QString::number(prod.get_pret());
        QString producator_str = QString::fromStdString(prod.get_producator());
        QString prod_string = QString("%1  %2 %3 %4").arg(nume_str, -7).arg(tip_str, -7).arg(pret_str, -5).arg(producator_str, -7);
        list_cos->addItem(prod_string);

    }
}

void Cos_Window::update(){
    reload_cos();
}

void Cos_Window::golire_cos() {
    service_c.goleste();
}

void Cos_Window::generare_cos() {
    service_c.goleste();
    vector<Produs> rez{ service.getAll() };

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, rez.size() - 1); // define the range

    int nr= rand()%20+1;
    for (int n = 0; n < nr; ++n)// range for(0,nr)
    {
        int poz = distr(gen);
        Produs p = rez[poz];
        service_c.addCos(p);
    }
    service_c.salveaza_fisier("cos.txt");
}


/////////////////////////////////////////////////////////////

Cos_Desen::Cos_Desen(int size) : size_c { size }
{

    this->setWindowTitle("Desen Cos");

    this->resize(600, 400);
    
    

}
///////////////////////////////////////////////////////////////

Adaugare::Adaugare(Magazin& service) : srv{ service }
{
    layout = new QFormLayout(this);

    label_nume = new QLabel("Nume");
    label_tip = new QLabel("Tip");
    label_pret = new QLabel("Pret");
    label_prod = new QLabel("Producator");

    text_nume = new QLineEdit;
    text_tip = new QLineEdit;
    text_pret = new QLineEdit;
    text_prod = new QLineEdit;
    submit_button = new QPushButton("Adauga produs");

    layout->addRow(label_nume, text_nume);
    layout->addRow(label_tip, text_tip);
    layout->addRow(label_pret, text_pret);
    layout->addRow(label_prod, text_prod);
    layout->addRow(submit_button);

    this->connect(submit_button, SIGNAL(clicked()), this, SLOT(submit_button_clicked()));
}

void Adaugare::submit_button_clicked()
{
    std::string nume = text_nume->text().toStdString();
    //QString proba = QString::fromStdString(nume);
    std::string tip = text_tip->text().toStdString();

    bool convert = true;
    int pret = text_pret->text().toInt(&convert);
    if (convert == false)
    {
        QMessageBox* mesaj = new QMessageBox;
        mesaj->setText("Pretul nu este numar");
        mesaj->setWindowTitle("Eroare");
        mesaj->show();
        return;
    }
    std::string prod = text_prod->text().toStdString();

    try
    {
        srv.addProdus(nume, tip, pret, prod);
        this->close();
    }
    catch (...) {

        QMessageBox* mesaj = new QMessageBox;
        mesaj->setText("Produsul exista deja");
        mesaj->setWindowTitle("Eroare");
        mesaj->show();
    }
    

}



//////////////////////////////////////////////////////////////


Stergere::Stergere(Magazin& service) : srv{ service }
{
    layout = new QFormLayout(this);

    label_nume = new QLabel("Nume");
    label_tip = new QLabel("Tip");
    text_nume = new QLineEdit;
    text_tip = new QLineEdit;
    submit_button = new QPushButton("Sterge produs");

    layout->addRow(label_nume, text_nume);
    layout->addRow(label_tip, text_tip);
    layout->addRow(submit_button);

    this->connect(submit_button, SIGNAL(clicked()), this, SLOT(submit_button_clicked()));
}

void Stergere::submit_button_clicked()
{
    std::string nume = text_nume->text().toStdString();
    std::string tip = text_tip->text().toStdString();
    


    try
    {
        srv.stergeProdus(nume, tip);
        this->close();
    }
    catch(...){

  
        QMessageBox* mesaj = new QMessageBox;
        mesaj->setText("Nu exista produsul");
        mesaj->setWindowTitle("Eroare");
        mesaj->show(); 
    }
}


/////////////////////////////////////////////////////////////////


Modificare::Modificare(Magazin& service) : srv{ service }
{
    layout = new QFormLayout(this);

    label_nume = new QLabel("Nume");
    label_tip = new QLabel("Tip");
    label_pret = new QLabel("Pret nou");

    text_nume = new QLineEdit;
    text_tip = new QLineEdit;
    text_pret = new QLineEdit;
    submit_button = new QPushButton("Modifica produs");

    layout->addRow(label_nume, text_nume);
    layout->addRow(label_tip, text_tip);
    layout->addRow(label_pret, text_pret);
    layout->addRow(submit_button);

    this->connect(submit_button, SIGNAL(clicked()), this, SLOT(submit_button_clicked()));
}

void Modificare::submit_button_clicked()
{
    std::string nume = text_nume->text().toStdString();
    std::string tip = text_tip->text().toStdString();
    
    bool convert = true;
    int pret = text_pret->text().toInt(&convert);
    if (convert == false)
    {
        QMessageBox* mesaj = new QMessageBox;
        mesaj->setText("Pretul nu este numar");
        mesaj->setWindowTitle("Eroare");
        mesaj->show();
        return;
    }
    

    try
    {
        srv.modificaProdus(nume, tip, pret);
        this->close();
    }
    catch (...) {


        QMessageBox* mesaj = new QMessageBox;
        mesaj->setText("Nu exista produsul");
        mesaj->setWindowTitle("Eroare");
        mesaj->show();
    }
}


/////////////////////////////////////////////////////////

FiltrarePret::FiltrarePret(Magazin& service) : srv{ service }
{

    layout = new QFormLayout(this);

    label_pret = new QLabel("Introduce Pret");
    text_pret = new QLineEdit;
    submit_button = new QPushButton("Filtrare dupa Pret");

    layout->addRow(label_pret, text_pret);
    layout->addRow(submit_button);

    this->connect(submit_button, SIGNAL(clicked()), this, SLOT(submit_button_clicked()));
}

void FiltrarePret::submit_button_clicked()
{
    bool convert = true;
    int pret = text_pret->text().toInt(&convert);
    if (convert == false)
    {
        QMessageBox* mesaj = new QMessageBox;
        mesaj->setText("Pretul nu este numar");
        mesaj->setWindowTitle("Eroare");
        mesaj->show();
        return;
    }

    
    produse= srv.filtrarePret(pret);


    listP = new QListWidget();
    QString messageT = "Produsele cu pretul mai mic decat ";
    messageT.append(QString::number(pret));
    listP->setWindowTitle(messageT);

    QFont font("Courier");
    font.setStyleHint(QFont::Monospace);
    listP->setFont(font);

    QString message = QString("%1  %2 %3 %4").arg("Nume", -7).arg("Tip", -7).arg("Pret", -5).arg("Producator", -7);
    listP->addItem(message);
    for (const auto& prod : produse) {
        QString nume_str = QString::fromStdString(prod.get_nume());
        QString tip_str = QString::fromStdString(prod.get_tip());
        QString pret_str = QString::number(prod.get_pret());
        QString producator_str = QString::fromStdString(prod.get_producator());
        QString prod_string = QString("%1  %2 %3 %4").arg(nume_str, -7).arg(tip_str, -7).arg(pret_str, -5).arg(producator_str, -7);
        listP->addItem(prod_string);

    }
    listP->show();
    this->close();

}


///////////////////////////////////////////////////


FiltrareNume::FiltrareNume(Magazin& service) : srv{ service }
{
    layout = new QFormLayout(this);

    label_nume = new QLabel("Introduce Nume");
    text_nume = new QLineEdit;
    submit_button = new QPushButton("Filtrare dupa Nume");

    layout->addRow(label_nume, text_nume);
    layout->addRow(submit_button);

    this->connect(submit_button, SIGNAL(clicked()), this, SLOT(submit_button_clicked()));
}

void FiltrareNume::submit_button_clicked()
{


    std::string nume = text_nume->text().toStdString();



    produse = srv.filtrareNume(nume);

    listP = new QListWidget();

    QString messageT = "Produsele cu numele ";
    messageT.append(QString::fromStdString(nume));
    listP->setWindowTitle(messageT);

    QFont font("Courier");
    font.setStyleHint(QFont::Monospace);
    listP->setFont(font);

    QString message = QString("%1  %2 %3 %4").arg("Nume", -7).arg("Tip", -7).arg("Pret", -5).arg("Producator", -7);
    listP->addItem(message);
    for (const auto& prod : produse) {
        QString nume_str = QString::fromStdString(prod.get_nume());
        QString tip_str = QString::fromStdString(prod.get_tip());
        QString pret_str = QString::number(prod.get_pret());
        QString producator_str = QString::fromStdString(prod.get_producator());
        QString prod_string = QString("%1  %2 %3 %4").arg(nume_str, -7).arg(tip_str, -7).arg(pret_str, -5).arg(producator_str, -7);
        listP->addItem(prod_string);

    }
    listP->show();
    this->close();
}

