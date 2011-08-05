
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


	QGroupBox *groupBox = new QGroupBox("Speed");
	mainLayout->addWidget(groupBox);
	QVBoxLayout *grpLay = new QVBoxLayout();
	groupBox->setLayout(grpLay);

	QHBoxLayout *buttLay = new QHBoxLayout();
	grpLay->addLayout(buttLay);

	buttGroupSpeed = new QButtonGroup(this);
	connect(buttGroupSpeed, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(on_speed_button(QAbstractButton*)));

	QToolButton *buttDec10 = new QToolButton();
	buttDec10->setText("<<");
	buttDec10->setProperty("val",QVariant("-10"));
	buttLay->addWidget(buttDec10);
	buttGroupSpeed->addButton(buttDec10);

	QToolButton *buttDec1 = new QToolButton();
	buttDec1->setText("<");
	buttDec1->setProperty("val",QVariant("-1"));
	buttLay->addWidget(buttDec1);
	buttGroupSpeed->addButton(buttDec1);

	labelSpeed = new QLabel();
	//labelSpeed->setDigitCount(3);
	//QFont font = lcdSpeed->font();
	//font.setPointSize(20);
	//font.setFamily("monospaced");
	//lcdSpeed->setFont(font);
	labelSpeed->setStyleSheet("font-family: monospace; font-size: 32pt; font-weight: bold; background-color: #333333; color: #efffff;");
	buttLay->addWidget(labelSpeed);


	QPushButton *buttInc1 = new QPushButton();
	buttInc1->setText(">>");
	buttInc1->setProperty("val","1");
	buttLay->addWidget(buttInc1);
	buttGroupSpeed->addButton(buttInc1);

	QPushButton *buttInc10 = new QPushButton();
	buttInc10->setText(">>");
	buttInc10->setProperty("val","10");
	buttLay->addWidget(buttInc10);
	buttGroupSpeed->addButton(buttInc10);


	//====================================================
	QGridLayout *layModes = new QGridLayout();
	grpLay->addLayout(layModes);

	buttATEnabled = new QPushButton();
	buttATEnabled->setText("A/T");
	buttATEnabled->setCheckable(true);
	buttATEnabled->setIcon(QIcon(":/icon/black"));
	layModes->addWidget(buttATEnabled, 0, 0, 2, 1);
	connect(buttATEnabled, SIGNAL(clicked()), this, SLOT(on_at_button_clicked()));


	radioSpeedWithThrottle = new QRadioButton();
	radioSpeedWithThrottle->setText("Speed with Throttle");
	layModes->addWidget(radioSpeedWithThrottle, 0, 1, 1, 1);

	radioSpeedWithPitch = new QRadioButton();
	radioSpeedWithPitch->setText("Speed with Pitch");
	layModes->addWidget(radioSpeedWithPitch, 1, 1, 1, 1);


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
		//qDebug() << "YES";
	}
	if(node == "/instrumentation/flightdirector/at-on"){
		//qDebug() << node << value;
		buttATEnabled->setIcon(QIcon(value == "1" ? ":/icon/green" : ":/icon/black"));
		buttATEnabled->setChecked(value == "1");
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
