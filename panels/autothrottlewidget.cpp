
#include <QtDebug>

#include <QUrl>
#include <QVariant>


#include <QHBoxLayout>
#include <QPushButton>
#include <QLCDNumber>


#include "panels/autothrottlewidget.h"

AutoThrottleWidget::AutoThrottleWidget(QWidget *parent) :
	QWidget(parent)
{

	QHBoxLayout *lay = new QHBoxLayout();
	setLayout(lay);

	buttGroupSpeed = new QButtonGroup(this);
	connect(buttGroupSpeed, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(on_speed_button(QAbstractButton*)));

	QPushButton *buttDec10 = new QPushButton();
	buttDec10->setText("<<");
	buttDec10->setProperty("val",QVariant("-10"));
	lay->addWidget(buttDec10);
	buttGroupSpeed->addButton(buttDec10);


	lcdSpeed = new QLCDNumber();
	lcdSpeed->setDigitCount(3);
	lay->addWidget(lcdSpeed);

	QPushButton *buttInc10 = new QPushButton();
	buttInc10->setText(">>");
	buttDec10->setProperty("val","+10");
	lay->addWidget(buttInc10);
	buttGroupSpeed->addButton(buttInc10);



}

void AutoThrottleWidget::on_speed_button(QAbstractButton *butt)
{
	//lcdSpeed->display(butt->);
	//serverCall->fetch("/autopilot/settings");
	emit fetch_node("/autopilot/settings");
	//QUrl url ("http://localhost:8888/autopilot/settings/?json=1");


}

