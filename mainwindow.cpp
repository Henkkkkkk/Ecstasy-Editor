#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "splashscreen.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Set MainWindow minimum size
    this->setMinimumHeight(440);
    this->setMinimumWidth(440);

    //Setting backcolor label border
    ui->label->setStyleSheet("QLabel { border: 1px solid black; }");

    //Setting the windows color
    QPalette thisColor = this->palette();
    thisColor.setColor(this->backgroundRole(), QColor(243,243,243));
    this->setPalette(thisColor);

    //Setting backcolor lbl palette
    QPalette palette = ui->backColor_lbl->palette();
    palette.setColor(ui->backColor_lbl->backgroundRole(), Qt::white);
    ui->backColor_lbl->setPalette(palette);

    //Setting forecolor label border
    ui->label_2->setStyleSheet("QLabel { border: 1px solid black; }");

    //Setting foreoclor lbl palette
    QPalette palette2 = ui->forecolor_lbl->palette();
    palette2.setColor(ui->forecolor_lbl->backgroundRole(), Qt::black);
    ui->forecolor_lbl->setPalette(palette2);

    //Setting toUpwerMenu pop-up menu
    QMenu *toUpwerMenu = new QMenu(this);
    QAction *toUpper = new QAction("To Upper Case", this);
    QAction *toLower = new QAction("To Lower Case", this);
    //Connecting signals
    connect(toUpper, SIGNAL(triggered()), this, SLOT(toUpper()));
    connect(toLower, SIGNAL(triggered()), this, SLOT(toLower()));

    //Adding actions to the menu
    toUpwerMenu->addAction(toUpper);
    toUpwerMenu->addAction(toLower);
    ui->toUpwer->setMenu(toUpwerMenu);
}

//Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

//Global Variables
bool boldEnabled = false;
bool italicsEnabled = false;
bool underlineEnabled = false;
bool superscriptEnabled = false;
bool subscriptEnabled = false;

//On new text function (see splashscreen.cpp constructor to see connected functions)
void MainWindow::onNewText(const QString &text, const QString &fileName)
{
    ui->edit->setHtml(text);
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), fileName);
    currentFile = fileName;
}

//Mainwindo resize event
void MainWindow::resizeEvent(QResizeEvent *)
{
    ui->tabWidget->resize(this->width() + 3, this->height() - 87);
    ui->edit->resize(ui->tabWidget->width() - 6, ui->tabWidget->height() - 30);
}

//Closing tabs
void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if (ui->tabWidget->count() > 1)
    {
        ui->tabWidget->removeTab(index);
    }

}

//Getting the tabWidget QTextEdit
QTextEdit* MainWindow::getTabTextEdit()
{
    return qobject_cast <QTextEdit*>(ui->tabWidget->widget(ui->tabWidget->currentIndex()));
}

//On new file button clicked
void MainWindow::on_newFile_clicked()
{
    //Creating a new tab
    ui->tabWidget->addTab(new QTextEdit(), QString("New Document " + QString::number(ui->tabWidget->count() + 1)));
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    //Resetting the currentFile varibble
    currentFile = "";
    //Setting up the QTextEdit in new tab
    QTextEdit *edit = getTabTextEdit();
    edit->setFocus();
    edit->setFontPointSize(11);
    ui->fontsize->setValue(11);
}

//On open file button clicked
void MainWindow::on_openFile_clicked()
{
    //Getting QTextEdit from tabWidget
    QTextEdit *edit = getTabTextEdit();

    //Setting the document path
    QString documentPath = QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));

    //Opening the file
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open a file"), documentPath, tr("Ecstasy Text File (*.etxt);; All Files (*)"));
    QFile file(fileName);
    QFileInfo fileInfo(file);
    currentFile = fileName;
    if(fileInfo.completeSuffix() == "etxt")
    {
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            if(file.open(QIODevice::ReadOnly | QFile::Text))
            {
               ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), file.fileName());
               ui->edit->setHtml(file.readAll());
               file.close();
               ui->edit->setFocus();
            }
        }
        else
        {
            if(file.open(QIODevice::ReadOnly | QFile::Text))
            {
               ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), file.fileName());
               edit->setHtml(file.readAll());
               file.close();
               edit->setFocus();
            }
        }
    }
    else
    {
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            if(file.open(QIODevice::ReadOnly | QFile::Text))
            {
               ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), file.fileName());
               ui->edit->setText(file.readAll());
               file.close();
               ui->edit->setFocus();
            }
        }
        else
        {
            if(file.open(QIODevice::ReadOnly | QFile::Text))
            {
               ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), file.fileName());
               edit->setText(file.readAll());
               file.close();
               edit->setFocus();
            }
        }
    }
}

