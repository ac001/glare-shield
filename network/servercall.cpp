

#include <QtDebug>

#include <QScriptEngine>
#include <QScriptValue>
#include <QScriptValueIterator>

#include "servercall.h"

ServerCall::ServerCall(QObject *parent) :
	QObject(parent)
{

	//== Network
	netMan = new QNetworkAccessManager(this);



}

//===================================================================================
//= Fetch Node
//===================================================================================
void ServerCall::fetch_node(QString node)
{
	QUrl url (server_url);
	url.setPath(node);
	url.addQueryItem("json", "1");

	QNetworkRequest request;
	request.setUrl(url);
	qDebug() << "----------------------------------------------------------------";
	qDebug() << url.toString();

	server_string = "";
	reply = netMan->get(request);

	connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(on_net_error(QNetworkReply::NetworkError)));
	connect(reply, SIGNAL(readyRead()), this, SLOT(on_net_ready_read()));
	connect(reply, SIGNAL(finished()), this, SLOT(on_net_finished()));
}


//===================================================================================
//= Server Callbacks
//===================================================================================


//= Error
void ServerCall::on_net_error(QNetworkReply::NetworkError err){
	qDebug() << "net Error";
}



//= read_ready - reads data into local server_string buffer
void ServerCall::on_net_ready_read()
{
	qDebug() << "ready reed";
	server_string.append(reply->readAll());
}

//= Net finished
void ServerCall::on_net_finished(){

	qDebug() << "finsihed"; //<< server_string;
	QScriptValue sc;
	QScriptEngine engine;
	sc = engine.evaluate("(" + QString(server_string) + ")"); //?? why ?? In new versions it may need to look like engine.evaluate("(" + QString(result) + ")");

	QHash<QString, QString> hash;
	if (sc.property("nodes").isArray())
	{
			qDebug() << "nodes is aray";
			QScriptValueIterator it(sc.property("nodes"));
			 while (it.hasNext()) {
				 it.next();
				 //qDebug("Nick %s",it.value().property("node").toString().toStdString().c_str());
				 //qDebug() << " > emit() " << it.value().property("node").toString() << it.value().property("value").toString();
				 emit node_val(it.value().property("node").toString(), it.value().property("value").toString());
				 hash[ it.value().property("node").toString() ] = it.value().property("value").toString();
			 }
	}
	//emit node_vals(hash);
}

void ServerCall::set_url(QString new_server)
{
	server_url = new_server;
}




