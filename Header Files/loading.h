#ifndef LOADING_H
#define LOADING_H

#include <QDialog>
#include <QGraphicsDropShadowEffect>
#include <QTimer>

namespace Ui {
class loading;
}

class loading : public QDialog
{
    Q_OBJECT

public:
    explicit loading(QWidget *parent = nullptr);
    ~loading();

private slots:
    void updateProgressBar();
private:
    Ui::loading *ui;
    QTimer *timer{new QTimer()};
};

#endif // LOADING_H