//On save file clicked
void MainWindow::on_save_clicked()
{
    //Getting QTextEdit from tabWidget
    QTextEdit *edit = getTabTextEdit();

    QString fileName;

    //Setting the document path
    QString documentPath = QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    //Verifying currentFile variable
    if (currentFile.isEmpty())
    {
        fileName = QFileDialog::getSaveFileName(this, tr("Save a file"), documentPath, tr("Ecstasy Text File (*.etxt);; All Files (*)"));
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
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            if(file.open(QIODevice::WriteOnly | QFile::Text))
            {
                ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), file.fileName());
                QTextStream out (&file);
                out << ui->edit->toHtml();
                file.close();
                ui->edit->setFocus();
            }
        }
        else
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
    }
    else
    {
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            if(file.open(QIODevice::WriteOnly | QFile::Text))
            {
                ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), file.fileName());
                QTextStream out (&file);
                out << ui->edit->toPlainText();
                file.close();
                ui->edit->setFocus();
            }
        }
        else
        {
            if(file.open(QIODevice::WriteOnly | QFile::Text))
            {
                ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), file.fileName());
                QTextStream out (&file);
                out << edit->toPlainText();
                file.close();
                edit->setFocus();
            }
        }
    }
}

//Paste function
void MainWindow::on_paste_clicked()
{
    QTextEdit *edit = getTabTextEdit();
    if(ui->tabWidget->currentWidget() == ui->tab_1)
    {
        ui->edit->paste();
        ui->edit->setFocus();
    }
    else
    {
        edit->paste();
        edit->setFocus();
    }
}

//Copy function
void MainWindow::on_copy_clicked()
{
    QTextEdit *edit = getTabTextEdit();
    if(ui->tabWidget->currentWidget() == ui->tab_1)
    {
        ui->edit->copy();
        ui->edit->setFocus();
    }
    else
    {
        edit->copy();
        edit->setFocus();
    }
}

//Cut function
void MainWindow::on_cut_clicked()
{
    QTextEdit *edit = getTabTextEdit();
    if(ui->tabWidget->currentWidget() == ui->tab_1)
    {
        ui->edit->cut();
        ui->edit->setFocus();
    }
    else
    {
        edit->cut();
        edit->setFocus();
    }
}

//On tab widget tab changed
void MainWindow::on_tabWidget_currentChanged(int index)
{
    QTextEdit *edit = getTabTextEdit();
    currentFile = "";
    QString tabText = ui->tabWidget->tabText(index);
    if (!tabText.contains("New Document ", Qt::CaseSensitive))
    {
        currentFile = ui->tabWidget->tabText(index);
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            ui->fontsize->setValue(ui->edit->fontPointSize());
        }
        else
        {
            ui->fontsize->setValue(edit->fontPointSize());
        }
    }
}

//On font combobox font changed
void MainWindow::on_fontComboBox_currentFontChanged(const QFont &f)
{
    ui->fontComboBox->setFont(f);
    QTextEdit *edit = getTabTextEdit();

    if(ui->tabWidget->currentWidget() == ui->tab_1)
    {
        ui->edit->setCurrentFont(f);
        ui->edit->setFontPointSize(ui->fontsize->value());
    }
    else
    {
        edit->setCurrentFont(f);
        edit->setFontPointSize(ui->fontsize->value());
    }
}

//On fontsize spinbox value changed
void MainWindow::on_fontsize_valueChanged(int arg1)
{
    QTextEdit *edit = getTabTextEdit();
    if(ui->tabWidget->currentWidget() == ui->tab_1)
    {
        ui->edit->setFontPointSize(arg1);
    }
    else
    {
        edit->setFontPointSize(arg1);
    }
}

