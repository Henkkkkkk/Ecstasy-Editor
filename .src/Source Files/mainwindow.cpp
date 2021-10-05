#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "splashscreen.h"
#include "about.h"
#include "settings.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    //Setting the colors to the toolbar
    int red{obj["toolBarColor"].toObject()["red"].toInt()};
    int green{obj["toolBarColor"].toObject()["green"].toInt()};
    int blue{obj["toolBarColor"].toObject()["blue"].toInt()};
    //Setting toolBar palette
    QPalette toolBarPalette{ui->toolBar->palette()};
    toolBarPalette.setColor(QPalette::Window, QColor(red,green,blue));
    ui->toolBar->setPalette(toolBarPalette);
    //Setting up colors
    int foreRed{obj["font"].toObject()["foregroundColor"].toObject()["red"].toInt()};
    int foreGreen{obj["font"].toObject()["foregroundColor"].toObject()["green"].toInt()};
    int foreBlue{obj["font"].toObject()["foregroundColor"].toObject()["blue"].toInt()};

    int backRed{obj["font"].toObject()["backgroundColor"].toObject()["red"].toInt()};
    int backGreen{obj["font"].toObject()["backgroundColor"].toObject()["green"].toInt()};
    int backBlue{obj["font"].toObject()["backgroundColor"].toObject()["blue"].toInt()};

    //Set MainWindow minimum size
    this->setMinimumHeight(652);
    this->setMinimumWidth(1187);

    //Setting the windows color
    QPalette thisColor{this->palette()};
    if(obj["darkTheme"].toBool() == false)
        thisColor.setColor(QPalette::Window, QColor(243,243,243));
    else
        thisColor.setColor(QPalette::Window, QColor(54,54,54));
    this->setPalette(thisColor);

    //Setting backcolor lbl palette
    QPalette palette{ui->backColor_lbl->palette()};
    if(obj["darkTheme"].toBool() == true)
    {
        if(backRed + backGreen + backBlue != 765)
            palette.setColor(QPalette::Window, QColor(backRed, backGreen, backBlue));
        else
            palette.setColor(QPalette::Window, Qt::black);
    }
    else
        palette.setColor(QPalette::Window, QColor(backRed, backGreen, backBlue));
    ui->backColor_lbl->setPalette(palette);

    //Setting foreoclor lbl palette
    QPalette palette2{ui->forecolor_lbl->palette()};
    if(obj["darkTheme"].toBool() == true)
    {
        if(foreRed + foreGreen + foreBlue != 0)
            palette2.setColor(QPalette::Window, QColor(foreRed, foreGreen, foreBlue));
        else
            palette2.setColor(QPalette::Window, Qt::white);
    }
    else
        palette2.setColor(QPalette::Window, QColor(foreRed, foreGreen, foreBlue));
    ui->forecolor_lbl->setPalette(palette2);

    //Setting the stackedWidget palette
    QPalette palette3{ui->stackedWidget->palette()};
    if(obj["darkTheme"].toBool() == false)
        palette3.setColor(QPalette::Window, QColor(243,243,243));
    else
        palette3.setColor(QPalette::Window, QColor(54,54,54));
    ui->stackedWidget->setPalette(palette3);

    //Setting toUpwerMenu pop-up menu
    QMenu *toUpwerMenu{new QMenu(this)};
    QAction *toUpper{new QAction("To Upper Case", this)};
    QAction *toLower{new QAction("To Lower Case", this)};
    //QObject::connecting signals
    QObject::connect(toUpper, &QAction::triggered, this, &MainWindow::toUpper);
    QObject::connect(toLower, &QAction::triggered, this, &MainWindow::toLower);

    //Adding actions to the menu
    toUpwerMenu->addAction(toUpper);
    toUpwerMenu->addAction(toLower);
    ui->toUpwer->setMenu(toUpwerMenu);

    //Stackedwidget btns
    homePalette = ui->homeButton->palette();
    designPalette = ui->designButton->palette();
    miscPalette = ui->miscellaniousButton->palette();
    homePalette.setColor(QPalette::Button, QColor(red,green,blue));
    designPalette.setColor(QPalette::Button, QColor(red,green,blue));
    miscPalette.setColor(QPalette::Button, QColor(red,green,blue));
    ui->homeButton->setPalette(homePalette);
    ui->designButton->setPalette(designPalette);
    ui->miscellaniousButton->setPalette(miscPalette);

    //Setting up the TextEdit
    QString fontName{obj["font"].toObject()["family"].toString()};
    int fontSize{obj["font"].toObject()["pointSize"].toInt()};
    ui->tabWidget->addTab(new TextEdit(), QString("New Document " + QString::number(ui->tabWidget->count() + 1)));
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    TextEdit *edit{getTabTextEdit()};
    edit->setGeometry(0,0,ui->tabWidget->width() - 3, ui->tabWidget->height() - 59);
    edit->setTabStopDistance(32);
    edit->setFocus();
    if(foreRed + foreGreen + foreBlue != 0)
        edit->setTextColor(QColor(foreRed, foreGreen, foreBlue));
    if(backRed + backGreen + backBlue != 765)
        edit->setTextBackgroundColor(QColor(backRed, backGreen, backBlue));
    edit->setFontPointSize(fontSize);
    edit->setFontFamily(fontName);
    ui->fontComboBox->setCurrentFont(QFont(fontName));
    ui->fontsize->setValue(fontSize);
    QObject::connect(edit, &TextEdit::textChanged, this, &MainWindow::edit_changed);
    QObject::connect(edit, &TextEdit::cursorPositionChanged, this, &MainWindow::cursorPosChanged);

    //Setting up some font buttons;
    if(obj["font"].toObject()["bold"].toBool() == true)
    {
        ui->boldBtn->setChecked(true);
        edit->setFontWeight(QFont::Bold);
    }
    else
    {
        ui->boldBtn->setChecked(false);
        edit->setFontWeight(QFont::Normal);
    }
    if(obj["font"].toObject()["italics"].toBool() == true)
    {
        ui->italicBtn->setChecked(true);
        edit->setFontItalic(true);
    }
    else
    {
        ui->italicBtn->setChecked(false);
        edit->setFontItalic(false);
    }
    if(obj["font"].toObject()["underline"].toBool() == true)
    {
        ui->underlineBtn->setChecked(true);
        edit->setFontUnderline(true);
    }
    else
    {
        ui->underlineBtn->setChecked(false);
        edit->setFontUnderline(false);
    }

    //Setting up the layout for the Design Section
    QWidget *widg{new QWidget};
    QHBoxLayout *layout{new QHBoxLayout(widg)};
    ui->normal->setFixedSize(81,51);
    ui->heading1->setFixedSize(81,51);
    ui->heading2->setFixedSize(81,51);
    ui->heading3->setFixedSize(81,51);
    ui->heading4->setFixedSize(81,51);
    ui->heading5->setFixedSize(81,51);
    ui->heading6->setFixedSize(81,51);
    ui->heading7->setFixedSize(81,51);
    ui->heading8->setFixedSize(81,51);
    ui->heading9->setFixedSize(81,51);
    ui->title->setFixedSize(81,51);
    ui->subtitle->setFixedSize(81,51);
    ui->subtitle_emphasis->setFixedSize(81,51);
    ui->emphasis->setFixedSize(81,51);
    ui->intense_emphasis->setFixedSize(81,51);
    ui->strong->setFixedSize(81,51);
    ui->quote->setFixedSize(81,51);
    ui->subtitle_reference->setFixedSize(81,51);
    ui->intense_reference->setFixedSize(81,51);
    ui->book_reference->setFixedSize(81,51);

    layout->addWidget(ui->normal);
    layout->addWidget(ui->heading1);
    layout->addWidget(ui->heading2);
    layout->addWidget(ui->heading3);
    layout->addWidget(ui->heading4);
    layout->addWidget(ui->heading5);
    layout->addWidget(ui->heading6);
    layout->addWidget(ui->heading7);
    layout->addWidget(ui->heading8);
    layout->addWidget(ui->heading9);
    layout->addWidget(ui->title);
    layout->addWidget(ui->subtitle);
    layout->addWidget(ui->subtitle_emphasis);
    layout->addWidget(ui->emphasis);
    layout->addWidget(ui->intense_emphasis);
    layout->addWidget(ui->strong);
    layout->addWidget(ui->quote);
    layout->addWidget(ui->subtitle_reference);
    layout->addWidget(ui->intense_reference);
    layout->addWidget(ui->book_reference);
    ui->scrollArea->setWidget(widg);

    //Setting dark/light theme
    if(obj["darkTheme"].toBool() == true)
    {
        QPalette palette5{widg->palette()};
        palette5.setColor(QPalette::Window, QColor(54,54,54));
        widg->setPalette(palette5);
        ui->normal->setStyleSheet("QPushButton{color: white;}");
        ui->title->setStyleSheet("QPushButton{color:white;}");
        ui->emphasis->setStyleSheet("QPushButton{color:white;}");
        ui->book_reference->setStyleSheet("QPushButton{color:white;}");
        ui->strong->setStyleSheet("QPushButton{color:white;}");
        ui->fileLbl->setStyleSheet("QLabel{color:white;}");
        ui->clipboardLbl->setStyleSheet("QLabel{color:white;}");
        ui->fontLbl->setStyleSheet("QLabel{color:white;}");
        ui->paragraphLbl->setStyleSheet("QLabel{color:white;}");
        ui->editLbl->setStyleSheet("QLabel{color:white;}");
        ui->insertLbl->setStyleSheet("QLabel{color:white;}");
        ui->textInfolbl->setStyleSheet("QLabel{color:white;}");
        ui->numOfColumns->setStyleSheet("QLabel{color:white;}");
        ui->numOfLines->setStyleSheet("QLabel{color:white;}");
        ui->addTable->setStyleSheet("QPushButton{color:white;}");
        ui->addFromFile->setStyleSheet("QPushButton{color:white;}");
        ui->separator_1->setStyleSheet("background-color:grey;");
        ui->separator_2->setStyleSheet("background-color:grey;");
        ui->separator_3->setStyleSheet("background-color:grey;");
        ui->separator_4->setStyleSheet("background-color:grey;");
        ui->separator_5->setStyleSheet("background-color:grey;");
        ui->separator_6->setStyleSheet("background-color:grey;");
        ui->line->setStyleSheet("background-color:grey;");
        ui->line_2->setStyleSheet("background-color:grey;");
        ui->line_3->setStyleSheet("background-color:grey;");
        toUpwerMenu->setStyleSheet("QMenu{background-color: rgb(64,64,64); color: white; selection-background-color: rgb(131,200,215);}");
        ui->fontComboBox->setStyleSheet("QFontComboBox{background-color: rgb(54,54,54)} QFontComboBox, QAbstractItemView {border:1px solid grey; background-color: rgb(48,48,48); color: white;} QFontComboBox, QLineEdit{color:white;}");
        ui->comboBox->setStyleSheet("QComboBox{background-color: rgb(54,54,54)} QComboBox, QAbstractItemView {border:1px solid grey; background-color: rgb(48,48,48); color: white;} QComboBox, QLineEdit{color:white;}");
        ui->fontsize->setStyleSheet("QSpinBox{background-color: rgb(54,54,54);} QSpinBox, QLineEdit{color:white;}");
        ui->tabWidget->setStyleSheet("QTabWidget{border: none;}");
        ui->tabWidget->tabBar()->setStyleSheet("QTabBar::tab{color: white; background-color: rgb(48,48,48);}"
                                               "QTabBar::tab:selected{background-color: rgb(38,38,38);}");
        edit->setStyleSheet("QTextEdit{background-color: rgb(38,38,38); color: white;}");
        ui->label->setStyleSheet("QLabel{color:white;}");
        ui->label_3->setStyleSheet("QLabel{color:white;}");
    }

    //Setting up lines and columns
    ui->numOfLines->setText("Line: 1");
    ui->numOfColumns->setText("Column: 1");
    //Enabling home button
    ui->homeButton->click();
}

//Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

//Global Variables
bool superscriptEnabled{false};
bool subscriptEnabled{false};

//On new text function (see splashscreen.cpp constructor to see QObject::connected functions)
void MainWindow::onNewText(const QString &text, const QString &fileName, const QFileInfo &fileInfo)
{
    TextEdit *edit{getTabTextEdit()};
    if(fileInfo.completeSuffix() == "etxt")
    {
        edit->setHtml(text);
        ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), fileName);
        currentFile = fileName;
    }
    else
    {
        if(fileInfo.completeSuffix() == "cpp" || fileInfo.completeSuffix() == "hpp")
        {
            cppHighlighter = new CppSyntax(edit->document());
            edit->setFont(QFont("Consolas"));
            ui->fontComboBox->setCurrentFont(QFont("Consolas"));
        }
            edit->setText(text);
            ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), fileName);
            currentFile = fileName;
    }
}

//Mainwindow resize event
void MainWindow::resizeEvent(QResizeEvent *)
{
    TextEdit *edit{getTabTextEdit()};
    ui->tabWidget->resize(this->width() + 3, this->height() - 87);
    edit->setGeometry(0,0,ui->tabWidget->width() - 3, ui->tabWidget->height() - 59);
    ui->toolBar->resize(this->width(), ui->toolBar->height());
}

//Closing tabs
void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    QTextEdit *edit{getTabTextEdit()};
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
    if(obj["showWarnMsg"].toBool() == true)
    {
        if(ui->tabWidget->count() > 1)
        {
            if(ui->tabWidget->tabText(index).contains("New Document ", Qt::CaseSensitive))
            {
                //Create a msg box to warn the user to save the file
                QMessageBox msgBox;
                QAbstractButton* save{msgBox.addButton(tr("Save"), QMessageBox::YesRole)};
                QAbstractButton* dontSave{msgBox.addButton(tr("Don't save"), QMessageBox::NoRole)};
                msgBox.addButton(tr("Cancel"), QMessageBox::RejectRole);
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setWindowTitle("Warning");
                msgBox.setText("Do you want to save your changes to the document?");
                msgBox.exec();
                if(msgBox.clickedButton() == save)
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
                    if(obj["defaultSavingLocation"].toString() == "Documents")
                        path = QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
                    else
                        path = obj["defaultSavingLocation"].toString();
                    QString fileName = QFileDialog::getSaveFileName(this, tr("Save a file"), path, tr("Ecstasy Text File (*.etxt);; All Files (*)"));
                    currentFile = fileName;

                    //Saving the file
                    QFile file(fileName);
                    QFileInfo fileInfo(file);
                    if(fileInfo.completeSuffix() == "etxt")
                    {
                        if(file.open(QIODevice::WriteOnly | QFile::Text))
                        {
                            ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), file.fileName());
                            QTextStream out (&file);
                            out << edit->toHtml();
                            file.close();
                            edit->setFocus();
                        }
                    }
                    else
                    {
                        if(file.open(QIODevice::WriteOnly | QFile::Text))
                        {
                            if(fileInfo.completeSuffix() == "cpp" || fileInfo.completeSuffix() == "hpp")
                            {
                                cppHighlighter = new CppSyntax(edit->document());
                                edit->setFont(QFont("Consolas"));
                                ui->fontComboBox->setCurrentFont(QFont("Consolas"));
                            }
                            ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), file.fileName());
                            QTextStream out (&file);
                            out << edit->toPlainText();
                            file.close();
                            edit->setFocus();
                        }
                    }
                    if (ui->tabWidget->count() > 1)
                    {
                        ui->tabWidget->removeTab(index);
                    }
                }
                else if(msgBox.clickedButton() == dontSave)
                {
                    if (ui->tabWidget->count() > 1)
                    {
                        ui->tabWidget->removeTab(index);
                    }
                }
                else{}
            }
            else
            {
                QFile veriFile(currentFile);
                QString content{};
                if(veriFile.open(QIODevice::ReadOnly | QFile::Text))
                {
                    QTextStream in(&veriFile);
                    content = in.readAll();
                    veriFile.close();
                }
                if(content != edit->toHtml())
                {
                    //Create a msg box to warn the user to save the file
                    QMessageBox msgBox;
                    QAbstractButton* save{msgBox.addButton(tr("Save"), QMessageBox::YesRole)};
                    QAbstractButton* dontSave{msgBox.addButton(tr("Don't save"), QMessageBox::NoRole)};
                    msgBox.addButton(tr("Cancel"), QMessageBox::RejectRole);
                    msgBox.setIcon(QMessageBox::Warning);
                    msgBox.setWindowTitle("Warning");
                    msgBox.setText("Do you want to save your changes to the document?");
                    msgBox.exec();
                    if(msgBox.clickedButton() == save)
                    {
                        //Saving the file
                        QFile file(currentFile);
                        QFileInfo fileInfo(file);
                        if(fileInfo.completeSuffix() == "etxt")
                        {
                            if(file.open(QIODevice::WriteOnly | QFile::Text))
                            {
                                ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), file.fileName());
                                QTextStream out (&file);
                                out << edit->toHtml();
                                file.close();
                                edit->setFocus();
                            }
                        }
                        else
                        {
                            if(file.open(QIODevice::WriteOnly | QFile::Text))
                            {
                                if(fileInfo.completeSuffix() == "cpp" || fileInfo.completeSuffix() == "hpp")
                                {
                                    cppHighlighter = new CppSyntax(edit->document());
                                    edit->setFont(QFont("Consolas"));
                                    ui->fontComboBox->setCurrentFont(QFont("Consolas"));
                                }
                                ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), file.fileName());
                                QTextStream out (&file);
                                out << edit->toPlainText();
                                file.close();
                                edit->setFocus();
                            }
                        }
                        if (ui->tabWidget->count() > 1)
                        {
                            ui->tabWidget->removeTab(index);
                        }
                    }
                    else if(msgBox.clickedButton() == dontSave)
                    {
                        if (ui->tabWidget->count() > 1)
                        {
                            ui->tabWidget->removeTab(index);
                        }
                    }
                    else {}
                }
                else
                {
                    if (ui->tabWidget->count() > 1)
                    {
                        ui->tabWidget->removeTab(index);
                    }
                }
            }
        }
    }
    else
    {
        if (ui->tabWidget->count() > 1)
        {
            ui->tabWidget->removeTab(index);
        }
    }
}

//Getting the tabWidget TextEdit
TextEdit* MainWindow::getTabTextEdit()
{
    return qobject_cast<TextEdit*>(ui->tabWidget->widget(ui->tabWidget->currentIndex()));
}

//On new file button clicked
void MainWindow::on_newFile_clicked()
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
    //Setting up colors
    int foreRed{obj["font"].toObject()["foregroundColor"].toObject()["red"].toInt()};
    int foreGreen{obj["font"].toObject()["foregroundColor"].toObject()["green"].toInt()};
    int foreBlue{obj["font"].toObject()["foregroundColor"].toObject()["blue"].toInt()};

    int backRed{obj["font"].toObject()["backgroundColor"].toObject()["red"].toInt()};
    int backGreen{obj["font"].toObject()["backgroundColor"].toObject()["green"].toInt()};
    int backBlue{obj["font"].toObject()["backgroundColor"].toObject()["blue"].toInt()};

    //Creating a new tab
    ui->tabWidget->addTab(new TextEdit(), QString("New Document " + QString::number(ui->tabWidget->count() + 1)));
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    //Resetting the currentFile variable
    currentFile = "";
    //Setting up the TextEdit in new tab
    QString fontName{obj["font"].toObject()["family"].toString()};
    int fontSize{obj["font"].toObject()["pointSize"].toInt()};
    TextEdit *edit{getTabTextEdit()};
    edit->setGeometry(0,0,ui->tabWidget->width() - 3, ui->tabWidget->height() - 59);
    if(obj["darkTheme"].toBool() == true)
    {
        edit->setStyleSheet("QTextEdit{background-color: rgb(38,38,38); color: white;}");
    }
    if(foreRed + foreGreen + foreBlue != 0)
        edit->setTextColor(QColor(foreRed, foreGreen, foreBlue));
    if(backRed + backGreen + backBlue != 765)
        edit->setTextBackgroundColor(QColor(backRed, backGreen, backBlue));
    edit->setFocus();
    edit->setFontPointSize(fontSize);
    edit->setFontFamily(fontName);
    ui->fontComboBox->setCurrentFont(QFont(fontName));
    ui->fontsize->setValue(fontSize);
    ui->fontComboBox->setCurrentFont(QFont(edit->currentFont()));
    ui->numOfLines->setText("Line: " + QString::number(edit->textCursor().blockNumber()+1));
    ui->numOfColumns->setText("Column: " + QString::number(edit->textCursor().positionInBlock()+1));
    QObject::connect(edit, &TextEdit::cursorPositionChanged, this, &MainWindow::cursorPosChanged);
}

