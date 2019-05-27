#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QNetworkAccessManager *managet = new QNetworkAccessManager(this);
    connect(managet, &QNetworkAccessManager::finished, this, &Widget::replyFinished);
    QNetworkRequest request;
    request.setUrl(QUrl("https://programari.registru.md/wp-admin/admin-ajax.php"));
    request.setRawHeader(QByteArray("Accept"), QByteArray("*/*"));
    request.setRawHeader(QByteArray("Origin"), QByteArray("https://programari.registru.md"));
    request.setRawHeader(QByteArray("X-Requested-With"), QByteArray("XMLHttpRequest"));
    request.setRawHeader(QByteArray("Content-Type"), QByteArray("application/x-www-form-urlencoded; charset=UTF-8"));
    managet->post(request,QByteArray("ProviderId:36"
                                     "ServiceId:338"
                                     "action:GetProviderAvailableDatesByService"));
    //managet->get(QNetworkRequest(QUrl("https://programari.registru.md")));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::replyFinished(QNetworkReply *reply)
{
    qDebug()<<reply->readAll();
}
