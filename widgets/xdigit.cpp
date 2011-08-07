
#include <QtDebug>

#include "widgets/xdigit.h"

XDigit::XDigit(QWidget *parent) :
	QLabel(parent)
{
	QFont fo = font();
	fo.setBold(true);
	fo.setFamily("courier");
	fo.setPixelSize(60);
	setFont(fo);
	setStyleSheet("border: none; color: white;");
}


void XDigit::mousePressEvent(QMouseEvent *ev)
{
	int multi = property("multi").toInt();
	if( ev->y() < height() / 2){
		emit nudge_value(multi);
	}else{
		emit nudge_value(multi * -1);
	}
}