//Increasing the font of the textEdit
void MainWindow::on_increaseFont_clicked()
{
    //Setting the spinbox value
    ui->fontsize->setValue(ui->fontsize->value() + 2);
    QTextEdit *edit = getTabTextEdit();
    //Verifying if the fontsize is less than 200
    if(ui->fontsize->value() != 200)
    {
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            ui->edit->setFontPointSize(ui->edit->fontPointSize() + 2);
            ui->edit->setFocus();
        }
        else
        {
            edit->setFontPointSize(edit->fontPointSize() + 2);
            edit->setFocus();
        }
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
    QTextEdit *edit = getTabTextEdit();
    //Verifying if the fontsize is more than 2
    if(ui->fontsize->value() != 2)
        {
            if(ui->tabWidget->currentWidget() == ui->tab_1)
            {
                ui->edit->setFontPointSize(ui->edit->fontPointSize() - 2);
                ui->edit->setFocus();
            }
            else
            {
                edit->setFontPointSize(edit->fontPointSize() - 2);
                edit->setFocus();
            }
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
    QTextEdit *edit = getTabTextEdit();
    if(boldEnabled == false)
    {

        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            ui->edit->setFontWeight(QFont::Bold);
            ui->edit->setFocus();
        }
        else
        {
            edit->setFontWeight(QFont::Bold);
            edit->setFocus();
        }
        boldEnabled = true;
    }
    else if(boldEnabled == true)
    {
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            ui->edit->setFontWeight(QFont::Normal);
            ui->edit->setFocus();
        }
        else
        {
            edit->setFontWeight(QFont::Normal);
            edit->setFocus();
        }
        boldEnabled = false;
    }
}

//Putting the text in italics function
void MainWindow::on_italicBtn_clicked()
{
    QTextEdit *edit = getTabTextEdit();
    if(italicsEnabled == false)
    {
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            ui->edit->setFontItalic(true);
            ui->edit->setFocus();
        }
        else
        {
            edit->setFontItalic(true);
            edit->setFocus();
        }
        italicsEnabled = true;
    }
    else if(italicsEnabled == true)
    {
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            ui->edit->setFontItalic(false);
            ui->edit->setFocus();
        }
        else
        {
            edit->setFontItalic(false);
            edit->setFocus();
        }
        italicsEnabled = false;
    }
}

//Underlining in bold function
void MainWindow::on_underlineBtn_clicked()
{
    QTextEdit *edit = getTabTextEdit();
    if(underlineEnabled == false)
    {
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            ui->edit->setFontUnderline(true);
            ui->edit->setFocus();
        }
        else
        {
            edit->setFontUnderline(true);
            edit->setFocus();
        }
        underlineEnabled = true;
    }
    else if(underlineEnabled == true)
    {
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            ui->edit->setFontUnderline(false);
            ui->edit->setFocus();
        }
        else
        {
            edit->setFontUnderline(false);
            edit->setFocus();
        }
        underlineEnabled = false;
    }
}

//Setting the backcolor of the selected text
void MainWindow::on_backcolorbtn_clicked()
{
    QTextEdit *edit = getTabTextEdit();
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose a color", QColorDialog::DontUseNativeDialog);
    if(ui->tabWidget->currentWidget() == ui->tab_1)
    {
        ui->edit->setTextBackgroundColor(color);
        ui->edit->setFocus();
    }
    else
    {
        edit->setTextBackgroundColor(color);
        edit->setFocus();
    }
    QPalette palette = ui->backColor_lbl->palette();
    palette.setColor(ui->backColor_lbl->backgroundRole(), color);
    ui->backColor_lbl->setPalette(palette);
}

//Setting the forecolor of the selected text
void MainWindow::on_forecolorbtn_clicked()
{
    QTextEdit *edit = getTabTextEdit();
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose a color", QColorDialog::DontUseNativeDialog);
    if(ui->tabWidget->currentWidget() == ui->tab_1)
    {
        ui->edit->setTextColor(color);
        ui->edit->setFocus();
    }
    else
    {
        edit->setTextColor(color);
        edit->setFocus();
    }
    QPalette palette = ui->forecolor_lbl->palette();
    palette.setColor(ui->forecolor_lbl->backgroundRole(), color);
    ui->forecolor_lbl->setPalette(palette);
}