//On open file button clicked
void MainWindow::on_openFile_clicked()
{
    //Getting TextEdit from tabWidget
    TextEdit *edit{getTabTextEdit()};

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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open a file"), path, tr("Ecstasy Text File (*.etxt);; All Files (*)"));
    QFile file(fileName);
    QFileInfo fileInfo(file);
    currentFile = fileName;
    if(fileInfo.completeSuffix() == "etxt")
    {
        if(file.open(QIODevice::ReadOnly | QFile::Text))
        {
           ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), file.fileName());
           edit->setHtml(file.readAll());
           file.close();
           edit->setFocus();
        }
    }
    else
    {
        if(file.open(QIODevice::ReadOnly | QFile::Text))
        {
            if(fileInfo.completeSuffix() == "cpp" || fileInfo.completeSuffix() == "hpp")
            {
                cppHighlighter = new CppSyntax(edit->document());
                edit->setFont(QFont("Consolas"));
                ui->fontComboBox->setCurrentFont(QFont("Consolas"));
            }
            ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), file.fileName());
            edit->setText(file.readAll());
            file.close();
            edit->setFocus();
        }
    }
}

//On save file clicked
void MainWindow::on_save_clicked()
{
    //Getting TextEdit from tabWidget
    TextEdit *edit{getTabTextEdit()};

    QString fileName;

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
    if(obj["defaultSavingLocation"].toString() == "Documents")
        path = QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    else
        path = obj["defaultSavingLocation"].toString();
    //Verifying currentFile variable
    if (currentFile.isEmpty())
    {
        fileName = QFileDialog::getSaveFileName(this, tr("Save a file"), path, tr("Ecstasy Text File (*.etxt);; All Files (*)"));
        currentFile = fileName;
    }
    else
    {
        fileName = currentFile;
    }

    //Saving the file
    QFile file(fileName);
    QFileInfo fileInfo(file);
    if(fileInfo.completeSuffix() == "etxt")
    {
        if(file.open(QIODevice::WriteOnly | QFile::Text))
        {
            ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), file.fileName());
            QTextStream out (&file);
            out << edit->toHtml();
            file.close();
            edit->setFocus();
        }
    }
    else
    {
        if(file.open(QIODevice::WriteOnly | QFile::Text))
        {
            if(fileInfo.completeSuffix() == "cpp" || fileInfo.completeSuffix() == "hpp")
            {
                cppHighlighter = new CppSyntax(edit->document());
                edit->setFont(QFont("Consolas"));
                ui->fontComboBox->setCurrentFont(QFont("Consolas"));
            }
            ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), file.fileName());
            QTextStream out (&file);
            out << edit->toPlainText();
            file.close();
            edit->setFocus();
        }
    }
}

//Paste function
void MainWindow::on_paste_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    edit->paste();
    edit->setFocus();
}

//Copy function
void MainWindow::on_copy_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    edit->copy();
    edit->setFocus();
}

//Cut function
void MainWindow::on_cut_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    edit->cut();
    edit->setFocus();
}

//On tab widget tab changed
void MainWindow::on_tabWidget_currentChanged(int index)
{
    TextEdit *edit{getTabTextEdit()};
    currentFile = "";
    QString tabText{ui->tabWidget->tabText(index)};
    if (!tabText.contains("New Document ", Qt::CaseSensitive))
    {
        currentFile = ui->tabWidget->tabText(index);
        ui->fontsize->setValue(edit->fontPointSize());
        ui->fontComboBox->setCurrentFont(QFont(edit->currentFont()));
    }
    else
    {
        ui->fontsize->setValue(edit->fontPointSize());
        ui->fontComboBox->setCurrentFont(QFont(edit->currentFont()));
    }
    edit->setGeometry(0,0,ui->tabWidget->width() - 3, ui->tabWidget->height() - 59);
    ui->numOfLines->setText("Line: " + QString::number(edit->textCursor().blockNumber()+1));
    ui->numOfColumns->setText("Column: " + QString::number(edit->textCursor().positionInBlock()+1));
    QObject::connect(edit, &TextEdit::cursorPositionChanged, this, &MainWindow::cursorPosChanged);
}

//On font combobox font changed
void MainWindow::on_fontComboBox_currentFontChanged(const QFont &f)
{
    QFont tempFont;
    tempFont.setFamily(f.family());
    tempFont.setPointSize(11);
    ui->fontComboBox->setFont(tempFont);
    TextEdit *edit{getTabTextEdit()};
    edit->setCurrentFont(f);
    edit->setFontPointSize(ui->fontsize->value());
}

//On fontsize spinbox value changed
void MainWindow::on_fontsize_valueChanged(int arg1)
{
    TextEdit *edit{getTabTextEdit()};
    edit->setFontPointSize(arg1);
}

//Increasing the font of the textEdit
void MainWindow::on_increaseFont_clicked()
{
    //Setting the spinbox value
    ui->fontsize->setValue(ui->fontsize->value() + 2);
    TextEdit *edit{getTabTextEdit()};
    //Verifying if the fontsize is less than 200
    if(ui->fontsize->value() != 200)
    {
        edit->setFontPointSize(ui->fontsize->value());
        edit->setFocus();
    }
    else
    {
        //Creating an MsgBox to warn the user that he reached the maximum size
        QMessageBox incrmsgBox;
        incrmsgBox.setIcon(QMessageBox::Warning);
        incrmsgBox.setWindowTitle("Error");
        incrmsgBox.setText("Cannot increase more than 200. Maximum reached.");
        incrmsgBox.setStandardButtons(QMessageBox::Ok);
        incrmsgBox.exec();
    }
}

//Decreasing the font of the textEdit
void MainWindow::on_decreaseFont_clicked()
{
    //Setting the spinbox value
    ui->fontsize->setValue(ui->fontsize->value() - 2);
    TextEdit *edit{getTabTextEdit()};
    //Verifying if the fontsize is more than 2
    if(ui->fontsize->value() != 2)
        {
            edit->setFontPointSize(ui->fontsize->value());
            edit->setFocus();
        }
        else
        {
            //Creating an MsgBox to warn the user that he reached the minimum size
            QMessageBox decrmsgBox;
            decrmsgBox.setIcon(QMessageBox::Warning);
            decrmsgBox.setWindowTitle("Error");
            decrmsgBox.setText("Cannot decrease more than 2. Minimum reached.");
            decrmsgBox.setStandardButtons(QMessageBox::Ok);
            decrmsgBox.exec();
        }
}

//Putting the text in bold function
void MainWindow::on_boldBtn_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    if(ui->boldBtn->isChecked())
    {
        edit->setFontWeight(QFont::Bold);
        edit->setFocus();
    }
    else
    {
        edit->setFontWeight(QFont::Normal);
        edit->setFocus();
    }
}

//Putting the text in italics function
void MainWindow::on_italicBtn_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    if(ui->italicBtn->isChecked())
    {
        edit->setFontItalic(true);
        edit->setFocus();
    }
    else
    {
        edit->setFontItalic(false);
        edit->setFocus();
    }
}

//Underlining in bold function
void MainWindow::on_underlineBtn_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    if(ui->underlineBtn->isChecked())
    {
        edit->setFontUnderline(true);
        edit->setFocus();
    }
    else
    {
        edit->setFontUnderline(false);
        edit->setFocus();
    }
}

//Setting the backcolor of the selected text
void MainWindow::on_backcolorbtn_clicked()
{
    QFile file(QCoreApplication::applicationDirPath() + "/settings.json");
    QByteArray content;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        content = file.readAll();
        file.close();
    }

    QJsonParseError *errPars{new QJsonParseError()};
    QJsonDocument jsonDoc{QJsonDocument::fromJson(content, errPars)};
    QJsonObject obj{jsonDoc.object()};

    int backRed{obj["font"].toObject()["backgroundColor"].toObject()["red"].toInt()};
    int backGreen{obj["font"].toObject()["backgroundColor"].toObject()["green"].toInt()};
    int backBlue{obj["font"].toObject()["backgroundColor"].toObject()["blue"].toInt()};

    TextEdit *edit{getTabTextEdit()};
    QColorDialog colorDialog;
    colorDialog.setWindowTitle("Choose a color");
    colorDialog.setCurrentColor(QColor(backRed, backGreen, backBlue));
    if (colorDialog.exec() == QDialog::Accepted)
    {
        QColor color = colorDialog.currentColor();
        edit->setTextBackgroundColor(color);
        edit->setFocus();
        QPalette palette = ui->backColor_lbl->palette();
        palette.setColor(QPalette::Window, color);
        ui->backColor_lbl->setPalette(palette);
    }
}

//Setting the forecolor of the selected text
void MainWindow::on_forecolorbtn_clicked()
{
    QFile file(QCoreApplication::applicationDirPath() + "/settings.json");
    QByteArray content;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        content = file.readAll();
        file.close();
    }

    QJsonParseError *errPars{new QJsonParseError()};
    QJsonDocument jsonDoc{QJsonDocument::fromJson(content, errPars)};
    QJsonObject obj{jsonDoc.object()};

    int foreRed{obj["font"].toObject()["foregroundColor"].toObject()["red"].toInt()};
    int foreGreen{obj["font"].toObject()["foregroundColor"].toObject()["green"].toInt()};
    int foreBlue{obj["font"].toObject()["foregroundColor"].toObject()["blue"].toInt()};

    TextEdit *edit{getTabTextEdit()};
    QColorDialog colorDialog;
    colorDialog.setWindowTitle("Choose a color");
    colorDialog.setCurrentColor(QColor(foreRed, foreGreen, foreBlue));
    if(colorDialog.exec() == QDialog::Accepted)
    {
        QColor color {colorDialog.currentColor()};
        edit->setTextColor(color);
        edit->setFocus();
        QPalette palette{ui->forecolor_lbl->palette()};
        palette.setColor(QPalette::Window, color);
        ui->forecolor_lbl->setPalette(palette);
    }
}

