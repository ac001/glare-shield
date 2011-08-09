

#include <QtDebug>

#include <QTimer>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>



#include "panels/flapswidget.h"

FlapsWidget::FlapsWidget(QWidget *parent) :
	QWidget(parent)
{

	flapsDeg["0"] = 0;
	flapsDeg["1"] = 1;
	flapsDeg["2"] = 5;
	flapsDeg["3"] = 15;
	flapsDeg["4"] = 20;
	flapsDeg["5"] = 25;
	flapsDeg["6"] = 30;

	flapsVal["0"] = 0;
	flapsVal["1"] = 33;
	flapsVal["2"] = 220;
	flapsVal["3"] = 500;
	flapsVal["4"] = 666;
	flapsVal["5"] = 833;
	flapsVal["6"] = 1000;



	QHBoxLayout *mainLayout = new QHBoxLayout();
	setLayout(mainLayout);

	QGroupBox *groupBox = new QGroupBox();
	mainLayout->addWidget(groupBox);


	QVBoxLayout *grpLay = new QVBoxLayout();
	groupBox->setLayout(grpLay);

	//===
	QString top_style("font-size: 8pt; color: #dddddd; font-weight: bold;");
	QLabel *headLAbel = new QLabel();
	headLAbel->setAlignment(Qt::AlignHCenter| Qt::AlignVCenter);
	headLAbel->setStyleSheet(top_style);
	headLAbel->setText("FLAPS");
	grpLay->addWidget(headLAbel);

	QHBoxLayout *splitLay = new QHBoxLayout();
	grpLay->addLayout(splitLay);




	//===
	slider = new QSlider();
	slider->setRange(0, 6);
	slider->setPageStep(1);
	slider->setSingleStep(1);
	slider->setTickInterval(1);
	slider->setTickPosition(QSlider::TicksRight);
	splitLay->addWidget(slider);
	connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(on_slider_moved(int)));


	//=================
	QString butt_style("font-size: 8pt; background-color: #222222; color: #dddddd; border: 2px solid #999999;");
	int widi = 40;

	QVBoxLayout *buttLay = new QVBoxLayout();
	splitLay->addLayout(buttLay);

	buttUp = new QToolButton();
	buttUp->setText("UP");
	buttUp->setStyleSheet(butt_style);
	buttUp->setFixedWidth(widi);
	buttLay->addWidget(buttUp);
	connect(buttUp, SIGNAL(clicked()), this, SLOT(on_button_up()));

	buttLay->addStretch(10);

	labelFlapsDeg = new QLabel();
	labelFlapsDeg->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	labelFlapsDeg->setStyleSheet("background-color: #444444; color: #dddddd; font-size 8pt; border 2px solid #aaaaaa; padding: 3px;");
	buttLay->addWidget(labelFlapsDeg);

	buttLay->addStretch(10);

	buttDown = new QToolButton();
	buttDown->setText("DOWN");
	buttDown->setStyleSheet(butt_style);
	buttDown->setFixedWidth(widi);
	buttLay->addWidget(buttDown);
	connect(buttDown, SIGNAL(clicked()), this, SLOT(on_button_down()));





	//======================
	progressBar = new QProgressBar();
	progressBar->setOrientation(Qt::Vertical);
	progressBar->setMinimum(0);
	progressBar->setMaximum(1000);
	progressBar->setTextVisible(false);
	progressBar->setStyleSheet("margin: 0; padding: 0; background-color: #aaaaaa;");
	splitLay->addWidget(progressBar);


}


void FlapsWidget::on_button_up()
{
	slider->setValue( slider->value()  + 1);
	send_new_flaps();
}
void FlapsWidget::on_button_down()
{
	slider->setValue( slider->value() - 1);
	send_new_flaps();
}

void FlapsWidget::on_slider_moved(int new_val)
{
	send_new_flaps();
}

void FlapsWidget::send_new_flaps()
{
	float val =  flapsVal.value( QString::number(6 - slider->value()));
	val = val / 1000;
	QString new_v = QString::number( val  );
	emit set_node("/controls/flight/flaps", new_v);
	emit fetch_node("/surface-positions/flap-pos-norm");
}


void FlapsWidget::on_node_val(QString node, QString val)
{
	static int last_flap = -1;

	if(node == "/surface-positions/flap-pos-norm"){

		float v =   (val.toFloat() * 1000);
		if(v != last_flap){
			progressBar->setValue(1000 - v);

			//qDebug() << "flaps= " << val << v << progressBar->value();
			//qDebug() << flapsVal.key(v);
			QString ki = flapsVal.key(v);
			if(ki.length() > 0){
				labelFlapsDeg->setText(QString::number(flapsDeg.value(ki)));
				slider->setValue(slider->maximum() -  ki.toInt());
			}else{
				labelFlapsDeg->setText("");
			}

			QTimer::singleShot(1000, this, SLOT(refresh_flaps()));
			last_flap = v;
		}
	}
}

void FlapsWidget::refresh_flaps()
{
	//qDebug() << "\nrefresh flaps";
	emit fetch_node("/surface-positions/flap-pos-norm");
}