//Saving the file with name
void MainWindow::on_saveas_clicked()
{
    QTextEdit *edit = getTabTextEdit();
    QString documentPath = QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, tr("Save a file"), documentPath, tr("Ecstasy Text File (*.etxt);; All Files (*)"));
    QFile file(fileName);
    QFileInfo fileInfo(file);
    if(fileInfo.completeSuffix() == "etxt")
    {
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            if(file.open(QIODevice::WriteOnly | QFile::Text))
            {
                ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), file.fileName());
                QTextStream out (&file);
                out << ui->edit->toHtml();
                file.close();
                ui->edit->setFocus();
            }
        }
        else
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
    }
    else
    {
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            if(file.open(QIODevice::WriteOnly | QFile::Text))
            {
                ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), file.fileName());
                QTextStream out (&file);
                out << ui->edit->toPlainText();
                file.close();
                ui->edit->setFocus();
            }
        }
        else
        {
            if(file.open(QIODevice::WriteOnly | QFile::Text))
            {
                ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), file.fileName());
                QTextStream out (&file);
                out << edit->toPlainText();
                file.close();
                edit->setFocus();
            }
        }
    }
}

//Printing the content of the textEdit
void MainWindow::on_print_clicked()
{
    //Settig up the printer
    QPrinter printer;
    printer.setResolution(QPrinter::HighResolution);
    printer.setPageSize(QPageSize::A4);
    printer.setPageOrientation(QPageLayout::Portrait);
    //Creating the page setup dialog
    QPageSetupDialog *pageSetup = new QPageSetupDialog(&printer, this);
    //Creating the printpreview dialog
    QPrintPreviewDialog *printPrev = new QPrintPreviewDialog(&printer);
    //Connecting printPrev paint signal to print slot
    connect(printPrev, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print(QPrinter *)));
    if(pageSetup->exec() == QDialog::Accepted)
    {
        printPrev->exec();
    }
}

//Print slot
void MainWindow::print(QPrinter *p)
{
    QTextEdit *edit = getTabTextEdit();
    if(ui->tabWidget->currentWidget() == ui->tab_1)
    {
        ui->edit->print(p);
    }
    else
    {
        edit->print(p);
    }
}

//On textEdit text changed
void MainWindow::on_edit_textChanged()
{
    QTextEdit *edit = getTabTextEdit();
    if(ui->tabWidget->currentWidget() == ui->tab_1)
    {
        if(ui->edit->toPlainText() == "")
        {
            ui->edit->setFontPointSize(ui->fontsize->value());
        }
    }
    else
    {
        if(edit->toPlainText() == "")
        {
            edit->setFontPointSize(ui->fontsize->value());
        }
    }
}

//To upper function
void MainWindow::toUpper()
{
    QTextEdit *edit = getTabTextEdit();
    if(ui->tabWidget->currentWidget() == ui->tab_1)
    {
        QTextCursor cursor = ui->edit->textCursor();
        if(cursor.hasSelection())
        {
            cursor.insertText(cursor.selectedText().toUpper());
        }
    }
    else
    {
        QTextCursor cursor = edit->textCursor();
        if(cursor.hasSelection())
        {
            cursor.insertText(cursor.selectedText().toUpper());
        }
    }
}

//To lower function
void MainWindow::toLower()
{
    QTextEdit *edit = getTabTextEdit();
    if(ui->tabWidget->currentWidget() == ui->tab_1)
    {
        QTextCursor cursor = ui->edit->textCursor();
        if(cursor.hasSelection())
        {
            cursor.insertText(cursor.selectedText().toLower());
        }
    }
    else
    {
        QTextCursor cursor = edit->textCursor();
        if(cursor.hasSelection())
        {
            cursor.insertText(cursor.selectedText().toLower());
        }
    }
}

