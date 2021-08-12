#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QWidget>
#include <QPropertyAnimation>
#include <QGraphicsColorizeEffect>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>
#include <QTreeWidget>
#include <QFont>
#include <QFontDatabase>
#include <QTreeWidgetItem>
#include <QListWidget>
#include <QListWidgetItem>
#include <QColorDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QMenu>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QSettings>
#include <QPrintPreviewDialog>
#include <QPageSetupDialog>
#include <QImageReader>
#include <QSpacerItem>
#include <QGraphicsDropShadowEffect>
#include <QPoint>
#include <QFormLayout>

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
    void onNewText(const QString &text, const QString &fileName);
    void toUpper();
    void toLower();
private slots:
    void resizeEvent(QResizeEvent *);
    void on_tabWidget_tabCloseRequested(int index);

    void on_newFile_clicked();
    QTextEdit* getTabTextEdit();

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

    void on_edit_textChanged();

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

private:
    Ui::MainWindow *ui;
    QString currentFile;
};
#endif // MAINWINDOW_H
