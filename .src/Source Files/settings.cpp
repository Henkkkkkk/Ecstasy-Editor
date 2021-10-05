#include "settings.h"
#include "ui_settings.h"

settings::settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    //Setting fixed size to the dialog
    this->setFixedSize(392, 556);
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
    //Settings up the widgets
    QString fontName{jo["font"].toObject()["family"].toString()};
    int fontSize{jo["font"].toObject()["pointSize"].toInt()};
    ui->fontComboBox->setCurrentText(fontName);
    ui->spinBox->setValue(fontSize);
    ui->textEdit->setText("Lorem ipsum dolor sit amet, consectetur adipiscing elit.");
    ui->textEdit->setFont(QFont(fontName));
    ui->textEdit->setFontPointSize(fontSize);
    ui->spinBox->setValue(ui->spinBox->value() + 1);
    ui->spinBox->setValue(ui->spinBox->value() - 1);
    if(jo["defaultSavingLocation"].toString() == "Documents")
    {
        QString documentPath{QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation))};
        ui->lineEdit->setText(documentPath);
    }
    else
    {
        ui->lineEdit->setText(jo["defaultSavingLocation"].toString());
    }
    if(jo["defaultOpenLocation"].toString() == "Documents")
    {
        QString documentPath{QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation))};
        ui->lineEdit_2->setText(documentPath);
    }
    else
    {
        ui->lineEdit_2->setText(jo["defaultOpenLocation"].toString());
    }
    if(jo["defaultPictureLocation"].toString() == "Pictures")
    {
        QString picturePath{QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation))};
        ui->lineEdit_3->setText(picturePath);
    }
    else
    {
        ui->lineEdit_3->setText(jo["defaultPictureLocation"].toString());
    }
    if(jo["font"].toObject()["bold"].toBool() == true)
    {
        ui->checkBox->setChecked(true);
    }
    else
    {
        ui->checkBox->setChecked(false);
    }
    if(jo["font"].toObject()["italics"].toBool() == true)
    {
        ui->checkBox_2->setChecked(true);
    }
    else
    {
        ui->checkBox_2->setChecked(false);
    }
    if(jo["font"].toObject()["underline"].toBool() == true)
    {
        ui->checkBox_3->setChecked(true);
    }
    else
    {
        ui->checkBox_3->setChecked(false);
    }
    if(jo["showWarnMsg"].toBool() == true)
    {
        ui->checkBox_4->setChecked(true);
    }
    else
    {
        ui->checkBox_4->setChecked(false);
    }
    if(jo["printWithColors"].toBool() == true)
    {
        ui->checkBox_5->setChecked(true);
    }
    else
    {
        ui->checkBox_5->setChecked(false);
    }
    if(jo["printHorizontally"].toBool() == true)
        ui->checkBox_6->setChecked(true);
    else
        ui->checkBox_6->setChecked(false);
    bool darkEnabled{jo["darkTheme"].toBool()};
    if(darkEnabled == true)
    {
        ui->comboBox->setCurrentIndex(1);
        this->setStyleSheet("QDialog{ background-color: rgb(64,64,64);}");
        ui->fontCustomTitle->setStyleSheet("QLabel {background-color: rgb(54,54,54); color: white;}");
        ui->fontImage->setStyleSheet("QLabel {background-color: rgb(54,54,54); color: white;}");
        ui->saveSettings->setStyleSheet("QLabel {background-color: rgb(54,54,54); color: white;}");
        ui->saveImage->setStyleSheet("QLabel {background-color: rgb(54,54,54); color: white;}");
        ui->printSettings->setStyleSheet("QLabel {background-color: rgb(54,54,54); color: white;}");
        ui->printImage->setStyleSheet("QLabel {background-color: rgb(54,54,54); color: white;}");
        ui->colorimg->setStyleSheet("QLabel {background-color: rgb(54,54,54); color: white;}");
        ui->colorTitle->setStyleSheet("QLabel {background-color: rgb(54,54,54); color: white;}");
        ui->interfaceImg->setStyleSheet("QLabel {background-color: rgb(54,54,54); color: white;}");
        ui->interfaceTitle->setStyleSheet("QLabel {background-color: rgb(54,54,54); color: white;}");
        ui->tabWidget->setStyleSheet("QTabWidget{border: none;}");
        ui->tabWidget->tabBar()->setStyleSheet("QTabBar::tab{color: white; background-color: rgb(74,75,76);}"
                                               "QTabBar::tab:selected{background-color: rgb(54,54,54);}");
        ui->label->setStyleSheet("QLabel{color:white;}");
        ui->label_2->setStyleSheet("QLabel{color:white;}");
        ui->label_3->setStyleSheet("QLabel{color:white;}");
        ui->label_4->setStyleSheet("QLabel{color:white;}");
        ui->defFont->setStyleSheet("QLabel{color:white;}");
        ui->checkBox->setStyleSheet("QCheckBox{color:white;}");
        ui->checkBox_2->setStyleSheet("QCheckBox{color:white;}");
        ui->checkBox_3->setStyleSheet("QCheckBox{color:white;}");
        ui->checkBox_4->setStyleSheet("QCheckBox{color:white;}");
        ui->checkBox_5->setStyleSheet("QCheckBox{color:white;}");
        ui->checkBox_6->setStyleSheet("QCheckBox{color:white;}");
        ui->spinBox->setStyleSheet("QSpinBox{background-color: rgb(54,54,54);} QSpinBox, QLineEdit{color:white;}");
        ui->textEdit->setStyleSheet("QTextEdit{ color:white; background-color: rgb(38,38,38);}");
        ui->textEdit_2->setStyleSheet("QTextEdit{ color:white; background-color: rgb(38,38,38);}");
        ui->lineEdit->setStyleSheet("QLineEdit{ color:white; background-color: rgb(38,38,38); border: 1px solid grey}");
        ui->lineEdit_2->setStyleSheet("QLineEdit{ color:white; background-color: rgb(38,38,38); border: 1px solid grey}");
        ui->lineEdit_3->setStyleSheet("QLineEdit{ color:white; background-color: rgb(38,38,38); border: 1px solid grey}");
        ui->fontComboBox->setStyleSheet("QFontComboBox{background-color: rgb(38,38,38)} QFontComboBox, QAbstractItemView {border:1px solid grey; background-color: rgb(48,48,48); color: white;} QFontComboBox, QLineEdit{color:white;}");
        ui->comboBox->setStyleSheet("QComboBox{background-color: rgb(38,38,38)} QComboBox, QAbstractItemView {border:1px solid grey; background-color: rgb(48,48,48); color: white;} QComboBox, QLineEdit{color:white;}");
        ui->label_5->setStyleSheet("QLabel{color:white;}");
        ui->label_8->setStyleSheet("QLabel{color:white;}");
        ui->label_9->setStyleSheet("QLabel{color:white;}");
        ui->label_11->setStyleSheet("QLabel{color:white;}");
        ui->borderFont->setStyleSheet("QLabel{border: 1px solid grey;}");
        ui->borderSaving->setStyleSheet("QLabel{border: 1px solid grey;}");
        ui->borderPrint->setStyleSheet("QLabel{border: 1px solid grey;}");
        ui->borderColor->setStyleSheet("QLabel{border: 1px solid grey;}");
        ui->borderInterface->setStyleSheet("QLabel{border: 1px solid grey;}");
        QPalette tab1Background{ui->tab_1->palette()};
        tab1Background.setColor(QPalette::Window, QColor(54,54,54));
        ui->tab_1->setPalette(tab1Background);
        QPalette tab2Background{ui->tab_2->palette()};
        tab2Background.setColor(QPalette::Window, QColor(54,54,54));
        ui->tab_2->setPalette(tab2Background);
    }
    else
    {
        ui->fontCustomTitle->setStyleSheet("QLabel {background-color: white; color: black;}");
        ui->fontImage->setStyleSheet("QLabel {background-color: white; color: black;}");
        ui->saveSettings->setStyleSheet("QLabel {background-color: white; color: black;}");
        ui->saveImage->setStyleSheet("QLabel {background-color: white; color: black;}");
        ui->printSettings->setStyleSheet("QLabel {background-color: white; color: black;}");
        ui->printImage->setStyleSheet("QLabel {background-color: white; color: black;}");
        ui->colorimg->setStyleSheet("QLabel {background-color: white; color: black;}");
        ui->colorTitle->setStyleSheet("QLabel {background-color: white; color: black;}");
        ui->interfaceImg->setStyleSheet("QLabel {background-color: white; color: black;}");
        ui->interfaceTitle->setStyleSheet("QLabel {background-color: white; color: black;}");
        ui->borderFont->setStyleSheet("QLabel{border: 1px solid black;}");
        ui->borderSaving->setStyleSheet("QLabel{border: 1px solid black;}");
        ui->borderPrint->setStyleSheet("QLabel{border: 1px solid black;}");
        ui->borderColor->setStyleSheet("QLabel{border: 1px solid black;}");
        ui->borderInterface->setStyleSheet("QLabel{border: 1px solid black;}");
        QPalette tab1Background{ui->tab_1->palette()};
        tab1Background.setColor(QPalette::Window, Qt::white);
        ui->tab_1->setPalette(tab1Background);
        QPalette tab2Background{ui->tab_2->palette()};
        tab2Background.setColor(QPalette::Window, Qt::white);
        ui->tab_2->setPalette(tab2Background);
    }
    cppHighlighter = new CppSyntax(ui->textEdit_2->document());
    ui->textEdit_2->setTabStopDistance(32);
    ui->textEdit_2->setText("#include <iostream>//Input\\OutputFolder\n\nint main()\n{\n\tstd::cout << \"Hello World\" << std::endl;\n\treturn 0;\n}");

    int foreRed{jo["font"].toObject()["foregroundColor"].toObject()["red"].toInt()};
    int foreGreen{jo["font"].toObject()["foregroundColor"].toObject()["green"].toInt()};
    int foreBlue{jo["font"].toObject()["foregroundColor"].toObject()["blue"].toInt()};
    ui->label_6->setAutoFillBackground(true);
    QPalette defaultForegroundPalette{ui->label_6->palette()};
    defaultForegroundPalette.setColor(QPalette::Window, QColor(foreRed, foreGreen, foreBlue));
    ui->label_6->setPalette(defaultForegroundPalette);

    int backRed{jo["font"].toObject()["backgroundColor"].toObject()["red"].toInt()};
    int backGreen{jo["font"].toObject()["backgroundColor"].toObject()["green"].toInt()};
    int backBlue{jo["font"].toObject()["backgroundColor"].toObject()["blue"].toInt()};
    ui->label_7->setAutoFillBackground(true);
    QPalette defaultBackgroundPalette{ui->label_7->palette()};
    defaultBackgroundPalette.setColor(QPalette::Window, QColor(backRed, backGreen, backBlue));
    ui->label_7->setPalette(defaultBackgroundPalette);

    int red{jo["toolBarColor"].toObject()["red"].toInt()};
    int green{jo["toolBarColor"].toObject()["green"].toInt()};
    int blue{jo["toolBarColor"].toObject()["blue"].toInt()};
    ui->label_10->setAutoFillBackground(true);
    QPalette defaultToolBarColor{ui->label_10->palette()};
    defaultToolBarColor.setColor(QPalette::Window, QColor(red, green, blue));
    ui->label_10->setPalette(defaultToolBarColor);
}