//Enabling superscripts
void MainWindow::on_superscript_clicked()
{

    QTextEdit *edit = getTabTextEdit();
    if(superscriptEnabled == false)
    {
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            QTextCharFormat format;
            format.setVerticalAlignment(QTextCharFormat::AlignSuperScript);
            ui->edit->mergeCurrentCharFormat(format);
            ui->edit->setFocus();
        }
        else
        {
            QTextCharFormat format;
            format.setVerticalAlignment(QTextCharFormat::AlignSuperScript);
            ui->edit->mergeCurrentCharFormat(format);
            edit->setFocus();
        }
        superscriptEnabled = true;
    }
    else if(superscriptEnabled == true)
    {
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            QTextCharFormat format;
            format.setVerticalAlignment(QTextCharFormat::AlignNormal);
            ui->edit->mergeCurrentCharFormat(format);
            ui->edit->setFocus();
        }
        else
        {
            QTextCharFormat format;
            format.setVerticalAlignment(QTextCharFormat::AlignNormal);
            ui->edit->mergeCurrentCharFormat(format);
            edit->setFocus();
        }
        superscriptEnabled = false;
    }
}

//Enabling subscripts
void MainWindow::on_subscript_clicked()
{
    QTextEdit *edit = getTabTextEdit();
    if(subscriptEnabled == false)
    {
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            QTextCharFormat format;
            format.setVerticalAlignment(QTextCharFormat::AlignSubScript);
            ui->edit->mergeCurrentCharFormat(format);
            ui->edit->setFocus();
        }
        else
        {
            QTextCharFormat format;
            format.setVerticalAlignment(QTextCharFormat::AlignSubScript);
            ui->edit->mergeCurrentCharFormat(format);
            edit->setFocus();
        }
        subscriptEnabled = true;
    }
    else if(subscriptEnabled == true)
    {
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            QTextCharFormat format;
            format.setVerticalAlignment(QTextCharFormat::AlignNormal);
            ui->edit->mergeCurrentCharFormat(format);
            ui->edit->setFocus();
        }
        else
        {
            QTextCharFormat format;
            format.setVerticalAlignment(QTextCharFormat::AlignNormal);
            ui->edit->mergeCurrentCharFormat(format);
            edit->setFocus();
        }
        subscriptEnabled = false;
    }
}


//Putting list in the qtextedit
void MainWindow::on_bullets_clicked()
{
    QTextListFormat listFormat;
    QTextEdit *edit = getTabTextEdit();
    if(ui->comboBox->currentText() == "Filled Circle")
    {
        listFormat.setStyle(QTextListFormat::ListDisc);
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            ui->edit->textCursor().insertList(listFormat);
            ui->edit->setFocus();
        }
        else
        {
            edit->textCursor().insertList(listFormat);
            edit->setFocus();
        }
    }
    else if(ui->comboBox->currentText() == "Empty Circle")
    {
        listFormat.setStyle(QTextListFormat::ListCircle);
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            ui->edit->textCursor().insertList(listFormat);
            ui->edit->setFocus();
        }
        else
        {
            edit->textCursor().insertList(listFormat);
            edit->setFocus();
        }
    }
    else if(ui->comboBox->currentText() == "Square")
    {
        listFormat.setStyle(QTextListFormat::ListSquare);
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            ui->edit->textCursor().insertList(listFormat);
            ui->edit->setFocus();
        }
        else
        {
            edit->textCursor().insertList(listFormat);
            edit->setFocus();
        }
    }
    else if(ui->comboBox->currentText() == "Decimal")
    {
        listFormat.setStyle(QTextListFormat::ListDecimal);
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            ui->edit->textCursor().insertList(listFormat);
            ui->edit->setFocus();
        }
        else
        {
            edit->textCursor().insertList(listFormat);
            edit->setFocus();
        }
    }
    else if(ui->comboBox->currentText() == "Lower Latin")
    {
        listFormat.setStyle(QTextListFormat::ListLowerAlpha);
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            ui->edit->textCursor().insertList(listFormat);
            ui->edit->setFocus();
        }
        else
        {
            edit->textCursor().insertList(listFormat);
            edit->setFocus();
        }
    }
    else if(ui->comboBox->currentText() == "Upper Latin")
    {
        listFormat.setStyle(QTextListFormat::ListUpperAlpha);
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            ui->edit->textCursor().insertList(listFormat);
            ui->edit->setFocus();
        }
        else
        {
            edit->textCursor().insertList(listFormat);
            edit->setFocus();
        }
    }
    else if(ui->comboBox->currentText() == "Lower Roman")
    {
        listFormat.setStyle(QTextListFormat::ListLowerRoman);
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            ui->edit->textCursor().insertList(listFormat);
            ui->edit->setFocus();
        }
        else
        {
            edit->textCursor().insertList(listFormat);
            edit->setFocus();
        }
    }
    else if(ui->comboBox->currentText() == "Upper Roman")
    {
        listFormat.setStyle(QTextListFormat::ListUpperRoman);
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            ui->edit->textCursor().insertList(listFormat);
            ui->edit->setFocus();
        }
        else
        {
            edit->textCursor().insertList(listFormat);
            edit->setFocus();
        }
    }
}

