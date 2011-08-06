
#include <QtDebug>

#include <QVariant>

#include <QGridLayout>
#include <QToolButton>



#include "widgets/gsreadoutwidget.h"

GSReadoutWidget::GSReadoutWidget(QWidget *parent) :
	QWidget(parent)
{
	step_big = 10;
	step_small = 1;
	digit_size = 3;
	setFixedHeight(100);
	//setFixedHeight(100);


	QGridLayout *gridMain = new QGridLayout();
	gridMain->setContentsMargins(0,0,0,0);
	//gridMain->set
	setLayout(gridMain);

	//=====================================================
	QHBoxLayout *topLayout = new QHBoxLayout();
	gridMain->addLayout(topLayout,0,1,1,3);
	QString top_style("font-size: 9pt; color: #dddddd; font-weight: bold;");

	topLayout->addStretch(10);

	topLabelLeft = new QLabel();
	topLabelLeft->setAlignment(Qt::AlignRight| Qt::AlignVCenter);
	topLabelLeft->setStyleSheet(top_style);
	topLayout->addWidget(topLabelLeft);

	buttonTop = new QToolButton();
	buttonTop->setAutoRaise(false);
	buttonTop->setStyleSheet("padding: O;");
	topLayout->addWidget(buttonTop);

	topLabelCenter = new QLabel();
	topLabelCenter->setStyleSheet(top_style);
	topLayout->addWidget(topLabelCenter);

	topLabelRight = new QLabel();
	topLabelRight->setStyleSheet(top_style);
	topLayout->addWidget(topLabelRight);


	topLayout->addStretch(10);


	//=====================================================
	buttonGroup = new QButtonGroup(this);
	connect(buttonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(on_button(QAbstractButton*)));

	QString in_style("padding: 0px; margin: 0px;");

	//buttLay->addStretch(10);

	QToolButton *buttonIncBig = new QToolButton();
	//buttDec10->setText("<<");
	buttonIncBig->setIcon(QIcon(":/icon/inc_big"));
	buttonIncBig->setProperty("val",QVariant("+big"));
	buttonIncBig->setAutoRaise(true);
	buttonIncBig->setStyleSheet(in_style);
	gridMain->addWidget(buttonIncBig, 1, 0, 1, 1);
	buttonGroup->addButton(buttonIncBig);

	QToolButton *buttDecBig = new QToolButton();
	//buttDec1->setText("<");
	buttDecBig->setIcon(QIcon(":/icon/dec_big"));
	buttDecBig->setProperty("val",QVariant("-big"));
	buttDecBig->setStyleSheet(in_style);
	buttDecBig->setAutoRaise(true);
	gridMain->addWidget(buttDecBig, 2, 0, 1, 1);
	buttonGroup->addButton(buttDecBig);

	//===================================================
	QWidget *readoutWidget = new QWidget();
	readoutWidget->setStyleSheet("padding: 0px; margin: 0px; font-family: monospace; font-size: 32pt; font-weight: bold; background-color: #333333; color: #efefef; text-align: center; border: 2px inset #666666;");
	gridMain->addWidget(readoutWidget,1, 1, 2, 1);

	QGridLayout *readLay = new QGridLayout();
	readoutWidget->setLayout(readLay);

	labelSide = new QLabel();
	labelSide->setText("TRK");
	labelSide->setFixedWidth(40);
	labelSide->setStyleSheet("margin: 0px; border: none; font-size: 12pt;  padding: 2px;");
	readLay->addWidget(labelSide,0, 0, 1, 1);


	labelMain = new QLabel();
	labelMain->setText("30000");
	labelMain->setStyleSheet("margin: 0px; border: none; font-size: 32pt;  padding: 2px;");
	readLay->addWidget(labelMain, 0, 1, 2, 1);





	QToolButton *buttIncSmall = new QToolButton();
	buttIncSmall->setIcon(QIcon(":/icon/inc_small"));
	buttIncSmall->setProperty("val","+small");
	buttIncSmall->setStyleSheet(in_style);
	buttIncSmall->setAutoRaise(true);
	gridMain->addWidget(buttIncSmall, 1, 2, 1, 1);
	buttonGroup->addButton(buttIncSmall);

	QToolButton *buttDecSmall = new QToolButton();
	buttDecSmall->setIcon(QIcon(":/icon/dec_small"));
	buttDecSmall->setProperty("val","-small");
	buttDecSmall->setStyleSheet(in_style);
	buttDecSmall->setAutoRaise(true);
	gridMain->addWidget(buttDecSmall, 2, 2, 1, 1);
	buttonGroup->addButton(buttDecSmall);

}


void GSReadoutWidget::on_button(QAbstractButton *butt)
{
	QString prop = butt->property("val").toString();
	int val = labelMain->text().toInt();

	if(prop == "+big"){
		emit prop_val(val + step_big);

	}else if(prop == "-big"){
		emit prop_val(val - step_big);

	}else if(prop == "+small"){
		emit prop_val(val + step_small);

	}else if(prop == "-small"){
		emit prop_val(val - step_small);
	}
}



void GSReadoutWidget::setup(int digit_siz, int big, int small)
{
	step_big = big;
	step_small = small;
	digit_size = digit_siz;
}


void GSReadoutWidget::set_value(QString value)
{
	QString zeros("00000");
	qDebug() << value;
	if(value.length() != digit_size){
		value.prepend(zeros.mid(0, digit_size - value.length()));
	}
	labelMain->setText(value);

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
