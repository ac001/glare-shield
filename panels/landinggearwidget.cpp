

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
	QString lbl_style("border: 2px inset #999999; background-color: #009900");

	QLabel *lblGear1 = new QLabel();
	lblGear1->setStyleSheet(lbl_style);
	lblGear1->setFixedHeight(30);
	topGrid->addWidget(lblGear1, 0, 1, 2, 1);

	QLabel *lblGear2 = new QLabel();
	lblGear2->setStyleSheet(lbl_style);
	lblGear2->setFixedHeight(30);
	topGrid->addWidget(lblGear2, 1, 0, 2, 1);


	QLabel *lblGear3 = new QLabel();
	lblGear3->setStyleSheet(lbl_style);
	lblGear3->setFixedHeight(30);
	topGrid->addWidget(lblGear3, 1, 2, 2, 1);

	//=====================

	int widi = 100;

	QVBoxLayout *buttonBox = new QVBoxLayout();
	grpLay->addLayout(buttonBox);

	buttonGroup = new QButtonGroup();
	buttonGroup->setExclusive(true);
	connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(on_button(int)));

	buttGearUp = new QToolButton();
	buttGearUp->setText("UP");
	buttGearUp->setFixedWidth(widi);
	buttGearUp->setCheckable(true);
	buttGearUp->setChecked(true);
	buttonBox->addWidget(buttGearUp);
	buttonGroup->addButton(buttGearUp, 0);

	buttGearDown = new QToolButton();
	buttGearDown->setText("DOWN");
	buttGearDown->setFixedWidth(widi);
	buttGearDown->setCheckable(true);
	buttGearDown->setChecked(false);
	buttonBox->addWidget(buttGearDown);
	buttonGroup->addButton(buttGearDown, 1);

	grpLay->addStretch(5);
}


void LandingGearWidget::on_button(int id)
{
	QString up_style("background-color: black; font-size: 10pt; font-weight: bold; color: white; border: 2px solid #999999;");
	QString down_style("background-color: black; font-size: 10pt; font-weight: bold; color: white; border: 2px solid #444444;");
	bool gear_down = buttonGroup->button(1)->isChecked();

	buttGearUp->setStyleSheet( gear_down ? down_style : up_style);
	buttGearDown->setStyleSheet( !gear_down ? down_style : up_style);
}
