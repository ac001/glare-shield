
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>


#include "panels/altitudewidget.h"

AltitudeWidget::AltitudeWidget(QWidget *parent) :
	QWidget(parent)
{

	QHBoxLayout *mainLayout = new QHBoxLayout();
	setLayout(mainLayout);

	QGroupBox *groupBox = new QGroupBox();
	mainLayout->addWidget(groupBox);


	QHBoxLayout *grpLay = new QHBoxLayout();
	groupBox->setLayout(grpLay);


	//==========================================================
	QVBoxLayout *verticalSpeedLayout = new QVBoxLayout();
	grpLay->addLayout(verticalSpeedLayout);

	//= Vertical Speed Readout
	gsVerticalSpeed = new GSReadoutWidget(4);
	gsVerticalSpeed->setup( 100, 10, true);
	gsVerticalSpeed->set_top("V/S", "FPA");
	verticalSpeedLayout->addWidget(gsVerticalSpeed);
	connect(gsVerticalSpeed, SIGNAL(prop_val(int)), this, SLOT(on_vs_changed(int)));
	connect(gsVerticalSpeed, SIGNAL(on_top()), this, SLOT(on_vs_fpa()));

	//====
	QHBoxLayout *bottomLayoutVs = new QHBoxLayout();
	verticalSpeedLayout->addLayout(bottomLayoutVs);

	buttVSEnabled = new GSButton();
	buttVSEnabled->setText("VS/FDA");
	bottomLayoutVs->addWidget(buttVSEnabled);
	connect(buttVSEnabled, SIGNAL(clicked()), this, SLOT(on_vs_button_clicked()));



	//==========================================================
	QVBoxLayout *altHoldLayout = new QVBoxLayout();
	grpLay->addLayout(altHoldLayout);

	//== Altitude readout
	gsAltitudeHold= new GSReadoutWidget(5);
	gsAltitudeHold->setup(1000, 100, false);
	gsAltitudeHold->set_top("ALTITUDE");
	altHoldLayout->addWidget(gsAltitudeHold);
	connect(gsAltitudeHold, SIGNAL(prop_val(int)), this, SLOT(on_alt_changed(int)));

	//====
	QHBoxLayout *bottomLayoutAlt = new QHBoxLayout();
	altHoldLayout->addLayout(bottomLayoutAlt);

	bottomLayoutAlt->addStretch(10);

	buttAltitudeHoldEnabled = new GSButton();
	buttAltitudeHoldEnabled->setText("HOLD");
	bottomLayoutAlt->addWidget(buttAltitudeHoldEnabled);
	connect(buttAltitudeHoldEnabled, SIGNAL(clicked()), this, SLOT(on_alt_hold_button_clicked()));

	bottomLayoutAlt->addStretch(10);

}



void AltitudeWidget::on_vs_changed(int val)
{
	emit set_node("/autopilot/settings/vertical-speed-fpm", QString::number(val));
}
void AltitudeWidget::on_vs_button_clicked()
{
	emit set_node("/instrumentation/flightdirector/vnav", buttVSEnabled->isChecked() ? "3" : "0");
}

void AltitudeWidget::on_alt_changed(int val)
{
	emit set_node("/autopilot/settings/target-altitude-ft", QString::number(val));
}
void AltitudeWidget::on_alt_hold_button_clicked()
{
	emit set_node("/instrumentation/flightdirector/vnav", buttAltitudeHoldEnabled->isChecked() ? "2" : "0");
}


void AltitudeWidget::on_node_val(QString node, QString value)
{
	if(node == "/autopilot/settings/vertical-speed-fpm"){
		gsVerticalSpeed->set_value(value);

	}else if(node == "/autopilot/settings/target-altitude-ft"){
		gsAltitudeHold->set_value(value);

	}else if(node == "/instrumentation/flightdirector/fpa-mode-on"){
		gsVerticalSpeed->labelMode->setText(value == "1" ? "FPA" : "V/S");

	}else if(node == "/instrumentation/flightdirector/vnav"){
		buttVSEnabled->set_state(value == "3");
		buttAltitudeHoldEnabled->set_state(value == "2");
	}
}

void AltitudeWidget::on_vs_fpa()
{
	emit set_node("/instrumentation/flightdirector/fpa-mode-on", gsVerticalSpeed->labelMode->text()  == "FPA" ? "0" : "1");
}
