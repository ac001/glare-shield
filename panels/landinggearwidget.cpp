

#include <QtDebug>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QToolButton>

#include "panels/landinggearwidget.h"

LandingGearWidget::LandingGearWidget(QWidget *parent) :
	QWidget(parent)
{

	QHBoxLayout *mainLayout = new QHBoxLayout();
	setLayout(mainLayout);

	QGroupBox *groupBox = new QGroupBox();
	mainLayout->addWidget(groupBox);


	QVBoxLayout *grpLay = new QVBoxLayout();
	groupBox->setLayout(grpLay);


	//=====================================
	QGridLayout *topGrid = new QGridLayout();

	grpLay->addLayout(topGrid);

	//====================

	lblGear1 = new QLabel();
	lblGear1->setFixedHeight(30);
	topGrid->addWidget(lblGear1, 0, 1, 2, 1);

	lblGear2 = new QLabel();
	lblGear2->setFixedHeight(30);
	topGrid->addWidget(lblGear2, 1, 0, 2, 1);

	lblGear3 = new QLabel();
	lblGear3->setFixedHeight(30);
	topGrid->addWidget(lblGear3, 1, 2, 2, 1);

	set_indicator_style("#444444");
	//=====================

	int widi = 100;

	QVBoxLayout *buttonBox = new QVBoxLayout();
	grpLay->addLayout(buttonBox);


	buttGearUp = new QToolButton();
	buttGearUp->setText("UP");
	buttGearUp->setFixedWidth(widi);
	buttGearUp->setCheckable(true);
	buttonBox->addWidget(buttGearUp);
	connect(buttGearUp, SIGNAL(clicked(bool)), this, SLOT(on_gear_up_button(bool)));

	buttGearDown = new QToolButton();
	buttGearDown->setText("DOWN");
	buttGearDown->setFixedWidth(widi);
	buttGearDown->setCheckable(true);
	buttGearDown->setChecked(true);
	buttonBox->addWidget(buttGearDown);
	connect(buttGearDown, SIGNAL(clicked(bool)), this, SLOT(on_gear_down_button(bool)));

	grpLay->addStretch(5);

	set_butt_style();
}


void LandingGearWidget::on_gear_down_button(bool state)
{
	set_butt_style();
	if(state == true){
		emit set_node("/controls/gear/gear-down", "1");
		emit fetch_node("/gear/gear/position-norm");
	}
}

void LandingGearWidget::on_gear_up_button(bool state)
{
	set_butt_style();
	if(state == true){
		emit set_node("/controls/gear/gear-down", "0");
		emit fetch_node("/gear/gear/position-norm");
	}
}

void LandingGearWidget::on_node_val(QString node, QString value)
{
	if(node == "/controls/gear/gear-down"){
		//qDebug() << "Gear Down=" << value;
		buttGearUp->setChecked(value != "true");
		buttGearDown->setChecked(value == "true");
		set_butt_style();

	}else if(node == "/gear/gear/position-norm"){
		//qDebug() << "pos=" << value;
		if(value == "1"){
			set_indicator_style("#006600");
		}else if(value == "0"){
			set_indicator_style("#333333");
		}else{
			set_indicator_style("#990000");
			emit fetch_node("/gear/gear/position-norm");
		}


	}else if(node == "XXX/instrumentation/flightdirector/track-mode-on"){
		//gsHeading->labelMode->setText(value == "1" ? "TRK" : "HDG");

	}
}

void LandingGearWidget::set_butt_style()
{
	QString up_style("background-color: black; font-size: 10pt; font-weight: bold; color: white; border: 2px solid #999999;");
	QString down_style("background-color: black; font-size: 10pt; font-weight: bold; color: white; border: 2px solid #444444;");
	buttGearUp->setStyleSheet( buttGearUp->isChecked() ?  up_style : down_style);
	buttGearDown->setStyleSheet( buttGearDown->isChecked() ? up_style : down_style );
}

void LandingGearWidget::set_indicator_style(QString color)
{
	QString sty("border: 1px inset #777777; background-color:");
	sty.append(color);
	//qDebug() << sty;
	lblGear1->setStyleSheet(sty);
	lblGear2->setStyleSheet(sty);
	lblGear3->setStyleSheet(sty);
}