//Aligning the text to the left
void MainWindow::on_alignleft_clicked()
{
    QTextEdit *edit = getTabTextEdit();
    ui->aligncenter->setChecked(false);
    ui->alignright->setChecked(false);
    ui->alignjustify->setChecked(false);
    if(ui->tabWidget->currentWidget() == ui->tab_1)
    {
        QTextCursor cursor = ui->edit->textCursor();
        QTextBlockFormat textBlockFormat = cursor.blockFormat();
        textBlockFormat.setAlignment(Qt::AlignLeft);
        cursor.mergeBlockFormat(textBlockFormat);
        ui->edit->setTextCursor(cursor);
        ui->edit->setFocus();
    }
    else
    {
        QTextCursor cursor = edit->textCursor();
        QTextBlockFormat textBlockFormat = cursor.blockFormat();
        textBlockFormat.setAlignment(Qt::AlignLeft);
        cursor.mergeBlockFormat(textBlockFormat);
        edit->setTextCursor(cursor);
        edit->setFocus();
    }
}

//Aligning the text to the center
void MainWindow::on_aligncenter_clicked()
{
    QTextEdit *edit = getTabTextEdit();
    ui->alignright->setChecked(false);
    ui->alignleft->setChecked(false);
    ui->alignjustify->setChecked(false);
    if(ui->tabWidget->currentWidget() == ui->tab_1)
    {
        QTextCursor cursor = ui->edit->textCursor();
        QTextBlockFormat textBlockFormat = cursor.blockFormat();
        textBlockFormat.setAlignment(Qt::AlignCenter);
        cursor.mergeBlockFormat(textBlockFormat);
        ui->edit->setTextCursor(cursor);
        ui->edit->setFocus();
    }
    else
    {
        QTextCursor cursor = edit->textCursor();
        QTextBlockFormat textBlockFormat = cursor.blockFormat();
        textBlockFormat.setAlignment(Qt::AlignCenter);
        cursor.mergeBlockFormat(textBlockFormat);
        edit->setTextCursor(cursor);
        edit->setFocus();
    }
}

//Aligning the text to the right
void MainWindow::on_alignright_clicked()
{
    QTextEdit *edit = getTabTextEdit();
    ui->alignleft->setChecked(false);
    ui->aligncenter->setChecked(false);
    ui->alignjustify->setChecked(false);
    if(ui->tabWidget->currentWidget() == ui->tab_1)
    {
        QTextCursor cursor = ui->edit->textCursor();
        QTextBlockFormat textBlockFormat = cursor.blockFormat();
        textBlockFormat.setAlignment(Qt::AlignRight);
        cursor.mergeBlockFormat(textBlockFormat);
        ui->edit->setTextCursor(cursor);
        ui->edit->setFocus();
    }
    else
    {
        QTextCursor cursor = edit->textCursor();
        QTextBlockFormat textBlockFormat = cursor.blockFormat();
        textBlockFormat.setAlignment(Qt::AlignRight);
        cursor.mergeBlockFormat(textBlockFormat);
        edit->setTextCursor(cursor);
        edit->setFocus();
    }
}

