#ifndef SETTINGS_H
#define SETTINGS_H

#include "cppsyntax.h"
#include <QDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMessageBox>
#include <QJsonArray>
#include <QDir>
#include <QJsonParseError>
#include <QFile>
#include <QStandardPaths>
#include <QDir>
#include <QFileDialog>
#include <QPalette>
#include <QColorDialog>
namespace Ui {
class settings;
}

class settings : public QDialog
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = nullptr);
    ~settings();

private slots:
    void on_spinBox_valueChanged(int arg1);
    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_openFolder_clicked();

    void on_openFolder_2_clicked();

    void on_openFolder_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_pushButton_3_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::settings *ui;
    CppSyntax *cppHighlighter;
};

#endif // SETTINGS_H
