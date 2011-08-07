
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
	gridMain->addLayout(topLayout,0,1,1,1);
	QString top_style("font-size: 9pt; color: #dddddd; font-weight: bold;");

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
	int butt_width = 14;

	QToolButton *buttonIncBig = new QToolButton();
	//buttDec10->setText("<<");
	buttonIncBig->setIcon(QIcon(":/icon/inc_big"));
	buttonIncBig->setProperty("val",QVariant("+big"));
	buttonIncBig->setAutoRaise(true);
	buttonIncBig->setStyleSheet(in_style);
	buttonIncBig->setFixedWidth(butt_width);
	gridMain->addWidget(buttonIncBig, 1, 0, 1, 1);
	buttonGroup->addButton(buttonIncBig);

	QToolButton *buttDecBig = new QToolButton();
	//buttDec1->setText("<");
	buttDecBig->setIcon(QIcon(":/icon/dec_big"));
	buttDecBig->setProperty("val",QVariant("-big"));
	buttDecBig->setStyleSheet(in_style);
	buttDecBig->setAutoRaise(true);
	buttDecBig->setFixedWidth(butt_width);
	gridMain->addWidget(buttDecBig, 2, 0, 1, 1);
	buttonGroup->addButton(buttDecBig);

	//===================================================
	QWidget *readoutWidget = new QWidget();
	readoutWidget->setStyleSheet("padding: 0px; margin: 0px; font-family: monospace; font-size: 32pt; font-weight: bold; background-color: #333333; color: #efefef; text-align: center; border: 2px inset #666666;");
	gridMain->addWidget(readoutWidget,1, 1, 2, 1);

	QGridLayout *readLay = new QGridLayout();
	int m = 3;
	readLay->setContentsMargins(m,m,m,m);
	readLay->setSpacing(0);
	readoutWidget->setLayout(readLay);

	labelMode = new QLabel();
	labelMode->setText("TRK");
	labelMode->setFixedWidth(40);
	labelMode->setAlignment(Qt::AlignRight);
	labelMode->setStyleSheet("margin: 0px; border: none; font-size: 12pt;  padding: 0; background-color: red;");
	readLay->addWidget(labelMode, 0, 0, 1, 1);

	labelPosNeg = new QLabel();
	labelPosNeg->setText("-");
	labelPosNeg->setFixedWidth(40);
	labelPosNeg->setAlignment(Qt::AlignRight);
	labelPosNeg->setStyleSheet("margin: 0px; border: none; font-size: 18pt;  padding: 0px 0px 5px 0px ;background-color: pink;");
	readLay->addWidget(labelPosNeg, 1, 0, 1, 1);

	QHBoxLayout *digitsLayout = new QHBoxLayout();
	readLay->addLayout(digitsLayout, 0, 1, 2, 1);

	//for(int loopy= digit_size -1; loopy >= 0; loopy--){
	for(int loopy = 0; loopy < digit_size; loopy++){
		XDigit *dig = new XDigit();
		dig->setText(QString::number(loopy));
		dig->setFixedHeight(45);
		dig->setFixedWidth(35);
		QString multi("1");
		multi.append( QString("0").repeated(digit_size - loopy - 1) );
		dig->setProperty("multi", multi);
		xDigits.append(dig);
		digitsLayout->addWidget(dig);
		connect(dig, SIGNAL(nudge_value(int)), this, SLOT(on_digit_nudge_value(int)));
	}







	QToolButton *buttIncSmall = new QToolButton();
	buttIncSmall->setIcon(QIcon(":/icon/inc_small"));
	buttIncSmall->setProperty("val","+small");
	buttIncSmall->setStyleSheet(in_style);
	buttIncSmall->setAutoRaise(true);
	buttIncSmall->setFixedWidth(butt_width);
	gridMain->addWidget(buttIncSmall, 1, 2, 1, 1);
	buttonGroup->addButton(buttIncSmall);

	QToolButton *buttDecSmall = new QToolButton();
	buttDecSmall->setIcon(QIcon(":/icon/dec_small"));
	buttDecSmall->setProperty("val","-small");
	buttDecSmall->setStyleSheet(in_style);
	buttDecSmall->setAutoRaise(true);
	buttDecSmall->setFixedWidth(butt_width);
	gridMain->addWidget(buttDecSmall, 2, 2, 1, 1);
	buttonGroup->addButton(buttDecSmall);

	QList<QAbstractButton*> buttons = buttonGroup->buttons();
	for(int i=0; i < buttons.length(); i++){
		buttons.at(i)->hide();
	}

}


void GSReadoutWidget::on_button(QAbstractButton *butt)
{
	QString prop = butt->property("val").toString();
	int val = 0;// labelMain->text().toInt();

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
