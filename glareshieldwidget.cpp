
#include <QTimer>
#include <QHBoxLayout>
#include <QToolBar>
#include <QToolButton>

#include "glareshieldwidget.h"

#include "network/servercall.h"

GlareShieldWidget::GlareShieldWidget(QWidget *parent) :
	QWidget(parent)
{


	setMinimumWidth(500);


	QVBoxLayout *mainLayout = new QVBoxLayout();
	setLayout(mainLayout);

	//==========================================================
	QToolBar *controlBar = new QToolBar();
	mainLayout->addWidget(controlBar);

	buttAPEnabled = new QPushButton();
	buttAPEnabled->setText("A/P");
	buttAPEnabled->setCheckable(true);
	buttAPEnabled->setIcon(QIcon(":/icon/black"));
	controlBar->addWidget(buttAPEnabled);
	connect(buttAPEnabled, SIGNAL(clicked()), this, SLOT(on_ap_button_clicked()));

	chkAutoRefresh = new QCheckBox();
	chkAutoRefresh->setChecked(true);
	controlBar->addWidget(chkAutoRefresh);

	txtServerUrl = new QLineEdit();
	txtServerUrl->setText("http://localhost:8888/");
	controlBar->addWidget(txtServerUrl);

	comboRefreshRate = new QComboBox();
	comboRefreshRate->addItem("1");
	comboRefreshRate->addItem("2");
	controlBar->addWidget(comboRefreshRate);


	QToolButton *butttRefresh = new QToolButton();
	butttRefresh->setText("Refresh");
	controlBar->addWidget(butttRefresh);
	connect(butttRefresh, SIGNAL(clicked()), this, SLOT(fetch_nodes()));

	//==========================================================
	AutoThrottleWidget *autoThrottleWidget = new AutoThrottleWidget();
	mainLayout->addWidget(autoThrottleWidget);


	//==========================================================
	serverCall = new ServerCall(this);
	serverCall->set_url(txtServerUrl->text());

	connect(autoThrottleWidget, SIGNAL(fetch_node(QString)), serverCall, SLOT(fetch_node(QString)));
	connect(serverCall, SIGNAL(node_val(QString,QString)), autoThrottleWidget, SLOT(on_node_val(QString, QString)));
	//connect(serverCall, SIGNAL(node_vals(QHash<QString,QString>)), autoThrottleWidget, SLOT(on_node_vals(QHash<QString,QString>)));

	connect(autoThrottleWidget, SIGNAL(set_node(QString,QString)), serverCall, SLOT(set_node(QString, QString)));

	fetch_nodes();



}

void GlareShieldWidget::fetch_nodes()
{
	serverCall->fetch_node("/autopilot/settings");
	serverCall->fetch_node("/instrumentation/flightdirector/");

	if(chkAutoRefresh->isChecked()){
		QTimer::singleShot(1000, this, SLOT(fetch_nodes()));
	}

}

void GlareShieldWidget::on_ap_button_clicked()
{
	serverCall->set_node("/instrumentation/flightdirector/autopilot-on", buttAPEnabled->isChecked() ? "1" : "0");
}
