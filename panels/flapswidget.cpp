


#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>


#include "panels/flapswidget.h"

FlapsWidget::FlapsWidget(QWidget *parent) :
	QWidget(parent)
{


	QHBoxLayout *mainLayout = new QHBoxLayout();
	setLayout(mainLayout);

	QGroupBox *groupBox = new QGroupBox();
	mainLayout->addWidget(groupBox);


	QHBoxLayout *grpLay = new QHBoxLayout();
	groupBox->setLayout(grpLay);

	//===
	QString top_style("font-size: 9pt; color: #dddddd; font-weight: bold;");
	QLabel *headLAbel = new QLabel();
	headLAbel->setAlignment(Qt::AlignHCenter| Qt::AlignVCenter);
	headLAbel->setStyleSheet(top_style);
	headLAbel->setText("FLAPS");
	grpLay->addWidget(headLAbel);

	//=================
	QVBoxLayout *sliderLay = new QVBoxLayout();
	grpLay->addLayout(sliderLay);

	buttUp = new QToolButton();
	sliderLay->addWidget(buttUp);

	slider = new QSlider();
	slider->setRange(0, 1000);
	slider->setPageStep(200);
	slider->setSingleStep(200);
	sliderLay->addWidget(slider);

	buttDown = new QToolButton();
	sliderLay->addWidget(buttDown);

}


void FlapsWidget::on_button_up()
{

}
void FlapsWidget::on_button_down()
{

}

void FlapsWidget::on_slider_value()
{

}

void FlapsWidget::on_node_val(QString node, QString val)
{

}
