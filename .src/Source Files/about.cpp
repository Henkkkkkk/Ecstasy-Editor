#include "about.h"
#include "ui_about.h"

//Constructor
about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);

    //Application infos
    QString appinfo{"A simple, lightweight and powerful text editor."};
    QString appversion{"Version 1.1.4"};
    QString appname{"Ecstasy Editor"};
    QString updateVersionCnt{"Update version KB90(04/10/2021)"};
    //Opening the settings.json file
    QFile file(QApplication::applicationDirPath() + "/settings.json");
    QByteArray content;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        content = file.readAll();
        file.close();
    }
    QJsonDocument jsonDoc{QJsonDocument::fromJson(content)};
    QJsonObject jo{jsonDoc.object()};
    //Setting up widgets in dark theme/light theme
    if(jo["darkTheme"].toBool() == true)
    {
        this->setStyleSheet("QDialog {background-color: rgb(54,54,54);}");
        ui->appinfo_title->setStyleSheet("QLabel {background-color: rgb(54,54,54); color: white;}");
        ui->contact_title->setStyleSheet("QLabel {background-color: rgb(54,54,54); color: white;}");
        ui->thanks_title->setStyleSheet("QLabel {background-color: rgb(54,54,54); color: white;}");
        ui->appinfo->setStyleSheet("QLabel {border: 1px solid grey; color: white;}");
        ui->thanks_border->setStyleSheet("QLabel {border: 1px solid grey; color: white;}");
        ui->contact_text->setStyleSheet("QLabel {border: 1px solid grey; color: white;}");
        ui->label_3->setStyleSheet("QLabel {color: white;}");
    }
    else
    {
        this->setStyleSheet("QDialog {background-color: rgb(243,243,243);}");
        ui->appinfo->setStyleSheet("QLabel {border: 1px solid black; color: black;}");
        ui->thanks_border->setStyleSheet("QLabel {border: 1px solid black; color: black;}");
        ui->contact_text->setStyleSheet("QLabel {border: 1px solid black; color: black;}");
        ui->appinfo_title->setStyleSheet("QLabel {background-color: rgb(243,243,243); color: black;}");
        ui->contact_title->setStyleSheet("QLabel {background-color: rgb(243,243,243); color: black;}");
        ui->thanks_title->setStyleSheet("QLabel {background-color: rgb(243,243,243); color: black;}");
    }
    //Window fixed sizes
    this->setFixedSize(365, 393);

    ui->label_7->setText(appinfo);

    //AppInfo Settings
    ui->appinfo->setText(appname + " - " + appversion + ". " + updateVersionCnt);

    //ContactText Settings
    ui->contact_text->setTextFormat(Qt::RichText);
    ui->contact_text->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->contact_text->setOpenExternalLinks(true);

}

//Destructor
about::~about()
{
    delete ui;
}
