#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "TextEdit.h"
#include "cppsyntax.h"
#include <QMainWindow>
#include <QTextEdit>
#include <QWidget>
#include <QTabBar>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QAbstractButton>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonParseError>
#include <QBuffer>
#include <QScreen>
#include <QAction>
#include <QPropertyAnimation>
#include <QGraphicsColorizeEffect>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>
#include <QTreeWidget>
#include <QFont>
#include <QColorDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QMenu>
#include <QPrintPreviewDialog>
#include <QPageSetupDialog>
#include <QImageReader>
#include <QGraphicsDropShadowEffect>
#include <QPoint>
#include <QFormLayout>
#include <QFontDialog>
#include <QLineEdit>
#include <QTextBlock>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void onNewText(const QString &text, const QString &fileName, const QFileInfo &fileInfo);
    void edit_changed();
    void findText_changed(const QString &text);
    void findText_clicked();
    void findReplaceText_changed(const QString &text);
    void find_clicked();
    void replaceText_changed(const QString &text);
    void replaceNext_clicked();
    void replaceAll_clicked();
    void cursorPosChanged();
private slots:
    void resizeEvent(QResizeEvent *);
    void on_tabWidget_tabCloseRequested(int index);

    void on_newFile_clicked();
    TextEdit* getTabTextEdit();

    void on_openFile_clicked();

    void on_save_clicked();

    void on_paste_clicked();

    void on_copy_clicked();

    void on_cut_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_fontsize_valueChanged(int arg1);

    void on_increaseFont_clicked();

    void on_decreaseFont_clicked();

    void on_boldBtn_clicked();

    void on_italicBtn_clicked();

    void on_underlineBtn_clicked();

    void on_backcolorbtn_clicked();

    void on_forecolorbtn_clicked();

    void on_saveas_clicked();

    void on_print_clicked();

    void on_superscript_clicked();

    void on_subscript_clicked();


    void on_bullets_clicked();


    void on_alignleft_clicked();

    void on_aligncenter_clicked();

    void on_alignright_clicked();

    void on_alignjustify_clicked();

    void print(QPrinter *p);
    void on_addImage_clicked();

    void on_addTable_clicked();

    void insertTable();

    void linesChanged(int arg1);

    void columnsChanged(int arg1);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_addFromFile_clicked();

    void on_homeButton_clicked();

    void on_fontBtn_clicked();

    void on_designButton_clicked();

    void on_selectAll_clicked();

    void on_undo_clicked();

    void on_redo_clicked();

    void on_find_clicked();
    void toUpper();
    void toLower();

    void on_replace_clicked();

    void on_normal_clicked();

    void on_heading1_clicked();

    void on_heading2_clicked();

    void on_heading3_clicked();

    void on_title_clicked();

    void on_subtitle_clicked();

    void on_subtitle_emphasis_clicked();

    void on_emphasis_clicked();

    void on_intense_emphasis_clicked();

    void on_strong_clicked();

    void on_quote_clicked();

    void on_subtitle_reference_clicked();

    void on_intense_reference_clicked();

    void on_miscellaniousButton_clicked();

    void on_heading4_clicked();

    void on_heading5_clicked();

    void on_heading6_clicked();

    void on_heading8_clicked();

    void on_heading9_clicked();

    void on_heading7_clicked();

    void on_book_reference_clicked();

    void on_aboutBtn_clicked();

    void on_settingBtn_clicked();

private:
    Ui::MainWindow *ui;
    QString currentFile;
    QPalette homePalette;
    QPalette designPalette;
    QPalette miscPalette;
    CppSyntax *cppHighlighter;
};
#endif // MAINWINDOW_H