//Align Justify
void MainWindow::on_alignjustify_clicked()
{
    QTextEdit *edit = getTabTextEdit();
    ui->alignleft->setChecked(false);
    ui->alignright->setChecked(false);
    ui->aligncenter->setChecked(false);
    if(ui->tabWidget->currentWidget() == ui->tab_1)
    {
        QTextCursor cursor = ui->edit->textCursor();
        QTextBlockFormat textBlockFormat = cursor.blockFormat();
        textBlockFormat.setAlignment(Qt::AlignJustify);
        cursor.mergeBlockFormat(textBlockFormat);
        ui->edit->setTextCursor(cursor);
        ui->edit->setFocus();
    }
    else
    {
        QTextCursor cursor = edit->textCursor();
        QTextBlockFormat textBlockFormat = cursor.blockFormat();
        textBlockFormat.setAlignment(Qt::AlignJustify);
        cursor.mergeBlockFormat(textBlockFormat);
        edit->setTextCursor(cursor);
        edit->setFocus();
    }
}

//Adding an image to the textedit
void MainWindow::on_addImage_clicked()
{
    QTextEdit *edit = getTabTextEdit();
    QString imagePath = QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation));
    QString file = QFileDialog::getOpenFileName(this, "Select an image", imagePath, tr("JPEG (*.jpg *.jpeg);; PNG (*.png);; Bitmap Files (*.bmp);; GIF (*.gif);; All Files (*)"));
    QUrl Uri(QString("%1").arg(file));
    QImage image = QImageReader (file).read();
    if(ui->tabWidget->currentWidget() == ui->tab_1)
    {
        QTextDocument * textDocument = ui->edit->document();
        textDocument->addResource(QTextDocument::ImageResource, Uri, QVariant(image));
        QTextCursor cursor = ui->edit->textCursor();
        QTextImageFormat imageFormat;
        imageFormat.setWidth(image.width());
        imageFormat.setHeight(image.height());
        imageFormat.setName(Uri.toString());
        cursor.insertImage(imageFormat);
    }
    else
    {
        QTextDocument * textDocument = edit->document();
        textDocument->addResource(QTextDocument::ImageResource, Uri, QVariant(image));
        QTextCursor cursor = edit->textCursor();
        QTextImageFormat imageFormat;
        imageFormat.setWidth(image.width());
        imageFormat.setHeight(image.height());
        imageFormat.setName(Uri.toString());
        cursor.insertImage(imageFormat);
    }
}

//global variables needed by addTable func
int lineNum;
int columnNum;
//Adding tables to the qtextEdit
void MainWindow::on_addTable_clicked()
{
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

    //Setting the default spinboxes values
    linesSpinBox->setValue(2);
    columnSpinBox->setValue(2);

    //Setting the layout to the pop-up menu
    QFormLayout *layout = new QFormLayout(popup);
    layout->addRow(lines, linesSpinBox);
    layout->addRow(columns, columnSpinBox);
    layout->addRow(addTable);

    //Positioning the pop-up menu
    QPoint popupTopLeft = ui->addTable->mapToGlobal(ui->addTable->rect().bottomLeft());
    popup->setGeometry(QRect(popupTopLeft , QSize(150,100)));
    popup->show();

    //Connecting spinboxes signals
    connect(linesSpinBox, SIGNAL(valueChanged(int)), this, SLOT(linesChanged(int)));
    connect(columnSpinBox, SIGNAL(valueChanged(int)), this, SLOT(columnsChanged(int)));

    //Connecting the clicked signal from addTable to its function
    connect(addTable, SIGNAL(clicked()), this, SLOT(insertTable()));
}

