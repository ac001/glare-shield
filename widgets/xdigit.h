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

signals:
	void got_focus(bool focused_rasta);
	void nudge_value(int multi);

public slots:

};

#endif // XDIGIT_H
