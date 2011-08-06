
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

	QGroupBox *groupBox = new QGroupBox("Speed");
	mainLayout->addWidget(groupBox);
	groupBox->setStyleSheet("background-color: #767676;");

	QVBoxLayout *grpLay = new QVBoxLayout();
	groupBox->setLayout(grpLay);

	QHBoxLayout *buttLay = new QHBoxLayout();
	grpLay->addLayout(buttLay);

	buttGroupSpeed = new QButtonGroup(this);
	connect(buttGroupSpeed, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(on_speed_button(QAbstractButton*)));

	QString in_style("font-size: 8pt; font-weight: bold;");

	buttLay->addStretch(10);
	QToolButton *buttDec10 = new QToolButton();
	buttDec10->setText("<<");
	buttDec10->setProperty("val",QVariant("-10"));
	buttDec10->setAutoRaise(true);
	buttDec10->setStyleSheet(in_style);
	buttLay->addWidget(buttDec10);
	buttGroupSpeed->addButton(buttDec10);

	QToolButton *buttDec1 = new QToolButton();
	buttDec1->setText("<");
	buttDec1->setProperty("val",QVariant("-1"));
	buttDec1->setStyleSheet(in_style);
	buttDec1->setAutoRaise(true);
	buttLay->addWidget(buttDec1);
	buttGroupSpeed->addButton(buttDec1);

	labelSpeed = new QLabel();
	labelSpeed->setFixedWidth(120);
	labelSpeed->setStyleSheet("padding: 5px; font-family: monospace; font-size: 32pt; font-weight: bold; background-color: #333333; color: #efefef; text-align: center; border: 3px solid #999999;");
	buttLay->addWidget(labelSpeed);


	QToolButton *buttInc1 = new QToolButton();
	buttInc1->setText(">");
	buttInc1->setProperty("val","1");
	buttInc1->setStyleSheet(in_style);
	buttInc1->setAutoRaise(true);
	buttLay->addWidget(buttInc1);
	buttGroupSpeed->addButton(buttInc1);

	QToolButton *buttInc10 = new QToolButton();
	buttInc10->setText(">>");
	buttInc10->setProperty("val","10");
	buttInc10->setStyleSheet(in_style);
	buttInc10->setAutoRaise(true);
	buttLay->addWidget(buttInc10);
	buttGroupSpeed->addButton(buttInc10);

	buttLay->addStretch(10);

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

void AutoThrottleWidget::on_speed_button(QAbstractButton *butt)
{
	int val = labelSpeed->text().toInt();
	val = val + butt->property("val").toInt();
	emit set_node("/autopilot/settings/target-speed-kt", QString::number(val));

}

void AutoThrottleWidget::on_node_val(QString node, QString value)
{
	//qDebug() << " - at=" << node <<  value;
	if(node == "/autopilot/settings/target-speed-kt"){
		labelSpeed->setText(value);
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
