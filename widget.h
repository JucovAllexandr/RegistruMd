#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSystemTrayIcon>
#include <QTimer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

    struct FreeDate{
        QDate date;
        QTime time;
    };


public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QNetworkAccessManager *manager;
    QTimer *timer;
    QSystemTrayIcon *trayIcon;
    void changeEvent(QEvent *event);

    bool isDataReceived = 0;
private slots:
    void replyFinished(QNetworkReply *reply);
    void checkSite();
    void on_pushButton_clicked();
};

#endif // WIDGET_H
