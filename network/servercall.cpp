#include "servercall.h"

ServerCall::ServerCall(QObject *parent) :
	QObject(parent)
{

	//== Network
	netMan = new QNetworkAccessManager(this);



}



void ServerCall::on_net_ready_read()
{
	qDebug() << "rady reed";
	server_string.append(reply->readAll());
}



void ServerCall::on_net_finished(){
	qDebug() << "finsihed" << server_string;
}



void ServerCall::on_net_error(QNetworkReply::NetworkError err){
	qDebug() << "net Error";
}


void ServerCall::fetch(QString node)
{
	QUrl url ("http://localhost:8888");
	url.setPath(node);
	url.addQueryItem("json", "1");

	QNetworkRequest request;
	request.setUrl(url);

	qDebug() << url.toString();

	server_string = "";
	reply = netMan->get(request);

	connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(on_net_error(QNetworkReply::NetworkError)));
	connect(reply, SIGNAL(readyRead()), this, SLOT(on_net_ready_read()));
	connect(reply, SIGNAL(readyRead()), this, SLOT(on_net_finished()));
}
