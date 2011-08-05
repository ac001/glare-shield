#ifndef SERVERCALL_H
#define SERVERCALL_H

#include <QObject>
#include <QHash>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>


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

signals:
	void node_val(QString node, QString value);
	//void node_vals(QHash<QString, QString> vals);

public slots:
	void on_net_ready_read();
	void on_net_finished();
	void on_net_error(QNetworkReply::NetworkError);

	void fetch_node(QString node);
};

#endif // SERVERCALL_H