//Saving the file with name
void MainWindow::on_saveas_clicked()
{
    TextEdit *edit{getTabTextEdit()};

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
    if(obj["defaultSavingLocation"].toString() == "Documents")
        path = QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    else
        path = obj["defaultSavingLocation"].toString();

    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, tr("Save a file"), path, tr("Ecstasy Text File (*.etxt);; All Files (*)"));
    QFile file(fileName);
    QFileInfo fileInfo(file);
    if(fileInfo.completeSuffix() == "etxt")
    {
        if(file.open(QIODevice::WriteOnly | QFile::Text))
        {
            ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), file.fileName());
            QTextStream out (&file);
            out << edit->toHtml();
            file.close();
            edit->setFocus();
        }
    }
    else
    {
        if(file.open(QIODevice::WriteOnly | QFile::Text))
        {
            if(fileInfo.completeSuffix() == "cpp" || fileInfo.completeSuffix() == "hpp")
            {
                cppHighlighter = new CppSyntax(edit->document());
                edit->setFont(QFont("Consolas"));
                ui->fontComboBox->setCurrentFont(QFont("Consolas"));
            }
            ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), file.fileName());
            QTextStream out (&file);
            out << edit->toPlainText();
            file.close();
            edit->setFocus();
        }
    }
}

//Printing the content of the textEdit
void MainWindow::on_print_clicked()
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

    //Setting up the printer
    QPrinter printer;
    printer.setResolution(QPrinter::HighResolution);
    printer.setPageSize(QPageSize::A4);
    if(obj["printHorizontally"].toBool() == false)
        printer.setPageOrientation(QPageLayout::Portrait);
    else
        printer.setPageOrientation(QPageLayout::Landscape);
    if(obj["printWithColors"].toBool() == false)
        printer.setColorMode(QPrinter::GrayScale);
    else
        printer.setColorMode(QPrinter::Color);
    //Creating the page setup dialog
    QPageSetupDialog *pageSetup = new QPageSetupDialog(&printer, this);
    //Creating the printpreview dialog
    QPrintPreviewDialog *printPrev = new QPrintPreviewDialog(&printer);
    //QObject::connecting printPrev paint signal to print slot
    QObject::connect(printPrev, &QPrintPreviewDialog::paintRequested, this, &MainWindow::print);
    if(pageSetup->exec() == QDialog::Accepted)
    {
        printPrev->exec();
    }
}

//Print slot
void MainWindow::print(QPrinter *p)
{
    TextEdit *edit{getTabTextEdit()};
    edit->print(p);
}

//On textEdit text changed
void MainWindow::edit_changed()
{
    TextEdit *edit{getTabTextEdit()};
    if(edit->toPlainText() == "")
    {
        edit->setCurrentFont(ui->fontComboBox->font());
        edit->setFontPointSize(ui->fontsize->value());
    }
}

//To upper function
void MainWindow::toUpper()
{
    TextEdit *edit{getTabTextEdit()};
    QTextCursor cursor{edit->textCursor()};
    if(cursor.hasSelection())
    {
        cursor.insertText(cursor.selectedText().toUpper());
    }
}

//To lower function
void MainWindow::toLower()
{
    TextEdit *edit{getTabTextEdit()};
    QTextCursor cursor = edit->textCursor();
    if(cursor.hasSelection())
    {
        cursor.insertText(cursor.selectedText().toLower());
    }
}

//Enabling superscripts
void MainWindow::on_superscript_clicked()
{

    TextEdit *edit{getTabTextEdit()};
    if(subscriptEnabled == true)
    {
        subscriptEnabled = false;
        ui->subscript->setChecked(false);
    }
    if(superscriptEnabled == false)
    {
        QTextCharFormat format;
        format.setVerticalAlignment(QTextCharFormat::AlignSuperScript);
        edit->mergeCurrentCharFormat(format);
        edit->setFocus();
        superscriptEnabled = true;
    }
    else if(superscriptEnabled == true)
    {
        QTextCharFormat format;
        format.setVerticalAlignment(QTextCharFormat::AlignNormal);
        edit->mergeCurrentCharFormat(format);
        edit->setFocus();
        superscriptEnabled = false;
    }
}

//Enabling subscripts
void MainWindow::on_subscript_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    if(superscriptEnabled == true)
    {
        superscriptEnabled = false;
        ui->superscript->setChecked(false);
    }
    if(subscriptEnabled == false)
    {
        QTextCharFormat format;
        format.setVerticalAlignment(QTextCharFormat::AlignSubScript);
        edit->mergeCurrentCharFormat(format);
        edit->setFocus();
        subscriptEnabled = true;
    }
    else if(subscriptEnabled == true)
    {
        QTextCharFormat format;
        format.setVerticalAlignment(QTextCharFormat::AlignNormal);
        edit->mergeCurrentCharFormat(format);
        edit->setFocus();
        subscriptEnabled = false;
    }
}


//Putting list in the TextEdit
void MainWindow::on_bullets_clicked()
{
    QTextListFormat listFormat;
    TextEdit *edit{getTabTextEdit()};
    if(ui->comboBox->currentText() == "Filled Circle")
    {
        listFormat.setStyle(QTextListFormat::ListDisc);
        edit->textCursor().insertList(listFormat);
        edit->setFocus();
    }
    else if(ui->comboBox->currentText() == "Empty Circle")
    {
        listFormat.setStyle(QTextListFormat::ListCircle);
        edit->textCursor().insertList(listFormat);
        edit->setFocus();
    }
    else if(ui->comboBox->currentText() == "Square")
    {
        listFormat.setStyle(QTextListFormat::ListSquare);
        edit->textCursor().insertList(listFormat);
        edit->setFocus();
    }
    else if(ui->comboBox->currentText() == "Decimal")
    {
        listFormat.setStyle(QTextListFormat::ListDecimal);
        edit->textCursor().insertList(listFormat);
        edit->setFocus();
    }
    else if(ui->comboBox->currentText() == "Lower Latin")
    {
        listFormat.setStyle(QTextListFormat::ListLowerAlpha);
        edit->textCursor().insertList(listFormat);
        edit->setFocus();
    }
    else if(ui->comboBox->currentText() == "Upper Latin")
    {
        listFormat.setStyle(QTextListFormat::ListUpperAlpha);
        edit->textCursor().insertList(listFormat);
        edit->setFocus();
    }
    else if(ui->comboBox->currentText() == "Lower Roman")
    {
        listFormat.setStyle(QTextListFormat::ListLowerRoman);
        edit->textCursor().insertList(listFormat);
        edit->setFocus();
    }
    else if(ui->comboBox->currentText() == "Upper Roman")
    {
        listFormat.setStyle(QTextListFormat::ListUpperRoman);
        edit->textCursor().insertList(listFormat);
        edit->setFocus();
    }
}

//Aligning the text to the left
void MainWindow::on_alignleft_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    ui->aligncenter->setChecked(false);
    ui->alignright->setChecked(false);
    ui->alignjustify->setChecked(false);
    QTextCursor cursor = edit->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignLeft);
    cursor.setBlockFormat(textBlockFormat);
    edit->setTextCursor(cursor);
    edit->setFocus();
}

//Aligning the text to the center
void MainWindow::on_aligncenter_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    ui->alignright->setChecked(false);
    ui->alignleft->setChecked(false);
    ui->alignjustify->setChecked(false);
    QTextCursor cursor = edit->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignCenter);
    cursor.setBlockFormat(textBlockFormat);
    edit->setTextCursor(cursor);
    edit->setFocus();
}

//Aligning the text to the right
void MainWindow::on_alignright_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    ui->alignleft->setChecked(false);
    ui->aligncenter->setChecked(false);
    ui->alignjustify->setChecked(false);
    QTextCursor cursor = edit->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignRight);
    cursor.setBlockFormat(textBlockFormat);
    edit->setTextCursor(cursor);
    edit->setFocus();
}

//Align Justify
void MainWindow::on_alignjustify_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    ui->alignleft->setChecked(false);
    ui->alignright->setChecked(false);
    ui->aligncenter->setChecked(false);
    QTextCursor cursor = edit->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignJustify);
    cursor.setBlockFormat(textBlockFormat);
    edit->setTextCursor(cursor);
    edit->setFocus();
}

//Adding an image to the textedit
void MainWindow::on_addImage_clicked()
{
    TextEdit *edit{getTabTextEdit()};
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
    QString path{""};
    if(obj["defaultPictureLocation"].toString() == "Pictures")
    {
        path = QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation));
    }
    else
        path = obj["defaultPictureLocation"].toString();
    QString file = QFileDialog::getOpenFileName(this, "Select an image", path, tr("JPEG (*.jpg *.jpeg *.jif);; PNG (*.png);; Bitmap Files (*.bmp);; All Files (*)"));
    QFileInfo fileInfo(file);
    QImage image(file);
    QByteArray bArray;
    QBuffer buffer(&bArray);
    QUrl Uri;
    if(fileInfo.completeSuffix() == "jpg" || fileInfo.completeSuffix() == "jpeg" || fileInfo.completeSuffix() == "jif")
    {
        image.save(&buffer, "JPEG");
        QString base64Img = bArray.toBase64();
        Uri.setUrl("data:image/jpg;base64," + base64Img);
    }
    else if(fileInfo.completeSuffix() == "png")
    {
        image.save(&buffer, "PNG");
        QString base64Img = bArray.toBase64();
        Uri.setUrl("data:image/png;base64," + base64Img);
    }
    else if(fileInfo.completeSuffix() == "bmp")
    {
        image.save(&buffer, "BMP");
        QString base64Img = bArray.toBase64();
        Uri.setUrl("data:image/bmp;base64," + base64Img);
    }
    else
    {
        image.save(&buffer, "PNG");
        QString base64Img = bArray.toBase64();
        Uri.setUrl("data:image/png;base64," + base64Img);
    }
    QTextDocument * textDocument{edit->document()};
    textDocument->addResource(QTextDocument::ImageResource, Uri, QVariant(image));
    QTextCursor cursor{edit->textCursor()};
    QTextImageFormat imageFormat;
    imageFormat.setWidth(image.width());
    imageFormat.setHeight(image.height());
    imageFormat.setName(Uri.toString());
    cursor.insertImage(imageFormat);
    edit->setCurrentFont(ui->fontComboBox->font());
    edit->setFontPointSize(ui->fontsize->value());
}

