#include "about.h"
#include "ui_about.h"

//Constructor
about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);

    //Application infos
    QString appversion = "Version 1.0.3";
    QString appname = "Ecstasy Editor";
    QString updateVersionCnt = "Update version KB1 (12/08/2021)";

    //Window fixed sizes
    this->setFixedSize(289, 416);

    //AppVersion_lbl Settings
    ui->appVersion_lbl->setText(appversion);

    //AppName Settings
    ui->appname->setStyleSheet("QLabel {color: aqua;}");

    //AppName Shadow Settings
    ui->appnameshw->setStyleSheet("QLabel {color: rgba(0,0,0,125);}");

    //AppInfo Settings
    ui->appinfo->setStyleSheet("QLabel {border: 1px solid black;}");
    ui->appinfo->setText(appname + " - " + appversion + ". " + updateVersionCnt);

    //AppInfo title Settings
    ui->appinfo_title->setStyleSheet("QLabel {background-color: rgb(240,240,240);}");

    //Thanks Border Settings
    ui->thanks_border->setStyleSheet("QLabel {border: 1px solid black;}");

    //Thanks title Settings
    ui->thanks_title->setStyleSheet("QLabel {background-color: rgb(240,240,240);}");

    //ContactText Settings
    ui->contact_text->setStyleSheet("QLabel {border: 1px solid black;}");
    ui->contact_text->setText(ui->contact_text->text() + "<a href=\"https://discord.gg/Qfz4zuPHZ6\"> Ecstasy Corp. Discord Server</a>");
    ui->contact_text->setTextFormat(Qt::RichText);
    ui->contact_text->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->contact_text->setOpenExternalLinks(true);

    //Contacttitle Settings
    ui->contact_title->setStyleSheet("QLabel {background-color: rgb(240,240,240);}");


}

//Destructor
about::~about()
{
    delete ui;
}
