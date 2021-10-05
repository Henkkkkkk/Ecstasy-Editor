#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonParseError>
#include "mainwindow.h"

namespace Ui {
class splashscreen;
}

class splashscreen : public QDialog
{
    Q_OBJECT

public:
    explicit splashscreen(QWidget *parent = nullptr);
    ~splashscreen();

private slots:


    void on_newFile_btn_clicked();

    void on_about_btn_clicked();

    void onTextReturned();
signals:
    void newText(const QString &text, const QString &fileName, const QFileInfo &fileInfo);
private:
    Ui::splashscreen *ui;
    MainWindow *mainwin;
};

#endif // SPLASHSCREEN_H