//inserting the table
void MainWindow::insertTable()
{
    QTextEdit *edit = getTabTextEdit();


    if(ui->tabWidget->currentWidget() == ui->tab_1)
    {
        ui->edit->textCursor().insertTable(lineNum, columnNum);
    }
    else
    {
        edit->textCursor().insertTable(lineNum, columnNum);
    }
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

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    QTextListFormat listFormat;
    QTextEdit *edit = getTabTextEdit();
    if(arg1 == "Filled Circle")
    {
        listFormat.setStyle(QTextListFormat::ListDisc);
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            ui->edit->textCursor().insertList(listFormat);
            ui->edit->setFocus();
        }
        else
        {
            edit->textCursor().insertList(listFormat);
            edit->setFocus();
        }
    }
    else if(arg1 == "Empty Circle")
    {
        listFormat.setStyle(QTextListFormat::ListCircle);
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            ui->edit->textCursor().insertList(listFormat);
            ui->edit->setFocus();
        }
        else
        {
            edit->textCursor().insertList(listFormat);
            edit->setFocus();
        }
    }
    else if(arg1 == "Square")
    {
        listFormat.setStyle(QTextListFormat::ListSquare);
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            ui->edit->textCursor().insertList(listFormat);
            ui->edit->setFocus();
        }
        else
        {
            edit->textCursor().insertList(listFormat);
            edit->setFocus();
        }
    }
    else if(arg1 == "Decimal")
    {
        listFormat.setStyle(QTextListFormat::ListDecimal);
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            ui->edit->textCursor().insertList(listFormat);
            ui->edit->setFocus();
        }
        else
        {
            edit->textCursor().insertList(listFormat);
            edit->setFocus();
        }
    }
    else if(arg1 == "Lower Latin")
    {
        listFormat.setStyle(QTextListFormat::ListLowerAlpha);
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            ui->edit->textCursor().insertList(listFormat);
            ui->edit->setFocus();
        }
        else
        {
            edit->textCursor().insertList(listFormat);
            edit->setFocus();
        }
    }
    else if(arg1 == "Upper Latin")
    {
        listFormat.setStyle(QTextListFormat::ListUpperAlpha);
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            ui->edit->textCursor().insertList(listFormat);
            ui->edit->setFocus();
        }
        else
        {
            edit->textCursor().insertList(listFormat);
            edit->setFocus();
        }
    }
    else if(arg1 == "Lower Roman")
    {
        listFormat.setStyle(QTextListFormat::ListLowerRoman);
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            ui->edit->textCursor().insertList(listFormat);
            ui->edit->setFocus();
        }
        else
        {
            edit->textCursor().insertList(listFormat);
            edit->setFocus();
        }
    }
    else if(arg1 == "Upper Roman")
    {
        listFormat.setStyle(QTextListFormat::ListUpperRoman);
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            ui->edit->textCursor().insertList(listFormat);
            ui->edit->setFocus();
        }
        else
        {
            edit->textCursor().insertList(listFormat);
            edit->setFocus();
        }
    }
}


void MainWindow::on_addFromFile_clicked()
{
    //Getting QTextEdit from tabWidget
    QTextEdit *edit = getTabTextEdit();

    //Setting the document path
    QString documentPath = QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));

    //Opening the file
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open a file"), documentPath, tr("Ecstasy Text File (*.etxt);; All Files (*)"));
    QFile file(fileName);
    QFileInfo fileInfo(file);
    currentFile = fileName;
    if(fileInfo.completeSuffix() == "etxt")
    {
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            if(file.open(QIODevice::ReadOnly | QFile::Text))
            {
               ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), file.fileName());
               QTextStream in(&file);
               QString content = in.readAll();
               QString prevContent = ui->edit->toHtml();
               ui->edit->setHtml(prevContent + content);
               file.close();
               ui->edit->setFocus();
            }
        }
        else
        {
            if(file.open(QIODevice::ReadOnly | QFile::Text))
            {
               ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), file.fileName());
               QTextStream in(&file);
               QString content = in.readAll();
               QString prevContent = edit->toHtml();
               edit->setHtml(prevContent + content);
               file.close();
               edit->setFocus();
            }
        }
    }
    else
    {
        if(ui->tabWidget->currentWidget() == ui->tab_1)
        {
            if(file.open(QIODevice::ReadOnly | QFile::Text))
            {
               ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), file.fileName());
               QTextStream in(&file);
               QString content = in.readAll();
               QString prevContent = ui->edit->toPlainText();
               ui->edit->setText(prevContent + content);
               file.close();
               ui->edit->setFocus();
            }
        }
        else
        {
            if(file.open(QIODevice::ReadOnly | QFile::Text))
            {
               ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), file.fileName());
               QTextStream in(&file);
               QString content = in.readAll();
               QString prevContent = edit->toPlainText();
               edit->setText(prevContent + content);
               file.close();
               edit->setFocus();
            }
        }
    }
}

