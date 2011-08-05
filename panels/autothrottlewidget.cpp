
#include <QtDebug>

#include <QUrl>
#include <QVariant>


#include <QHBoxLayout>
#include <QPushButton>
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

	QPushButton *buttDec10 = new QPushButton();
	buttDec10->setText("<<");
	buttDec10->setProperty("val",QVariant("-10"));
	buttLay->addWidget(buttDec10);
	buttGroupSpeed->addButton(buttDec10);

	QPushButton *buttDec1 = new QPushButton();
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

	QPushButton *buttInc10 = new QPushButton();
	buttInc10->setText(">>");
	buttDec10->setProperty("val","+10");
	buttLay->addWidget(buttInc10);
	buttGroupSpeed->addButton(buttInc10);

	QHBoxLayout *layModes = new QHBoxLayout();
	grpLay->addLayout(layModes);

	radioSpeedWithThrottle = new QRadioButton();
	radioSpeedWithThrottle->setText("Speed with Throttle");
	layModes->addWidget(radioSpeedWithThrottle);

	radioSpeedWithPitch = new QRadioButton();
	radioSpeedWithPitch->setText("Speed with Pitch");
	layModes->addWidget(radioSpeedWithPitch);


}

void AutoThrottleWidget::on_speed_button(QAbstractButton *butt)
{
	int val = labelSpeed->text().toInt();
	//if(val < 70){
	//	return;
	//}
	val = val + butt->property("val").toInt();

	emit set_node("/autopilot/settings/target-speed-kt", QString::number(val));
	//lcdSpeed->display(butt->);
	//serverCall->fetch("/autopilot/settings");
	//emit fetch_node("/autopilot/settings/");
	//QUrl url ("http://localhost:8888/autopilot/settings/?json=1");


}

void AutoThrottleWidget::on_node_val(QString node, QString val)
{
	//qDebug() << node <<  val;
	if(node == "/autopilot/settings/target-speed-kt"){
		labelSpeed->setText(val);
		//qDebug() << "YES";
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
