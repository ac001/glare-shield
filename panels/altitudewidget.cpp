

#include "altitudewidget.h"
#include "widgets/xgroupboxes.h"

AltitudeWidget::AltitudeWidget(QWidget *parent) :
	QWidget(parent)
{

	QHBoxLayout *mainLayout = new QHBoxLayout();
	setLayout(mainLayout);

	XGroupHBox *groupBox = new XGroupHBox("Altitude");
	mainLayout->addWidget(groupBox);
	//groupBox->setStyleSheet("background-color: transparent; border-left:none; border-right: none; border-bottom: none;");


	//==========================================================
	QVBoxLayout *verticalSpeedLayout = new QVBoxLayout();
	groupBox->addLayout(verticalSpeedLayout);

	//= Vertical Speed Readout
	gsVerticalSpeed = new GSReadoutWidget();
	gsVerticalSpeed->setup(4, 100, 10);
	gsVerticalSpeed->set_top("V/S", "FPA");
	verticalSpeedLayout->addWidget(gsVerticalSpeed);
	connect(gsVerticalSpeed, SIGNAL(prop_val(int)), this, SLOT(on_vs_changed(int)));

	//====
	QHBoxLayout *bottomLayoutVs = new QHBoxLayout();
	verticalSpeedLayout->addLayout(bottomLayoutVs);

	buttVSEnabled = new GSButton();
	buttVSEnabled->setText("VS/FDA");
	bottomLayoutVs->addWidget(buttVSEnabled);
	connect(buttVSEnabled, SIGNAL(clicked()), this, SLOT(on_vs_button_clicked()));

	//==========================================================
	QVBoxLayout *altHoldLayout = new QVBoxLayout();
	groupBox->addLayout(altHoldLayout);

	//== Altitude readout
	gsAltitudeHold= new GSReadoutWidget();
	gsAltitudeHold->setup(5, 1000, 100);
	gsAltitudeHold->set_top("Altitude");
	gsAltitudeHold->labelSide->hide();
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


	}else if(node == "/instrumentation/flightdirector/vnav"){
		buttVSEnabled->set_state(value == "3");
		buttAltitudeHoldEnabled->set_state(value == "2");
	}
}
