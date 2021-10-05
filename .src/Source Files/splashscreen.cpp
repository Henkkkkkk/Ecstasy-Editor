#include "splashscreen.h"
#include "mainwindow.h"
#include "ui_splashscreen.h"
#include "about.h"

//Constructor
splashscreen::splashscreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::splashscreen)
{
    ui->setupUi(this);
    //Disable Window Resizing
    this->setFixedSize(1020, 573);
    mainwin = new MainWindow();
    //AppVersion
    QString version{"Version 1.1.4"};

    //Set Splashscreen Background
    QPixmap splash_image;
    splash_image.load(":/Images/splashscreen_1.png");
    splash_image = splash_image.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette splash_palette;
    splash_palette.setBrush(QPalette::Window, splash_image);
    this->setPalette(splash_palette);

    //AppNamelbl Settings
    ui->appNamelbl->setStyleSheet("QLabel {color: aqua;}");

    //VersionCodelbl Settings
    ui->versionCode->setText(version);
    ui->versionCode->setStyleSheet("QLabel {color: white;}");

    //Copyrightlbl Settings
    ui->copyright_lbl->setStyleSheet("QLabel {color: white;}");

    //NewFile_btn Settings
    ui->newFile_btn->setStyleSheet("QPushButton {color: white;}");

    //OpenFile_btn Settings
    ui->openFile_btn->setStyleSheet("QPushButton {color: white;}");

    ui->appNameshw->setStyleSheet("QLabel {color: rgba(0,0,0,125);}");

    //About_btn Settings
    ui->about_btn->setStyleSheet("QPushButton {color: white;}");

    //Changelog Settings
    ui->changelog->setStyleSheet("QLabel {color: white;}");
    QFile changelog(QString(":/ChangeLog/changelog.txt"));
    if (changelog.open(QIODevice::ReadOnly))
    {
        while (!changelog.atEnd())
        {
            QString line = changelog.readLine();
            ui->changelog->setText(ui->changelog->text() + line);
        }
        changelog.close();
    }

    //Connecting open file menu signals and slots
    QObject::connect(ui->openFile_btn, &QPushButton::clicked, this, &splashscreen::onTextReturned);
    QObject::connect(this, &splashscreen::newText, mainwin, &MainWindow::onNewText);
}

//Destructor
splashscreen::~splashscreen()
{
    delete ui;
}

//On new file button clicked
void splashscreen::on_newFile_btn_clicked()
{
    MainWindow *mainwin{new MainWindow()};
    mainwin->show();
    this->close();
}

//On about button clicked

void splashscreen::on_about_btn_clicked()
{
    about *abt{new about};
    abt->exec();
}

//On open button clicked (go to constructor to see connected functions)
void splashscreen::onTextReturned()
{
    //Getting the settings.json file
    QFile settings(QCoreApplication::applicationDirPath() + "/settings.json");
    QByteArray content;
    if(settings.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        content = settings.readAll();
        settings.close();
    }

    QJsonParseError *errPars{new QJsonParseError()};
    QJsonDocument jsonDoc{QJsonDocument::fromJson(content, errPars)};
    QJsonObject obj{jsonDoc.object()};

    //Setting the document path
    QString path{};
    if(obj["defaultOpenLocation"].toString() == "Documents")
        path = QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    else
        path = obj["defaultOpenLocation"].toString();


    //Opening the file
    QString fileName{QFileDialog::getOpenFileName(this, tr("Open a file"), path, tr("Ecstasy Text File (*.etxt);; All Files (*)"))};
    QFile file(fileName);
    QFileInfo fileInfo(file);
    if(file.open(QIODevice::ReadOnly | QFile::Text))
    {
       emit newText(file.readAll(), file.fileName(), fileInfo);
       mainwin->show();
       file.close();
       this->close();
    }

}
