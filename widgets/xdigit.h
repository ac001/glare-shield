#ifndef XDIGIT_H
#define XDIGIT_H

#include <QLabel>

#include <QMouseEvent>

class XDigit : public QLabel
{
Q_OBJECT
public:
	explicit XDigit(QWidget *parent = 0);

	void mousePressEvent(QMouseEvent *ev);
	void focusInEvent(QFocusEvent *ev);
	void focusOutEvent(QFocusEvent *ev);


signals:
	void got_focus(bool focused_rasta);
	void nudge_value(bool up);

public slots:

};

#endif // XDIGIT_H
