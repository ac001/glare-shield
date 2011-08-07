
#include <QtDebug>

#include <QUrl>
#include <QVariant>


#include <QHBoxLayout>
#include <QToolButton>
#include <QLCDNumber>
#include <QGroupBox>


#include "panels/autothrottlewidget.h"

AutoThrottleWidget::AutoThrottleWidget(QWidget *parent) :
	QWidget(parent)
{
	QHBoxLayout *mainLayout = new QHBoxLayout();
	setLayout(mainLayout);

	setMaximumWidth(300);

	QGroupBox *groupBox = new QGroupBox();
	mainLayout->addWidget(groupBox);
	//groupBox->setStyleSheet("background-color: transparent;");

	QVBoxLayout *grpLay = new QVBoxLayout();
	groupBox->setLayout(grpLay);


	gsReadout = new GSReadoutWidget(3);
	gsReadout->setup(10, 1, true);
	gsReadout->set_top("IAS", "MACH");
	grpLay->addWidget(gsReadout);
	connect(gsReadout, SIGNAL(prop_val(int)), this, SLOT(on_val_changed(int)));



	//====================================================
	QGridLayout *layModes = new QGridLayout();
	grpLay->addLayout(layModes);

	buttATEnabled = new GSButton();
	buttATEnabled->setText("A/T");
	layModes->addWidget(buttATEnabled, 0, 0, 2, 1);
	connect(buttATEnabled, SIGNAL(clicked()), this, SLOT(on_at_button_clicked()));


	radioSpeedWithThrottle = new QRadioButton();
	radioSpeedWithThrottle->setText("Speed with Throttle");
	layModes->addWidget(radioSpeedWithThrottle, 0, 1, 1, 1);

	radioSpeedWithPitch = new QRadioButton();
	radioSpeedWithPitch->setText("Speed with Pitch");
	layModes->addWidget(radioSpeedWithPitch, 1, 1, 1, 1);

	//QDial *dial = new QDial();
	//dial->setRange(1,360);
	//dial->setWrapping(true);
	//layModes->addWidget(dial, 1, 2, 2, 1);

}

void AutoThrottleWidget::on_val_changed(int val)
{
	emit set_node("/autopilot/settings/target-speed-kt", QString::number(val));
}

void AutoThrottleWidget::on_node_val(QString node, QString value)
{
	if(node == "/autopilot/settings/target-speed-kt"){
		gsReadout->set_value(value);
	}
	if(node == "/instrumentation/flightdirector/at-on"){
		buttATEnabled->set_state(value == "1");
	}
}

/*
void AutoThrottleWidget::on_node_vals(QHash<QString, QString> hash)
{
	qDebug() << "AutoThrottleWidget::on_node_vals";
	if(hash.contains("/autopilot/settings/target-speed-kt")){
		lcdSpeed->display(hash.value("/autopilot/settings/target-speed-kt"));
	}
}
*/


void AutoThrottleWidget::on_at_button_clicked()
{
	emit set_node("/instrumentation/flightdirector/at-on", buttATEnabled->isChecked() ? "1" : "0");
}
