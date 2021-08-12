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
    QString version;
    version = "Version 1.0.3";

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
    connect(ui->openFile_btn, SIGNAL(clicked()), this, SLOT(onTextReturned()));
    connect(this, SIGNAL(newText(QString, QString)), mainwin, SLOT(onNewText(QString, QString)));
}

//Destructor
splashscreen::~splashscreen()
{
    delete ui;
}

//On new file button clicked
void splashscreen::on_newFile_btn_clicked()
{
    MainWindow *mainwin = new MainWindow();
    mainwin->show();
    this->close();
}

//On about button clicked

void splashscreen::on_about_btn_clicked()
{
    about *abt = new about;
    abt->exec();
}

//On open button clicked (go to constructor to see connected functions)
void splashscreen::onTextReturned()
{
    //Setting up the standard document path
    QString documentPath = QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));

    //Opening the file
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open a file"), documentPath, tr("Ecstasy Text File (*.etxt);; All Files (*)"));
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QFile::Text))
    {
       QTextStream in (&file);
       emit newText(in.readAll(), file.fileName());
       mainwin->show();
       file.close();
       this->close();
    }

}
