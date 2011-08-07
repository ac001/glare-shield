#ifndef GLARESHIELDWIDGET_H
#define GLARESHIELDWIDGET_H

#include <QSettings>


#include <QWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

#include "widgets/gsbutton.h"

#include "panels/autothrottlewidget.h"
#include "panels/altitudewidget.h"
#include "panels/headingwidget.h"

#include "panels/landinggearwidget.h"

#include "network/servercall.h"



class GlareShieldWidget : public QWidget
{
Q_OBJECT
public:
	explicit GlareShieldWidget(QWidget *parent = 0);

	QSettings settings;
	ServerCall *serverCall;


	QComboBox *comboRefreshRate;
	QCheckBox *chkAutoRefresh;
	QLineEdit *txtServerUrl;

	GSButton *buttAPEnabled;

	AutoThrottleWidget *autoThrottleWidget;
	HeadingWidget *headingWidget;
	AltitudeWidget *altitudeWidget;

	LandingGearWidget *landingGearWidget;




signals:

public slots:
	void closeEvent(QCloseEvent *event);

	void fetch_nodes();

	//void on_node_vals(QHash<QString,QString>);
	void on_node_val(QString node, QString value);
	void on_ap_button_clicked();
};

#endif // GLARESHIELDWIDGET_H
