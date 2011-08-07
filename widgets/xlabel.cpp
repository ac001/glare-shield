
#include <QtDebug>

#include "widgets/xlabel.h"

XLabel::XLabel(QWidget *parent) :
	QLabel(parent)
{
	QFont fo = font();
	fo.setBold(true);
	fo.setFamily("courier");
	fo.setPixelSize(60);
	setFont(fo);
}


void XLabel::mousePressEvent(QMouseEvent *ev)
{
	//= clicks in the top send nudge_value(bool) "up == true" otherwise false = down
	if( ev->y() < height() / 2){
		emit nudge_value(true);
	}else{
		emit nudge_value(true);
	}
}

void XLabel::focusInEvent(QFocusEvent *ev)
{
	emit got_focus(true);
	//setForegroundRole(QColor(250, 250, 0));
}

void XLabel::focusOutEvent(QFocusEvent *ev)
{
	emit got_focus(false);
}
