#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QNetworkProxy>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::checkSite);
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/new/prefix1/favicon.png"));
    trayIcon->setToolTip("RegistruMd");
    trayIcon->show();

    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &Widget::replyFinished);
    QNetworkRequest request;

    request.setUrl(QUrl("https://programari.registru.md/wp-admin/admin-ajax.php"));
    request.setRawHeader(QByteArray("Accept"), QByteArray("*"));
    request.setRawHeader(QByteArray("Origin"), QByteArray("https://programari.registru.md"));
    request.setRawHeader(QByteArray("X-Requested-With"), QByteArray("XMLHttpRequest"));
    request.setRawHeader(QByteArray("Content-Type"), QByteArray("application/x-www-form-urlencoded; charset=UTF-8"));
    manager->post(request,QByteArray("ProviderId=36&ServiceId=338&action=GetProviderAvailableDatesByService"));
    manager->post(request,QByteArray("Date=2019-07-26&ProviderId=36&ServiceId=338&action=GetProviderAvailableHoursByDate"));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::replyFinished(QNetworkReply *reply)
{
    QByteArray bt = reply->readAll();
    //qDebug()<<bt;
    bt.replace('"', ' ');
    bt.replace(']', ' ');
    bt.replace('[', ' ');

    QList<QByteArray> sp = bt.split(',');
    for(QByteArray ar: sp){
        ar = ar.trimmed();
        //qDebug()<<ar;
        QDate dt = QDate::fromString(ar, "yyyy-MM-dd");
        //qDebug()<<dt;
        if(dt < QDate(2020,1,15) && dt > QDate::currentDate()){
            qDebug()<<dt;
            trayIcon->showMessage("Warning!","Free date!!!\n"+dt.toString());
        }
    }
}

void Widget::checkSite()
{

   /* QEventLoop loop;
    connect(manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
    loop.exec();*/
    QNetworkRequest request;

    request.setUrl(QUrl("https://programari.registru.md/wp-admin/admin-ajax.php"));
    request.setRawHeader(QByteArray("Accept"), QByteArray("*"));
    request.setRawHeader(QByteArray("Origin"), QByteArray("https://programari.registru.md"));
    request.setRawHeader(QByteArray("X-Requested-With"), QByteArray("XMLHttpRequest"));
    request.setRawHeader(QByteArray("Content-Type"), QByteArray("application/x-www-form-urlencoded; charset=UTF-8"));

    QNetworkReply *re = manager->post(request,QByteArray("ProviderId=36&ServiceId=338&action=GetProviderAvailableDatesByService"));
    //re->waitForReadyRead(1000);
    //qDebug()<<re->readAll();
    //manager->post(request,QByteArray("Date=2019-07-26&ProviderId=36&ServiceId=338&action=GetProviderAvailableHoursByDate"));

}

void Widget::on_pushButton_clicked()
{
    qDebug()<<"Timer started";
    timer->start(1000);
}

void Widget::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);
    if (event -> type() == QEvent::WindowStateChange)
    {
        if (isMinimized())
        {
            this -> hide();
        }
    }
}
