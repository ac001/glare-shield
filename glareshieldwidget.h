#ifndef GLARESHIELDWIDGET_H
#define GLARESHIELDWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

#include "panels/autothrottlewidget.h"
#include "network/servercall.h"

class GlareShieldWidget : public QWidget
{
Q_OBJECT
public:
	explicit GlareShieldWidget(QWidget *parent = 0);


	QComboBox *comboRefreshRate;
	QCheckBox *chkAutoRefresh;
	QLineEdit *txtServerUrl;
	QPushButton *buttAPEnabled;

	AutoThrottleWidget *autoThrottleWidget;


	ServerCall *serverCall;


signals:

public slots:
	void fetch_nodes();

	//void on_node_vals(QHash<QString,QString>);
	void on_ap_button_clicked();
};

#endif // GLARESHIELDWIDGET_H