//global variables needed by addTable func
int lineNum;
int columnNum;
//Adding tables to the TextEdit
void MainWindow::on_addTable_clicked()
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

    QWidget *popup = new QWidget(ui->addTable, Qt::Popup );
    QLabel *lines = new QLabel("Number of lines: ");
    QSpinBox *linesSpinBox = new QSpinBox();
    QLabel *columns = new QLabel("Number of columns: ");
    QSpinBox *columnSpinBox = new QSpinBox();
    QPushButton *addTable = new QPushButton("Insert Table");
    QPixmap addTableIcon;
    addTableIcon.load(":Images/insert table.png");
    addTable->setIconSize(QSize(31,31));
    addTable->setIcon(QIcon(addTableIcon));
    addTable->setFlat(true);
    addTable->setToolTip("Insert Table");
    QPalette widgPalette{popup->palette()};
    popup->setAutoFillBackground(true);

    if(obj["darkTheme"].toBool() == true)
    {
        widgPalette.setColor(QPalette::Window, QColor(60,60,60));
        lines->setStyleSheet("QLabel{color: white;}");
        columns->setStyleSheet("QLabel{color:white;}");
        linesSpinBox->setStyleSheet("QSpinBox{background-color: rgb(54,54,54);} QSpinBox, QLineEdit{color:white;}");
        columnSpinBox->setStyleSheet("QSpinBox{background-color: rgb(54,54,54);} QSpinBox, QLineEdit{color:white;}");
        addTable->setStyleSheet("QPushButton{color:white;}");
    }
    else
    {
        widgPalette.setColor(QPalette::Window, QColor(243,243,243));
        addTable->setStyleSheet("QPushButton{color:black;}");
    }

    popup->setPalette(widgPalette);
    //Setting the default spinboxes values
    linesSpinBox->setValue(2);
    columnSpinBox->setValue(2);

    //Giving the two global variabled the default values
    lineNum = linesSpinBox->value();
    columnNum = linesSpinBox->value();
    //Setting the layout to the pop-up menu
    QFormLayout *layout = new QFormLayout(popup);
    layout->addRow(lines, linesSpinBox);
    layout->addRow(columns, columnSpinBox);
    layout->addRow(addTable);

    //Positioning the pop-up menu
    QPoint popupTopLeft = ui->addTable->mapToGlobal(ui->addTable->rect().bottomLeft());
    popup->setGeometry(QRect(popupTopLeft, QSize(150, 100)));
    popup->show();

    //QObject::connecting spinboxes signals
    QObject::connect(linesSpinBox, &QSpinBox::valueChanged, this, &MainWindow::linesChanged);
    QObject::connect(columnSpinBox, &QSpinBox::valueChanged, this, &MainWindow::columnsChanged);

    //QObject::connecting the clicked signal from addTable to its function
    QObject::connect(addTable, &QPushButton::clicked, this, &MainWindow::insertTable);
}

//inserting the table
void MainWindow::insertTable()
{
    TextEdit *edit{getTabTextEdit()};
    edit->textCursor().insertTable(lineNum, columnNum);
    lineNum = 2;
    columnNum = 2;
    edit->setFontPointSize(ui->fontsize->value());
}

//Setting lines for tables
void MainWindow::linesChanged(int arg1)
{
    lineNum = arg1;
}

//Setting columns for tables
void MainWindow::columnsChanged(int arg1)
{
    columnNum = arg1;
}

//Setting up lists when u change the content of the comboBox
void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    QTextListFormat listFormat;
    TextEdit *edit{getTabTextEdit()};
    if(arg1 == "Filled Circle")
    {
        listFormat.setStyle(QTextListFormat::ListDisc);
        edit->textCursor().insertList(listFormat);
        edit->setFocus();
    }
    else if(arg1 == "Empty Circle")
    {
        listFormat.setStyle(QTextListFormat::ListCircle);
        edit->textCursor().insertList(listFormat);
        edit->setFocus();
    }
    else if(arg1 == "Square")
    {
        listFormat.setStyle(QTextListFormat::ListSquare);
        edit->textCursor().insertList(listFormat);
        edit->setFocus();
    }
    else if(arg1 == "Decimal")
    {
        listFormat.setStyle(QTextListFormat::ListDecimal);
        edit->textCursor().insertList(listFormat);
        edit->setFocus();
    }
    else if(arg1 == "Lower Latin")
    {
        listFormat.setStyle(QTextListFormat::ListLowerAlpha);
        edit->textCursor().insertList(listFormat);
        edit->setFocus();
    }
    else if(arg1 == "Upper Latin")
    {
        listFormat.setStyle(QTextListFormat::ListUpperAlpha);
        edit->textCursor().insertList(listFormat);
        edit->setFocus();
    }
    else if(arg1 == "Lower Roman")
    {
        listFormat.setStyle(QTextListFormat::ListLowerRoman);
        edit->textCursor().insertList(listFormat);
        edit->setFocus();
    }
    else if(arg1 == "Upper Roman")
    {
        listFormat.setStyle(QTextListFormat::ListUpperRoman);
        edit->textCursor().insertList(listFormat);
        edit->setFocus();
    }
}

//Adding a file content to the current document
void MainWindow::on_addFromFile_clicked()
{
    //Getting TextEdit from tabWidget
    TextEdit *edit{getTabTextEdit()};

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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open a file"), path, tr("Ecstasy Text File (*.etxt);; All Files (*)"));
    QFile file(fileName);
    QFileInfo fileInfo(file);
    currentFile = fileName;
    if(fileInfo.completeSuffix() == "etxt")
    {
        if(file.open(QIODevice::ReadOnly | QFile::Text))
        {
           ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), file.fileName());
           QTextStream in(&file);
           edit->textCursor().insertHtml(in.readAll());
           file.close();
           edit->setFocus();
        }
    }
    else
    {
        if(file.open(QIODevice::ReadOnly | QFile::Text))
        {
           ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), file.fileName());
           QTextStream in(&file);
           edit->textCursor().insertText(in.readAll());
           file.close();
           edit->setFocus();
        }
    }
}

//Going to the home section
void MainWindow::on_homeButton_clicked()
{
    QFile file(QCoreApplication::applicationDirPath() + "/settings.json");
    QByteArray content;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        content = file.readAll();
        file.close();
    }

    QJsonParseError *errPars{new QJsonParseError()};
    QJsonDocument jsonDoc{QJsonDocument::fromJson(content, errPars)};
    QJsonObject jo{jsonDoc.object()};
    //Setting the colors to the toolbar
    int red{jo["toolBarColor"].toObject()["red"].toInt()};
    int green{jo["toolBarColor"].toObject()["green"].toInt()};
    int blue{jo["toolBarColor"].toObject()["blue"].toInt()};
    ui->stackedWidget->setCurrentIndex(0);
    if(jo["darkTheme"].toBool() == false)
        homePalette.setColor(QPalette::Button, QColor(243,243,243));
    else
        homePalette.setColor(QPalette::Button, QColor(54,54,54));
    designPalette.setColor(QPalette::Button, QColor(red,green,blue));
    miscPalette.setColor(QPalette::Button, QColor(red,green,blue));
    ui->homeButton->setPalette(homePalette);
    ui->designButton->setPalette(designPalette);
    ui->miscellaniousButton->setPalette(miscPalette);
    ui->homeButton->setEnabled(false);
    ui->designButton->setEnabled(true);
    ui->miscellaniousButton->setEnabled(true);
}

//Setting up the font button
void MainWindow::on_fontBtn_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    //Setting up the new font selected
    if (fontSelected)
    {
        edit->setCurrentFont(font);
        QFont tempFont = font;
        tempFont.setPointSize(11);
        ui->fontComboBox->setCurrentText(font.family());
        ui->fontComboBox->setFont(tempFont);
        ui->fontsize->setValue(tempFont.pointSize());
    }
}

//Going to the design section
void MainWindow::on_designButton_clicked()
{
    QFile file(QCoreApplication::applicationDirPath() + "/settings.json");
    QByteArray content;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        content = file.readAll();
        file.close();
    }

    QJsonParseError *errPars{new QJsonParseError()};
    QJsonDocument jsonDoc{QJsonDocument::fromJson(content, errPars)};
    QJsonObject jo{jsonDoc.object()};
    //Setting the colors to the toolbar
    int red{jo["toolBarColor"].toObject()["red"].toInt()};
    int green{jo["toolBarColor"].toObject()["green"].toInt()};
    int blue{jo["toolBarColor"].toObject()["blue"].toInt()};
    ui->stackedWidget->setCurrentIndex(1);
    if(jo["darkTheme"].toBool() == false)
        designPalette.setColor(QPalette::Button, QColor(243,243,243));
    else
        designPalette.setColor(QPalette::Button, QColor(54,54,54));
    homePalette.setColor(QPalette::Button, QColor(red,green,blue));
    miscPalette.setColor(QPalette::Button, QColor(red,green,blue));
    ui->homeButton->setPalette(homePalette);
    ui->designButton->setPalette(designPalette);
    ui->miscellaniousButton->setPalette(miscPalette);
    ui->designButton->setEnabled(false);
    ui->homeButton->setEnabled(true);
    ui->miscellaniousButton->setEnabled(true);
}

//Selects all the text when clicked
void MainWindow::on_selectAll_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    edit->selectAll();
    edit->setFocus();
}

//Undo
void MainWindow::on_undo_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    edit->undo();
    edit->setFocus();
}

//Redo
void MainWindow::on_redo_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    edit->redo();
    edit->setFocus();
}

