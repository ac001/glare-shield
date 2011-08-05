
#include <QHBoxLayout>
#include <QToolBar>

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

	buttAPEnabled = new QToolButton();
	buttAPEnabled->setText("A/P");
	buttAPEnabled->setCheckable(true);
	controlBar->addWidget(buttAPEnabled);

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

	fetch_nodes();

}

void GlareShieldWidget::fetch_nodes()
{
	serverCall->fetch_node("/autopilot/settings");
}
