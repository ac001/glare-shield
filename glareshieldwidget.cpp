
#include <QtDebug>

#include <QTimer>
#include <QHBoxLayout>
#include <QToolBar>
#include <QToolButton>


#include "glareshieldwidget.h"

#include "network/servercall.h"

GlareShieldWidget::GlareShieldWidget(QWidget *parent) :
	QWidget(parent)
{


	//setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #808080, stop: 1 #6A6A6A);");
	//setMinimumWidth(600);
	restoreGeometry( settings.value("glare_shield_widget_window").toByteArray() );


	QVBoxLayout *mainLayout = new QVBoxLayout();
	setLayout(mainLayout);

	//==========================================================
	QHBoxLayout *controlBar = new QHBoxLayout();
	mainLayout->addLayout(controlBar);

	buttAPEnabled = new GSButton();
	buttAPEnabled->setText("A/P");
	controlBar->addWidget(buttAPEnabled);
	connect(buttAPEnabled, SIGNAL(clicked()), this, SLOT(on_ap_button_clicked()));

	controlBar->addStretch(5);

	chkAutoRefresh = new QCheckBox();
	chkAutoRefresh->setChecked(true);
	controlBar->addWidget(chkAutoRefresh);

	txtServerUrl = new QLineEdit();
	txtServerUrl->setMaximumWidth(250);
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

	lblConnected = new QLabel();
	lblConnected->setFixedWidth(30);
	controlBar->addWidget(lblConnected);

	//==========================================================

	QHBoxLayout *middleLayout = new QHBoxLayout();
	mainLayout->addLayout(middleLayout);

	autoThrottleWidget = new AutoThrottleWidget();
	middleLayout->addWidget(autoThrottleWidget);

	headingWidget  = new HeadingWidget();
	middleLayout->addWidget(headingWidget);

	altitudeWidget = new AltitudeWidget();
	middleLayout->addWidget(altitudeWidget);


	//== 2nd row
	QHBoxLayout *bottomMiddleLayout = new QHBoxLayout();
	mainLayout->addLayout(bottomMiddleLayout);

	landingGearWidget = new LandingGearWidget();
	bottomMiddleLayout->addWidget(landingGearWidget);

	flapsWidget = new FlapsWidget();
	bottomMiddleLayout->addWidget(flapsWidget);

	bottomMiddleLayout->addStretch(20);

	middleLayout->addStretch(20);


	//==========================================================
	serverCall = new ServerCall(this);
	serverCall->set_url(txtServerUrl->text());

	connect(autoThrottleWidget, SIGNAL(set_node(QString,QString)), serverCall, SLOT(set_node(QString, QString)));
	connect(headingWidget, SIGNAL(set_node(QString,QString)), serverCall, SLOT(set_node(QString, QString)));
	connect(altitudeWidget, SIGNAL(set_node(QString,QString)), serverCall, SLOT(set_node(QString, QString)));
	connect(landingGearWidget, SIGNAL(set_node(QString,QString)), serverCall, SLOT(set_node(QString, QString)));
	connect(flapsWidget, SIGNAL(set_node(QString,QString)), serverCall, SLOT(set_node(QString, QString)));

	connect(landingGearWidget, SIGNAL(fetch_node(QString)), serverCall, SLOT(fetch_node(QString)));
	connect(flapsWidget, SIGNAL(fetch_node(QString)), serverCall, SLOT(fetch_node(QString)));

	connect(serverCall, SIGNAL(node_val(QString,QString)), autoThrottleWidget, SLOT(on_node_val(QString, QString)));
	connect(serverCall, SIGNAL(node_val(QString,QString)), headingWidget, SLOT(on_node_val(QString, QString)));
	connect(serverCall, SIGNAL(node_val(QString,QString)), altitudeWidget, SLOT(on_node_val(QString, QString)));
	connect(serverCall, SIGNAL(node_val(QString,QString)), landingGearWidget, SLOT(on_node_val(QString, QString)));
	connect(serverCall, SIGNAL(node_val(QString,QString)), flapsWidget, SLOT(on_node_val(QString, QString)));

	connect(serverCall, SIGNAL(node_val(QString,QString)), this, SLOT(on_node_val(QString, QString)));
	connect(serverCall, SIGNAL(server_connected(bool)), this, SLOT(on_server_connected(bool)));

	fetch_nodes();



}

void GlareShieldWidget::fetch_nodes()
{
	serverCall->fetch_node("/autopilot/settings");
	serverCall->fetch_node("/instrumentation/flightdirector/");
	serverCall->fetch_node("/controls/gear");
	serverCall->fetch_node("/surface-positions/");
	serverCall->fetch_node("/surface-positions/flap-pos-norm");

	//if(chkAutoRefresh->isChecked()){
		//QTimer::singleShot(1000, this, SLOT(fetch_nodes()));
	//}

}

void GlareShieldWidget::on_ap_button_clicked()
{
	serverCall->set_node("/instrumentation/flightdirector/autopilot-on", buttAPEnabled->isChecked() ? "1" : "0");
}

void GlareShieldWidget::on_node_val(QString node, QString value)
{
	if(node == "/instrumentation/flightdirector/autopilot-on"){
		 buttAPEnabled->set_state(value == "1");
	}
}




//= window close
void GlareShieldWidget::closeEvent(QCloseEvent *event){
	Q_UNUSED(event);
	settings.setValue("glare_shield_widget_window", QVariant(saveGeometry()));
}


void GlareShieldWidget::on_server_connected(bool state)
{
	QString sty("background-color:");
	sty.append(state ? "#00ff00" : "#990000");
	//qDebug() << state << sty;
	lblConnected->setStyleSheet(sty);
}