//Global Variables for Find Function
QString text_to_find{};
//On Find button clicked
void MainWindow::on_find_clicked()
{
    text_to_find = "";
    TextEdit *edit{getTabTextEdit()};
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
    if(!edit->isReadOnly())
    {
        QWidget *popup{new QWidget(ui->find, Qt::Popup )};
        QLabel *findWhat{new QLabel("Find What:")};
        QLineEdit *findEdit{new QLineEdit()};
        QPushButton *find{new QPushButton("Find All")};
        QFormLayout *layout = new QFormLayout(popup);
        layout->addRow(findWhat, findEdit);
        layout->setSpacing(15);
        layout->addRow(find);
        find->setToolTip("Find the text.");
        find->setFlat(true);
        QPalette widgPalette{popup->palette()};
        popup->setAutoFillBackground(true);

        if(obj["darkTheme"].toBool() == true)
        {
            widgPalette.setColor(QPalette::Window, QColor(60,60,60));
            findWhat->setStyleSheet("QLabel{color: white;}");
            findEdit->setStyleSheet("QLineEdit{background-color: rgb(54,54,54); color: white;}");
            find->setStyleSheet("QPushButton{color:white;}");
        }
        else
        {
            widgPalette.setColor(QPalette::Window, QColor(243,243,243));
            find->setStyleSheet("QPushButton{color:black;}");
            findEdit->setStyleSheet("QLineEdit{color: black;}");
        }
        popup->setPalette(widgPalette);
        QPoint popupTopRight{ui->find->mapToGlobal(ui->find->rect().bottomLeft())};
        popup->setGeometry(popupTopRight.x() - 170, popupTopRight.y(), 200, 50);
        popup->show();

        QObject::connect(findEdit, &QLineEdit::textChanged, this, &MainWindow::findText_changed);
        QObject::connect(find, &QPushButton::clicked, this, &MainWindow::findText_clicked);
    }
    else
    {
        ui->find->setIcon(QIcon(":/Images/find.png"));
        edit->setReadOnly(false);
        edit->undo();
        edit->setFocus();
    }
}

void MainWindow::findText_changed(const QString &arg1)
{
    text_to_find = arg1;
}

void MainWindow::findText_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    QTextDocument *document{edit->document()};
    bool found{false};
    if (text_to_find.isEmpty())
    {
        QMessageBox::information(this, tr("Empty Search Field"), "The search field is empty. Please enter a word and click Find.");
    }
    else
    {

        QTextCursor highlightCursor(document);
        QTextCursor cursor(document);

        cursor.beginEditBlock();

        QTextCharFormat plainFormat(highlightCursor.charFormat());
        QTextCharFormat colorFormat{plainFormat};
        colorFormat.setBackground(Qt::yellow);

        while (!highlightCursor.isNull() && !highlightCursor.atEnd())
        {
            highlightCursor = document->find(text_to_find, highlightCursor, QTextDocument::FindCaseSensitively | QTextDocument::FindFlags());

            if (!highlightCursor.isNull())
            {
                found = true;
                highlightCursor.mergeCharFormat(colorFormat);
            }
        }
        if (found == false)
        {
            QMessageBox::information(this, tr("Word Not Found"), "Sorry, the word cannot be found.");
        }
        cursor.endEditBlock();
        if(found == true)
        {
            edit->setReadOnly(true);
            ui->find->setIcon(QIcon(":/Images/close.png"));
            QMessageBox::information(this, tr("Words Found"), "All the instances have been found. Click on the X to toggle off the Find View.");
        }
    }
}

void MainWindow::cursorPosChanged()
{
    TextEdit *edit{getTabTextEdit()};
    ui->numOfLines->setText("Line: " + QString::number(edit->textCursor().blockNumber()+1));
    ui->numOfColumns->setText("Column: " + QString::number(edit->textCursor().positionInBlock()+1));
}

QString text_to_find2{};
QString text_to_replace{};
void MainWindow::on_replace_clicked()
{
    text_to_find2 = "";
    TextEdit *edit{getTabTextEdit()};
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
    if(!edit->isReadOnly())
    {
        QWidget *popup{new QWidget(ui->replace, Qt::Popup )};
        QLabel *findWhat{new QLabel("Find What:")};
        QLineEdit *findEdit{new QLineEdit()};
        QLabel *replaceWith{new QLabel("Replace With:")};
        QLineEdit *replaceEdit{new QLineEdit()};
        QPushButton *find{new QPushButton("Find All")};
        QPushButton *replaceNext{new QPushButton("Replace Next")};
        QPushButton *replaceAll{new QPushButton("Replace All")};
        QFormLayout *layout{new QFormLayout(popup)};
        QHBoxLayout *layout2{new QHBoxLayout()};
        layout->addRow(findWhat, findEdit);
        layout->setSpacing(10);
        layout->addRow(replaceWith, replaceEdit);
        layout2->addWidget(replaceNext);
        layout2->addWidget(replaceAll);
        layout->addRow(find, layout2);
        find->setToolTip("Find Text");
        find->setFlat(true);
        replaceNext->setToolTip("Replace Next");
        replaceNext->setFlat(true);
        replaceAll->setToolTip("Replace All");
        replaceAll->setFlat(true);
        QPalette widgPalette{popup->palette()};
        popup->setAutoFillBackground(true);
        if(obj["darkTheme"].toBool() == true)
        {
            widgPalette.setColor(QPalette::Window, QColor(60,60,60));
            findWhat->setStyleSheet("QLabel{color: white;}");
            findEdit->setStyleSheet("QLineEdit{background-color: rgb(54,54,54); color: white;}");
            replaceWith->setStyleSheet("QLabel{color: white;}");
            replaceNext->setStyleSheet("QPushButton{color:white;}");
            replaceAll->setStyleSheet("QPushButton{color:white;}");
            replaceEdit->setStyleSheet("QLineEdit{background-color: rgb(54,54,54); color: white;}");
            find->setStyleSheet("QPushButton{color:white;}");
        }
        else
        {
            widgPalette.setColor(QPalette::Window, QColor(243,243,243));
            find->setStyleSheet("QPushButton{color:black;}");
            findEdit->setStyleSheet("QLineEdit{color: black;}");
            replaceAll->setStyleSheet("QPushButton{color:black;}");
            replaceNext->setStyleSheet("QPushButton{color: black;}");
            replaceEdit->setStyleSheet("QLineEdit{color:white;}");
        }

        popup->setPalette(widgPalette);
        QPoint popupTopRight{ui->replace->mapToGlobal(ui->replace->rect().bottomLeft())};
        popup->setGeometry(popupTopRight.x() - 220, popupTopRight.y(), 250, 100);
        popup->show();

        QObject::connect(findEdit, &QLineEdit::textChanged, this, &MainWindow::findReplaceText_changed);
        QObject::connect(find, &QPushButton::clicked, this, &MainWindow::find_clicked);
        QObject::connect(replaceEdit, &QLineEdit::textChanged, this, &MainWindow::replaceText_changed);
        QObject::connect(replaceNext, &QPushButton::clicked, this, &MainWindow::replaceNext_clicked);
        QObject::connect(replaceAll, &QPushButton::clicked, this, &MainWindow::replaceAll_clicked);
    }
    else
    {
        ui->replace->setIcon(QIcon(":/Images/find and replace.png"));
        edit->setReadOnly(false);
        edit->undo();
        edit->setFocus();
    }
}

void MainWindow::findReplaceText_changed(const QString &text)
{
    text_to_find2 = text;
}

void MainWindow::find_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    QTextDocument *document{edit->document()};
    bool found{false};
    if(text_to_find2.isEmpty())
    {
        QMessageBox::information(this, tr("Empty Search Field"), "The search field is empty. Please enter a word and click Find.");
    }
    else
    {
        QTextCursor highlightCursor(document);
        QTextCursor cursor(document);

        cursor.beginEditBlock();

        QTextCharFormat plainFormat(highlightCursor.charFormat());
        QTextCharFormat colorFormat{plainFormat};
        colorFormat.setBackground(Qt::yellow);

        while(!highlightCursor.isNull() && !highlightCursor.atEnd())
        {
            highlightCursor = document->find(text_to_find2, highlightCursor, QTextDocument::FindCaseSensitively | QTextDocument::FindFlags());

            if (!highlightCursor.isNull())
            {
                found = true;
                highlightCursor.mergeCharFormat(colorFormat);
            }
        }
        if(found == false)
        {
            QMessageBox::information(this, tr("Word Not Found"), "Sorry, the word cannot be found.");
        }
        cursor.endEditBlock();
        if(found == true)
        {
            edit->setReadOnly(true);
            ui->replace->setIcon(QIcon(":/Images/close.png"));
            QMessageBox::information(this, tr("Words Found"), "All the instances have been found. Click on the X to toggle off the Find View.");
        }
    }
}

void MainWindow::replaceText_changed(const QString &text)
{
    text_to_replace = text;
}

void MainWindow::replaceNext_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    QTextDocument *document{edit->document()};
    bool found{false};
    if(!edit->isReadOnly())
    {
        if(text_to_find2.isEmpty())
        {
            QMessageBox::information(this, tr("Empty Search Field"), "The search field is empty. Please enter a word and click Find.");
        }
        if(text_to_replace.isEmpty())
        {
            QMessageBox::information(this, tr("Empty Replace Field"), "The replace field is empty. Please enter a word and click Replace.");
        }
        else
        {
            QTextCursor highlightCursor(document);
            QTextCursor cursor(document);
            cursor.beginEditBlock();
            highlightCursor = document->find(text_to_find2, highlightCursor, QTextDocument::FindCaseSensitively | QTextDocument::FindFlags());
            if(!highlightCursor.isNull())
            {
                found = true;
                highlightCursor.insertText(text_to_replace);

            }
            if(found == false)
            {
                QMessageBox::information(this, tr("Word Not Found"), "Sorry, the word cannot be found.");
            }
            cursor.endEditBlock();
        }
    }
    else
    {
        QMessageBox::information(this, tr("Error"), "Sorry, you cannot replace in find view. Remove it by clicking the X icon and try again.");
    }
}

void MainWindow::replaceAll_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    QTextDocument *document{edit->document()};
    bool found{false};
    int occurences{0};
    if(!edit->isReadOnly())
    {
        if(text_to_find2.isEmpty())
        {
            QMessageBox::information(this, tr("Empty Search Field"), "The search field is empty. Please enter a word and click Find.");
        }
        if (text_to_replace.isEmpty())
        {
            QMessageBox::information(this, tr("Empty Replace Field"), "The replace field is empty. Please enter a word and click Replace.");
        }
        else
        {
            QTextCursor highlightCursor(document);
            QTextCursor cursor(document);

            cursor.beginEditBlock();

            while(!highlightCursor.isNull() && !highlightCursor.atEnd())
            {
                highlightCursor = document->find(text_to_find2, highlightCursor, QTextDocument::FindCaseSensitively | QTextDocument::FindFlags());

                if (!highlightCursor.isNull())
                {
                    found = true;
                    highlightCursor.insertText(text_to_replace);
                    occurences += 1;
                }
            }
            if(found == true)
                QMessageBox::information(this, tr("All Result Replaced"), QString::number(occurences)+ " occurences replaced.");
            else
                QMessageBox::information(this, tr("Word Not Found"), "Sorry, the word cannot be found.");
            cursor.endEditBlock();
        }
    }
    else
    {
        QMessageBox::information(this, tr("Error"), "Sorry, you cannot replace in find view. Remove it by clicking the X icon and try again.");
    }
}

