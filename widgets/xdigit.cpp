
#include <QtDebug>

#include "widgets/xdigit.h"

XDigit::XDigit(QWidget *parent) :
	QLabel(parent)
{
	//QFont fo = font();
	//fo.setBold(true);
	//fo.setFamily("monospace");
	//fo.setPixelSize(10);
	//setFont(fo);
	setStyleSheet("border: none; color: white; font-family: monospaced; font-size: 20pt;");
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
