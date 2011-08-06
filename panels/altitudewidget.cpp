

#include "altitudewidget.h"
#include "widgets/xgroupboxes.h"

AltitudeWidget::AltitudeWidget(QWidget *parent) :
	QWidget(parent)
{

	QHBoxLayout *mainLayout = new QHBoxLayout();
	setLayout(mainLayout);






	//==========================================================
	QHBoxLayout *leftLayout = new QHBoxLayout();
	mainLayout->addLayout(leftLayout);



	gsVerticalSpeed = new GSReadoutWidget();
	gsVerticalSpeed->setup(4, 100, 10);
	gsVerticalSpeed->set_top("V/S", "FPA");
	gsVerticalSpeed->labelSide->hide();
	leftLayout->addWidget(gsVerticalSpeed);
	connect(gsVerticalSpeed, SIGNAL(prop_val(int)), this, SLOT(on_vs_changed(int)));



	//==========================================================
	QHBoxLayout *altHoldLayout = new QHBoxLayout();
	mainLayout->addLayout(altHoldLayout);

	XGroupVBox *groupBox = new XGroupVBox("Altitude");
	altHoldLayout->addWidget(groupBox);
	//groupBox->setStyleSheet("background-color: #767676;");

	gsAltitudeHold= new GSReadoutWidget();
	gsAltitudeHold->setup(5, 1000, 100);
	gsAltitudeHold->set_top("Altitude");
	gsAltitudeHold->labelSide->hide();
	groupBox->addWidget(gsAltitudeHold);
	connect(gsAltitudeHold, SIGNAL(prop_val(int)), this, SLOT(on_alt_changed(int)));

	QHBoxLayout *bottomLayout = new QHBoxLayout();
	groupBox->addLayout(bottomLayout);
	bottomLayout->addStretch(10);

	buttVNavEnabled = new GSButton();
	buttVNavEnabled->setText("HOLD");
	bottomLayout->addWidget(buttVNavEnabled);
	connect(buttVNavEnabled, SIGNAL(clicked()), this, SLOT(on_vnav_button_clicked()));

	bottomLayout->addStretch(10);

}


void AltitudeWidget::on_alt_changed(int val)
{
	emit set_node("/autopilot/settings/target-altitude-ft", QString::number(val));
}
void AltitudeWidget::on_vs_changed(int val)
{
	emit set_node("/autopilot/settings/target-altitude-ft", QString::number(val));
}

void AltitudeWidget::on_vnav_button_clicked()
{
	emit set_node("/instrumentation/flightdirector/vnav", buttVNavEnabled->isChecked() ? "2" : "0");
}


void AltitudeWidget::on_node_val(QString node, QString value)
{
	if(node == "/autopilot/settings/target-altitude-ft"){
		gsAltitudeHold->set_value(value);
	}
	if(node == "/instrumentation/flightdirector/vnav"){
		buttVNavEnabled->set_state(value == "2");
	}
}