//Styles
void MainWindow::on_normal_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    QTextCursor cursor(edit->textCursor());
    QFont font;
    font.setFamily("Calibri");
    font.setPointSize(11);
    QTextCharFormat format{cursor.charFormat()};
    format.setFont(font);
    format.setForeground(Qt::black);
    QTextBlockFormat form;
    form.setAlignment(Qt::AlignLeft);
    if(cursor.hasSelection())
    {
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    else
    {
        cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    edit->setFocus();
    ui->fontComboBox->setCurrentFont(font.family());
    ui->fontsize->setValue(font.pointSize());
    ui->boldBtn->setChecked(false);
    ui->italicBtn->setChecked(false);
    ui->underlineBtn->setChecked(false);
    ui->alignleft->setChecked(true);
    ui->aligncenter->setChecked(false);
    ui->alignright->setChecked(false);
    ui->alignjustify->setChecked(false);
}

void MainWindow::on_heading1_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    QTextCursor cursor(edit->textCursor());
    QFont font;
    font.setFamily("Calibri Light");
    font.setPointSize(16);
    QTextCharFormat format{cursor.charFormat()};
    format.setFont(font);
    format.setForeground(QColor(47,84,150));
    QTextBlockFormat form;
    form.setAlignment(Qt::AlignLeft);
    if(cursor.hasSelection())
    {
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    else
    {
        cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    edit->setFocus();
    ui->fontComboBox->setCurrentFont(font.family());
    ui->fontsize->setValue(font.pointSize());
    ui->boldBtn->setChecked(false);
    ui->italicBtn->setChecked(false);
    ui->underlineBtn->setChecked(false);
    ui->alignleft->setChecked(true);
    ui->aligncenter->setChecked(false);
    ui->alignright->setChecked(false);
    ui->alignjustify->setChecked(false);
}


void MainWindow::on_heading2_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    QTextCursor cursor(edit->textCursor());
    QFont font;
    font.setFamily("Calibri Light");
    font.setPointSize(13);
    QTextCharFormat format{cursor.charFormat()};
    format.setFont(font);
    format.setForeground(QColor(47,84,150));
    QTextBlockFormat form;
    form.setAlignment(Qt::AlignLeft);
    if(cursor.hasSelection())
    {
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    else
    {
        cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    edit->setFocus();
    ui->fontComboBox->setCurrentFont(font.family());
    ui->fontsize->setValue(font.pointSize());
    ui->boldBtn->setChecked(false);
    ui->italicBtn->setChecked(false);
    ui->underlineBtn->setChecked(false);
    ui->alignleft->setChecked(true);
    ui->aligncenter->setChecked(false);
    ui->alignright->setChecked(false);
    ui->alignjustify->setChecked(false);
}


void MainWindow::on_heading3_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    QTextCursor cursor(edit->textCursor());
    QFont font;
    font.setFamily("Calibri Light");
    font.setPointSize(12);
    QTextCharFormat format{cursor.charFormat()};
    format.setFont(font);
    format.setForeground(QColor(31,55,99));
    QTextBlockFormat form;
    form.setAlignment(Qt::AlignLeft);
    if(cursor.hasSelection())
    {
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    else
    {
        cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    edit->setFocus();
    ui->fontComboBox->setCurrentFont(font.family());
    ui->fontsize->setValue(font.pointSize());
    ui->boldBtn->setChecked(false);
    ui->italicBtn->setChecked(false);
    ui->underlineBtn->setChecked(false);
    ui->alignleft->setChecked(true);
    ui->aligncenter->setChecked(false);
    ui->alignright->setChecked(false);
    ui->alignjustify->setChecked(false);
}


void MainWindow::on_title_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    QTextCursor cursor(edit->textCursor());
    QFont font;
    font.setFamily("Calibri Light");
    font.setPointSize(28);
    QTextCharFormat format{cursor.charFormat()};
    format.setFont(font);
    format.setForeground(Qt::black);
    QTextBlockFormat form;
    form.setAlignment(Qt::AlignLeft);
    if(cursor.hasSelection())
    {
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    else
    {
        cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    edit->setFocus();
    ui->fontComboBox->setCurrentFont(font.family());
    ui->fontsize->setValue(font.pointSize());
    ui->boldBtn->setChecked(false);
    ui->italicBtn->setChecked(false);
    ui->underlineBtn->setChecked(false);
    ui->alignleft->setChecked(true);
    ui->aligncenter->setChecked(false);
    ui->alignright->setChecked(false);
    ui->alignjustify->setChecked(false);
}


void MainWindow::on_subtitle_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    QTextCursor cursor(edit->textCursor());
    QFont font;
    font.setFamily("Calibri");
    font.setPointSize(11);
    font.setLetterSpacing(QFont::AbsoluteSpacing, 1);
    QTextCharFormat format{cursor.charFormat()};
    format.setFont(font);
    format.setForeground(QColor(90,90,90));
    QTextBlockFormat form;
    form.setAlignment(Qt::AlignLeft);
    if(cursor.hasSelection())
    {
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    else
    {
        cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    edit->setFocus();
    ui->fontComboBox->setCurrentFont(font.family());
    ui->fontsize->setValue(font.pointSize());
    ui->boldBtn->setChecked(false);
    ui->italicBtn->setChecked(false);
    ui->underlineBtn->setChecked(false);
    ui->alignleft->setChecked(true);
    ui->aligncenter->setChecked(false);
    ui->alignright->setChecked(false);
    ui->alignjustify->setChecked(false);
}


void MainWindow::on_subtitle_emphasis_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    QTextCursor cursor(edit->textCursor());
    QFont font;
    font.setFamily("Calibri");
    font.setPointSize(11);
    font.setItalic(true);
    QTextCharFormat format{cursor.charFormat()};
    format.setFont(font);
    format.setForeground(QColor(64,64,64));
    QTextBlockFormat form;
    form.setAlignment(Qt::AlignLeft);
    if(cursor.hasSelection())
    {
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    else
    {
        cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    edit->setFocus();
    ui->fontComboBox->setCurrentFont(font.family());
    ui->fontsize->setValue(font.pointSize());
    ui->italicBtn->setChecked(true);
    ui->boldBtn->setChecked(false);
    ui->underlineBtn->setChecked(false);
    ui->alignleft->setChecked(true);
    ui->aligncenter->setChecked(false);
    ui->alignright->setChecked(false);
    ui->alignjustify->setChecked(false);
}


void MainWindow::on_emphasis_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    QTextCursor cursor(edit->textCursor());
    QFont font;
    font.setFamily("Calibri");
    font.setPointSize(11);
    font.setItalic(true);
    QTextCharFormat format{cursor.charFormat()};
    format.setFont(font);
    format.setForeground(Qt::black);
    QTextBlockFormat form;
    form.setAlignment(Qt::AlignLeft);
    if(cursor.hasSelection())
    {
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    else
    {
        cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    edit->setFocus();
    ui->fontComboBox->setCurrentFont(font.family());
    ui->fontsize->setValue(font.pointSize());
    ui->italicBtn->setChecked(true);
    ui->boldBtn->setChecked(false);
    ui->underlineBtn->setChecked(false);
    ui->alignleft->setChecked(true);
    ui->aligncenter->setChecked(false);
    ui->alignright->setChecked(false);
    ui->alignjustify->setChecked(false);
}

void MainWindow::on_intense_emphasis_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    QTextCursor cursor(edit->textCursor());
    QFont font;
    font.setFamily("Calibri");
    font.setPointSize(11);
    font.setItalic(true);
    QTextCharFormat format{cursor.charFormat()};
    format.setFont(font);
    format.setForeground(QColor(68,114,196));
    QTextBlockFormat form;
    form.setAlignment(Qt::AlignLeft);
    if(cursor.hasSelection())
    {
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    else
    {
        cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    edit->setFocus();
    ui->fontComboBox->setCurrentFont(font.family());
    ui->fontsize->setValue(font.pointSize());
    ui->italicBtn->setChecked(true);
    ui->boldBtn->setChecked(false);
    ui->underlineBtn->setChecked(false);
    ui->alignleft->setChecked(true);
    ui->aligncenter->setChecked(false);
    ui->alignright->setChecked(false);
    ui->alignjustify->setChecked(false);
}


void MainWindow::on_strong_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    QTextCursor cursor(edit->textCursor());
    QFont font;
    font.setFamily("Calibri");
    font.setPointSize(11);
    font.setBold(true);
    QTextCharFormat format{cursor.charFormat()};
    format.setFont(font);
    format.setForeground(Qt::black);
    QTextBlockFormat form;
    form.setAlignment(Qt::AlignLeft);
    if(cursor.hasSelection())
    {
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    else
    {
        cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    edit->setFocus();
    ui->fontComboBox->setCurrentFont(font.family());
    ui->fontsize->setValue(font.pointSize());
    ui->boldBtn->setChecked(true);
    ui->italicBtn->setChecked(false);
    ui->underlineBtn->setChecked(false);
    ui->alignleft->setChecked(true);
    ui->aligncenter->setChecked(false);
    ui->alignright->setChecked(false);
    ui->alignjustify->setChecked(false);
}

void MainWindow::on_quote_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    QTextCursor cursor(edit->textCursor());
    QFont font;
    font.setFamily("Calibri");
    font.setPointSize(11);
    font.setItalic(true);
    QTextCharFormat format{cursor.charFormat()};
    format.setFont(font);
    format.setForeground(QColor(64,64,64));
    QTextBlockFormat form;
    form.setAlignment(Qt::AlignCenter);
    if(cursor.hasSelection())
    {
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    else
    {
        cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    edit->setFocus();
    ui->fontComboBox->setCurrentFont(font.family());
    ui->fontsize->setValue(font.pointSize());
    ui->italicBtn->setChecked(true);
    ui->boldBtn->setChecked(false);
    ui->underlineBtn->setChecked(false);
    ui->alignleft->setChecked(false);
    ui->aligncenter->setChecked(true);
    ui->alignright->setChecked(false);
    ui->alignjustify->setChecked(false);
}


void MainWindow::on_subtitle_reference_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    QTextCursor cursor(edit->textCursor());
    QFont font;
    font.setFamily("Calibri");
    font.setPointSize(11);
    QTextCharFormat format{cursor.charFormat()};
    format.setFont(font);
    format.setForeground(QColor(90,90,90));
    QTextBlockFormat form;
    form.setAlignment(Qt::AlignLeft);
    if(cursor.hasSelection())
    {
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    else
    {
        cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    edit->setFocus();
    ui->fontComboBox->setCurrentFont(font.family());
    ui->fontsize->setValue(font.pointSize());
    ui->boldBtn->setChecked(false);
    ui->italicBtn->setChecked(false);
    ui->underlineBtn->setChecked(false);
    ui->alignleft->setChecked(true);
    ui->aligncenter->setChecked(false);
    ui->alignright->setChecked(false);
    ui->alignjustify->setChecked(false);
}


void MainWindow::on_intense_reference_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    QTextCursor cursor(edit->textCursor());
    QFont font;
    font.setFamily("Calibri");
    font.setPointSize(11);
    font.setBold(true);
    QTextCharFormat format{cursor.charFormat()};
    format.setFont(font);
    format.setForeground(QColor(47,84,150));
    QTextBlockFormat form;
    form.setAlignment(Qt::AlignLeft);
    if(cursor.hasSelection())
    {
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    else
    {
        cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    edit->setFocus();
    ui->fontComboBox->setCurrentFont(font.family());
    ui->fontsize->setValue(font.pointSize());
    ui->boldBtn->setChecked(true);
    ui->alignleft->setChecked(true);
    ui->aligncenter->setChecked(false);
    ui->alignright->setChecked(false);
    ui->alignjustify->setChecked(false);
}
void MainWindow::on_miscellaniousButton_clicked()
{
    QFile file(QCoreApplication::applicationDirPath() + "/settings.json");
    QByteArray content;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        content = file.readAll();
        file.close();
    }

    QJsonParseError *errPars{new QJsonParseError()};
    QJsonDocument jsonDoc{QJsonDocument::fromJson(content, errPars)};
    QJsonObject jo{jsonDoc.object()};
    //Setting the colors to the toolbar
    int red{jo["toolBarColor"].toObject()["red"].toInt()};
    int green{jo["toolBarColor"].toObject()["green"].toInt()};
    int blue{jo["toolBarColor"].toObject()["blue"].toInt()};
    ui->stackedWidget->setCurrentIndex(2);
    homePalette.setColor(QPalette::Button, QColor(red,green,blue));
    designPalette.setColor(QPalette::Button, QColor(red,green,blue));
    if(jo["darkTheme"].toBool() == false)
        miscPalette.setColor(QPalette::Button, QColor(243,243,243));
    else
        miscPalette.setColor(QPalette::Button, QColor(54,54,54));
    ui->homeButton->setPalette(homePalette);
    ui->designButton->setPalette(designPalette);
    ui->miscellaniousButton->setPalette(miscPalette);
    ui->designButton->setEnabled(true);
    ui->homeButton->setEnabled(true);
    ui->miscellaniousButton->setEnabled(false);
}


void MainWindow::on_heading4_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    QTextCursor cursor(edit->textCursor());
    QFont font;
    font.setFamily("Calibri Light");
    font.setPointSize(11);
    font.setItalic(true);
    QTextCharFormat format{cursor.charFormat()};
    format.setFont(font);
    format.setForeground(QColor(47,84,150));
    QTextBlockFormat form;
    form.setAlignment(Qt::AlignLeft);
    if(cursor.hasSelection())
    {
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    else
    {
        cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    edit->setFocus();
    ui->fontComboBox->setCurrentFont(font.family());
    ui->fontsize->setValue(font.pointSize());
    ui->italicBtn->setChecked(true);
    ui->boldBtn->setChecked(false);
    ui->underlineBtn->setChecked(false);
    ui->alignleft->setChecked(true);
    ui->aligncenter->setChecked(false);
    ui->alignright->setChecked(false);
    ui->alignjustify->setChecked(false);
}


void MainWindow::on_heading5_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    QTextCursor cursor(edit->textCursor());
    QFont font;
    font.setFamily("Calibri Light");
    font.setPointSize(11);
    QTextCharFormat format{cursor.charFormat()};
    format.setFont(font);
    format.setForeground(QColor(47,84,150));
    QTextBlockFormat form;
    form.setAlignment(Qt::AlignLeft);
    if(cursor.hasSelection())
    {
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    else
    {
        cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    edit->setFocus();
    ui->fontComboBox->setCurrentFont(font.family());
    ui->fontsize->setValue(font.pointSize());
    ui->boldBtn->setChecked(false);
    ui->italicBtn->setChecked(false);
    ui->underlineBtn->setChecked(false);
    ui->alignleft->setChecked(true);
    ui->aligncenter->setChecked(false);
    ui->alignright->setChecked(false);
    ui->alignjustify->setChecked(false);
}


void MainWindow::on_heading6_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    QTextCursor cursor(edit->textCursor());
    QFont font;
    font.setFamily("Calibri Light");
    font.setPointSize(11);
    QTextCharFormat format{cursor.charFormat()};
    format.setFont(font);
    format.setForeground(QColor(31,55,99));
    QTextBlockFormat form;
    form.setAlignment(Qt::AlignLeft);
    if(cursor.hasSelection())
    {
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    else
    {
        cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    edit->setFocus();
    ui->fontComboBox->setCurrentFont(font.family());
    ui->fontsize->setValue(font.pointSize());
    ui->boldBtn->setChecked(false);
    ui->italicBtn->setChecked(false);
    ui->underlineBtn->setChecked(false);
    ui->alignleft->setChecked(true);
    ui->aligncenter->setChecked(false);
    ui->alignright->setChecked(false);
    ui->alignjustify->setChecked(false);
}


void MainWindow::on_heading8_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    QTextCursor cursor(edit->textCursor());
    QFont font;
    font.setFamily("Calibri Light");
    font.setPointSize(10);
    QTextCharFormat format{cursor.charFormat()};
    format.setFont(font);
    format.setForeground(QColor(39,39,39));
    QTextBlockFormat form;
    form.setAlignment(Qt::AlignLeft);
    if(cursor.hasSelection())
    {
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    else
    {
        cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    edit->setFocus();
    ui->fontComboBox->setCurrentFont(font.family());
    ui->fontsize->setValue(font.pointSize());
    ui->boldBtn->setChecked(false);
    ui->italicBtn->setChecked(false);
    ui->underlineBtn->setChecked(false);
    ui->alignleft->setChecked(true);
    ui->aligncenter->setChecked(false);
    ui->alignright->setChecked(false);
    ui->alignjustify->setChecked(false);
}


void MainWindow::on_heading9_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    QTextCursor cursor(edit->textCursor());
    QFont font;
    font.setFamily("Calibri Light");
    font.setPointSize(10);
    font.setItalic(true);
    QTextCharFormat format{cursor.charFormat()};
    format.setFont(font);
    format.setForeground(QColor(39,39,39));
    QTextBlockFormat form;
    form.setAlignment(Qt::AlignLeft);
    if(cursor.hasSelection())
    {
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    else
    {
        cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    edit->setFocus();
    ui->fontComboBox->setCurrentFont(font.family());
    ui->fontsize->setValue(font.pointSize());
    ui->italicBtn->setChecked(true);
    ui->boldBtn->setChecked(false);
    ui->underlineBtn->setChecked(false);
    ui->alignleft->setChecked(true);
    ui->aligncenter->setChecked(false);
    ui->alignright->setChecked(false);
    ui->alignjustify->setChecked(false);
}


void MainWindow::on_heading7_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    QTextCursor cursor(edit->textCursor());
    QFont font;
    font.setFamily("Calibri Light");
    font.setPointSize(11);
    font.setItalic(true);
    QTextCharFormat format{cursor.charFormat()};
    format.setFont(font);
    format.setForeground(QColor(31,55,99));
    QTextBlockFormat form;
    form.setAlignment(Qt::AlignLeft);
    if(cursor.hasSelection())
    {
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    else
    {
        cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    edit->setFocus();
    ui->fontComboBox->setCurrentFont(font.family());
    ui->fontsize->setValue(font.pointSize());
    ui->italicBtn->setChecked(true);
    ui->boldBtn->setChecked(false);
    ui->underlineBtn->setChecked(false);
    ui->alignleft->setChecked(true);
    ui->aligncenter->setChecked(false);
    ui->alignright->setChecked(false);
    ui->alignjustify->setChecked(false);
}


void MainWindow::on_book_reference_clicked()
{
    TextEdit *edit{getTabTextEdit()};
    QTextCursor cursor(edit->textCursor());
    QFont font;
    font.setFamily("Calibri");
    font.setPointSize(11);
    font.setBold(true);
    font.setItalic(true);
    QTextCharFormat format{cursor.charFormat()};
    format.setFont(font);
    format.setForeground(Qt::black);
    QTextBlockFormat form;
    form.setAlignment(Qt::AlignLeft);
    if(cursor.hasSelection())
    {
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    else
    {
        cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        cursor.setCharFormat(format);
        cursor.mergeBlockFormat(form);
    }
    edit->setFocus();
    ui->fontComboBox->setCurrentFont(font.family());
    ui->fontsize->setValue(font.pointSize());
    ui->boldBtn->setChecked(true);
    ui->italicBtn->setChecked(true);
    ui->underlineBtn->setChecked(false);
    ui->alignleft->setChecked(true);
    ui->aligncenter->setChecked(false);
    ui->alignright->setChecked(false);
    ui->alignjustify->setChecked(false);
}

//Pops out an about dialog
void MainWindow::on_aboutBtn_clicked()
{
    about *abt{new about};
    abt->exec();
}


void MainWindow::on_settingBtn_clicked()
{
    settings *setting{new settings};
    setting->exec();
}
