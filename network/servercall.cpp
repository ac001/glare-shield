

#include <QtDebug>


#include <QScriptValue>
#include <QScriptValueIterator>

#include "servercall.h"

ServerCall::ServerCall(QObject *parent) :
	QObject(parent)
{

	//== Network
	netMan = new QNetworkAccessManager(this);

	in_request = false;


}

//===================================================================================
//= Fetch Node
//===================================================================================
void ServerCall::fetch_node(QString node)
{
	if(request_q.contains(node)){
		qDebug() << "already - skipped" << node;
		return;
	}
	request_q.enqueue(node);
	check_q();

}

void ServerCall::check_q()
{
	if(in_request == true){
		return;
	}
	if(request_q.isEmpty()){
		return;
	}
	in_request = true;

	QUrl url (server_url);
	url.setPath(request_q.dequeue());
	url.addQueryItem("json", "1");

	QNetworkRequest request;
	request.setUrl(url);
	//qDebug() << "----------------------------------------------------------------";
	//qDebug() << url.toString();

	server_string = "";
	reply = netMan->get(request);

	connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(on_net_error(QNetworkReply::NetworkError)));
	connect(reply, SIGNAL(readyRead()), this, SLOT(on_net_ready_read()));
	connect(reply, SIGNAL(finished()), this, SLOT(on_net_finished()));
}


void ServerCall::set_node(QString node, QString val)
{
	in_request = true;
	QUrl url (server_url);
	url.setPath(node);
	url.addQueryItem("json", "1");
	url.addQueryItem("value", val);

	QNetworkRequest request;
	request.setUrl(url);
	//qDebug() << "----------------------------------------------------------------";
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
	server_string.append(reply->readAll());
}

//= Net finished
void ServerCall::on_net_finished(){

	QScriptValue sc;
	qDebug() << server_string;
	sc = scriptEngine.evaluate("(" + QString(server_string) + ")"); //?? why ?? In new versions it may need to look like engine.evaluate("(" + QString(result) + ")");

	QHash<QString, QString> hash;
	if (sc.property("nodes").isArray())
	{
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
	in_request = false;
	check_q();
}

void ServerCall::set_url(QString new_server)
{
	server_url = new_server;
}




