
#include <QHBoxLayout>
#include <QGroupBox>
//#include <>
//#include <>
//#include <>

#include "panels/headingwidget.h"

HeadingWidget::HeadingWidget(QWidget *parent) :
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


	gsHeading = new GSReadoutWidget(3);
	gsHeading->setup(10, 1, true);
	gsHeading->set_top("HDG", "TRK");
	grpLay->addWidget(gsHeading);
	connect(gsHeading, SIGNAL(prop_val(int)), this, SLOT(on_heading_changed(int)) );
	connect(gsHeading, SIGNAL(on_top()), this, SLOT(on_top_button()));

	//====================================================
	QHBoxLayout *layModes = new QHBoxLayout();
	grpLay->addLayout(layModes);
	layModes->addStretch(10);

	buttHeadingHoldEnabled = new GSButton();
	buttHeadingHoldEnabled->setText("HOLD");
	layModes->addWidget(buttHeadingHoldEnabled);
	connect(buttHeadingHoldEnabled, SIGNAL(clicked()), this, SLOT(on_heading_button_clicked()));

	layModes->addStretch(10);


}

void HeadingWidget::on_heading_changed(int val)
{
	emit set_node("/autopilot/settings/heading-bug-deg", QString::number(val));
}

void HeadingWidget::on_node_val(QString node, QString value)
{
	if(node == "/autopilot/settings/heading-bug-deg"){
		gsHeading->set_value(value);

	}else if(node == "/instrumentation/flightdirector/lnav"){
		buttHeadingHoldEnabled->set_state(value == "1");

	}else if(node == "/instrumentation/flightdirector/track-mode-on"){
		gsHeading->labelMode->setText(value == "1" ? "TRK" : "HDG");

	}
}


void HeadingWidget::on_heading_button_clicked()
{
	emit set_node("/instrumentation/flightdirector/lnav", buttHeadingHoldEnabled->isChecked() ? "1" : "0");
}


void HeadingWidget::on_top_button()
{
	emit set_node("/instrumentation/flightdirector/track-mode-on", gsHeading->labelMode->text() == "TRK" ? "0" : "1");
}
