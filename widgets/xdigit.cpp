
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
}


void XDigit::mousePressEvent(QMouseEvent *ev)
{
	//= clicks in the top send nudge_value(bool) "up == true" otherwise false = down
	if( ev->y() < height() / 2){
		emit nudge_value(true);
	}else{
		emit nudge_value(true);
	}
}

void XDigit::focusInEvent(QFocusEvent *ev)
{
	emit got_focus(true);
	//setForegroundRole(QColor(250, 250, 0));
}

void XDigit::focusOutEvent(QFocusEvent *ev)
{
	emit got_focus(false);
}