settings::~settings()
{
    delete ui;
}
//Global Variables
QColor foreGroundColor{};
QColor backGroundColor{};
QColor toolBarColor{};
bool foreGroundChanged{false};
bool backGroundchanged{false};
bool toolBarChanged{false};

void settings::on_spinBox_valueChanged(int arg1)
{
    QFont font{ui->textEdit->font()};
    font.setPointSize(arg1);
    ui->textEdit->setFont(font);
}

void settings::on_checkBox_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->textEdit->selectAll();
        ui->textEdit->setFontWeight(QFont::Bold);
    }
    else
    {
        ui->textEdit->selectAll();
        ui->textEdit->setFontWeight(QFont::Normal);
    }
    ui->textEdit->setFocus();
}


void settings::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->textEdit->selectAll();
        ui->textEdit->setFontItalic(true);
    }
    else
    {
        ui->textEdit->selectAll();
        ui->textEdit->setFontItalic(false);
    }
    ui->textEdit->setFocus();
}


void settings::on_checkBox_3_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->textEdit->selectAll();
        ui->textEdit->setFontUnderline(true);
    }
    else
    {
        ui->textEdit->selectAll();
        ui->textEdit->setFontUnderline(false);
    }
    ui->textEdit->setFocus();
}


void settings::on_openFolder_clicked()
{
    QFileDialog dialog;
    dialog.setWindowTitle("Choose a Folder");
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory(ui->lineEdit->text());
    dialog.setOptions(QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(dialog.exec() == QDialog::Accepted)
    {
        QDir folderName{dialog.directory()};
        ui->lineEdit->setText(folderName.absolutePath());
    }

}


void settings::on_openFolder_2_clicked()
{
    QFileDialog dialog;
    dialog.setWindowTitle("Choose a Folder");
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory(ui->lineEdit_2->text());
    dialog.setOptions(QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(dialog.exec() == QDialog::Accepted)
    {
        QDir folderName{dialog.directory()};
        ui->lineEdit_2->setText(folderName.absolutePath());
    }
}


void settings::on_openFolder_3_clicked()
{
    QFileDialog dialog;
    dialog.setWindowTitle("Choose a Folder");
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory(ui->lineEdit_3->text());
    dialog.setOptions(QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(dialog.exec() == QDialog::Accepted)
    {
        QDir folderName{dialog.directory()};
        ui->lineEdit_3->setText(folderName.absolutePath());
    }
}


void settings::on_pushButton_clicked()
{
    QColorDialog colorDialog;
    colorDialog.setWindowTitle("Choose a color");
    colorDialog.setCurrentColor(Qt::white);
    if(colorDialog.exec() == QDialog::Accepted)
    {
        foreGroundColor = colorDialog.currentColor();
        QPalette palette{ui->label_6->palette()};
        palette.setColor(QPalette::Window, foreGroundColor);
        ui->label_6->setPalette(palette);
        foreGroundChanged = true;
    }
}


void settings::on_pushButton_2_clicked()
{
    QColorDialog colorDialog;
    colorDialog.setWindowTitle("Choose a color");
    colorDialog.setCurrentColor(Qt::black);
    if(colorDialog.exec() == QDialog::Accepted)
    {
        backGroundColor = colorDialog.currentColor();
        QPalette palette{ui->label_7->palette()};
        palette.setColor(QPalette::Window, backGroundColor);
        ui->label_7->setPalette(palette);
        backGroundchanged = true;
    }
}


void settings::on_fontComboBox_currentFontChanged(const QFont &f)
{
    QFont font(f);
    font.setPointSize(ui->spinBox->value());
    ui->textEdit->setFont(font);
}

void settings::on_pushButton_3_clicked()
{
    QColorDialog colorDialog;
    colorDialog.setWindowTitle("Choose a color");
    colorDialog.setCurrentColor(QColor(154,244,230));
    if(colorDialog.exec() == QDialog::Accepted)
    {
        toolBarColor = colorDialog.currentColor();
        QPalette palette{ui->label_10->palette()};
        palette.setColor(QPalette::Window,toolBarColor);
        ui->label_10->setPalette(palette);
        toolBarChanged = true;
    }
}


void settings::on_buttonBox_accepted()
{
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
    QJsonObject fontObj{jo["font"].toObject()};
    fontObj.insert("family", ui->fontComboBox->currentText());
    fontObj.insert("pointSize", ui->spinBox->value());
    if(ui->checkBox->isChecked())
        fontObj.insert("bold", true);
    else
        fontObj.insert("bold", false);
    if(ui->checkBox_2->isChecked())
        fontObj.insert("italics", true);
    else
        fontObj.insert("italics", false);
    if(ui->checkBox_3->isChecked())
        fontObj.insert("underline", true);
    else
        fontObj.insert("underline", false);
    if(ui->checkBox_4->isChecked())
        jo.insert("showWarnMsg", true);
    else
        jo.insert("showWarnMsg", false);
    if(ui->checkBox_5->isChecked())
        jo.insert("printWithColors", true);
    else
        jo.insert("printWithColors", false);
    if(ui->checkBox_6->isChecked())
        jo.insert("printHorizontally", true);
    else
        jo.insert("printHorizontally", false);
    jo.insert("defaultSavingLocation", ui->lineEdit->text());
    jo.insert("defaultOpenLocation", ui->lineEdit_2->text());
    jo.insert("defaultPictureLocation", ui->lineEdit_3->text());
    if(ui->comboBox->currentIndex() == 0)
        jo.insert("darkTheme", false);
    else if(ui->comboBox->currentIndex() == 1)
        jo.insert("darkTheme", true);

    QJsonObject foreObj{fontObj["foregroundColor"].toObject()};
    if(foreGroundChanged == true)
    {
        foreObj.insert("red", foreGroundColor.red());
        foreObj.insert("green", foreGroundColor.green());
        foreObj.insert("blue", foreGroundColor.blue());
    }
    QJsonObject backObj{fontObj["backgroundColor"].toObject()};
    if(backGroundchanged == true)
    {
        backObj.insert("red", backGroundColor.red());
        backObj.insert("green", backGroundColor.green());
        backObj.insert("blue", backGroundColor.blue());
    }
    QJsonObject toolObj{jo["toolBarColor"].toObject()};
    if(toolBarChanged == true)
    {
        toolObj.insert("red", toolBarColor.red());
        toolObj.insert("green", toolBarColor.green());
        toolObj.insert("blue", toolBarColor.blue());
    }
    fontObj.insert("foregroundColor", foreObj);
    fontObj.insert("backgroundColor", backObj);
    jo.insert("font", fontObj);
    jo.insert("toolBarColor", toolObj);
    jsonDoc.setObject(jo);
    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    file.write(jsonDoc.toJson(QJsonDocument::Indented));
    file.close();
    //Creating an MsgBox to warn the user that he has to restart the application to get all the settings working
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle("Warning");
    msgBox.setText("To get all the settings working you have to restart the application. Be sure to save all the files first.");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();

    this->close();

}

void settings::on_buttonBox_rejected()
{
    this->close();
}

