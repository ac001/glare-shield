

#include <QtDebug>

#include <QTimer>

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

	QString top_style("font-size: 9pt; color: #dddddd; font-weight: bold;");
	QLabel *headLAbel = new QLabel();
	headLAbel->setAlignment(Qt::AlignHCenter| Qt::AlignVCenter);
	headLAbel->setStyleSheet(top_style);
	headLAbel->setText("LANDING GEAR");
	grpLay->addWidget(headLAbel);


	//=====================================
	QGridLayout *topGrid = new QGridLayout();

	grpLay->addLayout(topGrid);

	//====================

	lblGear1 = new QLabel();
	lblGear1->setFixedHeight(30);
	lblGear1->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	topGrid->addWidget(lblGear1, 0, 1, 2, 1);

	lblGear2 = new QLabel();
	lblGear2->setFixedHeight(30);
	lblGear2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	topGrid->addWidget(lblGear2, 1, 0, 2, 1);

	lblGear3 = new QLabel();
	lblGear3->setFixedHeight(30);
	lblGear3->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	topGrid->addWidget(lblGear3, 1, 2, 2, 1);

	set_indicator_style(2);
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

void LandingGearWidget::refresh_gear_pos()
{
	emit fetch_node("/gear/gear/position-norm");
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
		set_indicator_style(value == "true" ? 0 : 2);

	}else if(node == "/gear/gear/position-norm"){
		qDebug() << "pos=" << value;
		if(value == "1"){
			set_indicator_style(0);
			set_indicator_text("OK");
			QTimer::singleShot(4000, this, SLOT(clear_indicator_text()));

		}else if(value == "0"){
			set_indicator_style(2);
			set_indicator_text("UP");
			QTimer::singleShot(4000, this, SLOT(clear_indicator_text()));

		}else{
			set_indicator_style(1);
			set_indicator_text("");
			QTimer::singleShot(1000, this, SLOT(refresh_gear_pos()));
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

void LandingGearWidget::set_indicator_style(int state)
{
	QString color;
	if(state == 0){
		color = "#87C082";
	}else if(state == 1){
		color = "#880000";
	}else if(state == 2){
		color = "#555555";
	}
	QString sty("border: 1px inset #777777; color: white; background-color:");
	sty.append(color);

	lblGear1->setStyleSheet(sty);
	lblGear2->setStyleSheet(sty);
	lblGear3->setStyleSheet(sty);
}
void LandingGearWidget::set_indicator_text(QString text)
{
	lblGear1->setText(text);
	lblGear2->setText(text);
	lblGear3->setText(text);
}

void LandingGearWidget::clear_indicator_text()
{
	set_indicator_text("");
}
