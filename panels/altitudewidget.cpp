

#include "altitudewidget.h"
#include "widgets/xgroupboxes.h"

AltitudeWidget::AltitudeWidget(QWidget *parent) :
	QWidget(parent)
{

	QVBoxLayout *mainLayout = new QVBoxLayout();
	setLayout(mainLayout);

	XGroupVBox *groupBox = new XGroupVBox("Altitude");
	mainLayout->addWidget(groupBox);
	groupBox->setStyleSheet("background-color: #767676;");

	gsReadout = new GSReadoutWidget();
	groupBox->addWidget(gsReadout);
	gsReadout->set_steps(1000, 100);
	connect(gsReadout, SIGNAL(prop_val(int)), this, SLOT(on_alt_changed(int)));

	QHBoxLayout *bottomLayout = new QHBoxLayout();
	groupBox->addWidget(bottomLayout);
	bottomLayout->addStretch(10);

	buttVNavEnabled = new GSButton();
	buttVNavEnabled->setText("HOLD");
	bottomLayout->addWidget(buttVNavEnabled);

	bottomLayout->addStretch(10);

}


void AltitudeWidget::on_val_changed(int val)
{
	emit set_node("/autopilot/settings/target-altitude-ft", QString::number(val));
}

void AltitudeWidget::on_node_val(QString node, QString value)
{
	if(node == "/autopilot/settings/target-altitude-ft"){
		gsReadout->labelMain->setText(value);
	}
	if(node == "/instrumentation/flightdirector/vnav"){
		buttVNavEnabled->set_state(value == "1");
	}
}
