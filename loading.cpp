#include "loading.h"
#include "ui_loading.h"
#include "splashscreen.h"

//Constructor
loading::loading(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loading)
{
    ui->setupUi(this);

    //Setting window attributes and flags
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    //Application Version
    QString version = "Version 1.0.3";
    ui->label->setText(version);

    //Shadow to the window
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(20);
    shadow->setXOffset(0);
    shadow->setYOffset(0);
    shadow->setColor(QColor(0,0,0,60));
    ui->frame->setGraphicsEffect(shadow);

    //Connecting the timer to the updateProgressBar function
    connect(timer, SIGNAL(timeout()), this, SLOT(updateProgressBar()));

    //Starting the timer
    timer->start(25);
}

//Declaring global int, counter
int counter = 0;


//Update progress bar function (go to the contructor to see connected functions)
void loading::updateProgressBar()
{
    if(counter <= 100)
    {
        counter++;
        ui->progressBar->setValue(counter);
        if(counter == 100)
        {
            ui->load->setText("Done!");
        }
    }
    else
    {
        timer->stop();
        delete timer;
        splashscreen *splash = new splashscreen();
        splash->show();
        this->close();
    }
}

//Destructor
loading::~loading()
{
    delete ui;
}
