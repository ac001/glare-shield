#ifndef SERVERCALL_H
#define SERVERCALL_H

#include <QObject>
#include <QHash>

#include <QScriptEngine>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QQueue>

class ServerCall : public QObject
{
Q_OBJECT
public:
	explicit ServerCall(QObject *parent = 0);

	QNetworkAccessManager *netMan;
	QNetworkReply *reply;
	QString server_string;

	QString server_url;
	void set_url(QString new_server);

	QScriptEngine scriptEngine;

	QQueue<QString> request_q;
	bool in_request;

signals:
	void node_val(QString node, QString value);
	//void node_vals(QHash<QString, QString> vals);

public slots:
	void on_net_ready_read();
	void on_net_finished();
	void on_net_error(QNetworkReply::NetworkError);

	void fetch_node(QString node);
	void set_node(QString node, QString val);

	void check_q();
};

#endif // SERVERCALL_H
