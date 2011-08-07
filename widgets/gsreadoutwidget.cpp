
#include <QtDebug>

#include <QVariant>

#include <QGridLayout>
#include <QToolButton>



#include "widgets/gsreadoutwidget.h"

GSReadoutWidget::GSReadoutWidget(int digits, QWidget *parent) :
	QWidget(parent)
{
	digit_size = digits;
	step_big = 10;
	step_small = 1;


	//setFixedHeight(100);


	QGridLayout *gridMain = new QGridLayout();
	gridMain->setContentsMargins(0,0,0,0);
	gridMain->setSpacing(0);
	setLayout(gridMain);

	//=====================================================
	QHBoxLayout *topLayout = new QHBoxLayout();
	topLayout->setSpacing(5);
	topLayout->setContentsMargins(0, 0, 0, 5);
	gridMain->addLayout(topLayout,0,1,1,1);
	QString top_style("font-size: 7pt; color: #cccccc; font-weight: bold;");

	topLayout->addStretch(10);

	topLabelLeft = new QLabel();
	topLabelLeft->setAlignment(Qt::AlignRight| Qt::AlignVCenter);
	topLabelLeft->setStyleSheet(top_style);

	topLayout->addWidget(topLabelLeft);

	buttonTop = new QToolButton();
	buttonTop->setAutoRaise(false);
	buttonTop->setStyleSheet("padding: O; background-color: #aaaaaa;");
	buttonTop->setFixedHeight(16);
	buttonTop->setFixedWidth(16);
	topLayout->addWidget(buttonTop);
	connect(buttonTop, SIGNAL(clicked()), this, SLOT(on_top_button()));

	topLabelCenter = new QLabel();
	topLabelCenter->setStyleSheet(top_style);
	topLayout->addWidget(topLabelCenter);

	topLabelRight = new QLabel();
	topLabelRight->setStyleSheet(top_style);
	topLayout->addWidget(topLabelRight);


	topLayout->addStretch(10);



	//===================================================
	QWidget *readoutWidget = new QWidget();
	readoutWidget->setStyleSheet("padding: 0px; margin: 0px;  font-weight: bold; background-color: #333333; color: #efefef; text-align: center; border: 2px inset #666666;");
	gridMain->addWidget(readoutWidget,1, 1, 2, 1);

	QHBoxLayout *readLay = new QHBoxLayout();
	int m = 3;
	readLay->setContentsMargins(m,m,m,m);
	readLay->setSpacing(0);
	readoutWidget->setLayout(readLay);

	QVBoxLayout *sideLay = new QVBoxLayout();
	readLay->addLayout(sideLay);

	labelMode = new QLabel();
	labelMode->setText("TRK");
	labelMode->setFixedWidth(40);
	//labelMode->setFixedHeight(20);
	//labelMode->setContentsMargins(0,5,0,0);
	labelMode->setAlignment(Qt::AlignHCenter);
	labelMode->setStyleSheet("margin: 0px; border: none; font-size: 8pt;  font-family: monospace; padding: 0px 0px 0px 0px;");
	sideLay->addWidget(labelMode);

	labelPosNeg = new QLabel();
	labelPosNeg->setText("-");
	labelPosNeg->setFixedWidth(40);
	labelPosNeg->setAlignment(Qt::AlignRight|Qt::AlignTop);
	labelPosNeg->setStyleSheet("margin: 0px; border: none; font-size: 14pt;  padding: 0px 0px 0px 0px;");
	sideLay->addWidget(labelPosNeg);

	sideLay->addStretch(20);

	QHBoxLayout *digitsLayout = new QHBoxLayout();
	readLay->addLayout(digitsLayout);

	for(int loopy = 0; loopy < digit_size; loopy++){
		XDigit *dig = new XDigit();
		dig->setText(QString::number(loopy));
		dig->setFixedHeight(32);
		dig->setFixedWidth(28);
		dig->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
		QString multi("1");
		multi.append( QString("0").repeated(digit_size - loopy - 1) );
		dig->setProperty("multi", multi);
		xDigits.append(dig);
		digitsLayout->addWidget(dig);
		connect(dig, SIGNAL(nudge_value(int)), this, SLOT(on_digit_nudge_value(int)));
	}


}



void GSReadoutWidget::setup(int big, int small, bool show_side_widgets)
{
	step_big = big;
	step_small = small;
	labelMode->setVisible(show_side_widgets);
	labelPosNeg->setVisible(show_side_widgets);
}


void GSReadoutWidget::set_value(QString value)
{
	int idx;
	int v = value.toInt();
	if(v < 0){
		labelPosNeg->setText("-");
		v = v * -1;
	}else{
		labelPosNeg->setText("");
	}
	QString number = QString("%1").arg(v, digit_size, 10, QChar('0')).toUpper();
	for(idx = 0; idx < number.length(); idx++){
		xDigits.at( idx )->setText(number.at(idx));
	}

}

void GSReadoutWidget::set_top(QString center)
{
	topLabelLeft->hide();
	topLabelRight->hide();
	buttonTop->hide();
	topLabelCenter->setText(center);
}
void GSReadoutWidget::set_top(QString left, QString right)
{
	topLabelCenter->hide();
	topLabelLeft->setText(left);
	topLabelRight->setText(right);
}


void GSReadoutWidget::on_digit_nudge_value(int add)
{
	qDebug() << add;
	int v = get_display_val().toInt();
	if(labelPosNeg->text() == "-"){
		v = v * -1;
	}
	v = v + add;

	emit prop_val(v);

}

QString GSReadoutWidget::get_display_val()
{
	QString v("");
	for(int i=0; i < xDigits.size(); i++){
		v.append(xDigits.at(i)->text());
	}
	return v;
}

void GSReadoutWidget::on_top_button()
{
	emit on_top();
}
