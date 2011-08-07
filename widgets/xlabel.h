#ifndef XLABEL_H
#define XLABEL_H

#include <QLabel>

#include <QMouseEvent>

class XLabel : public QLabel
{
Q_OBJECT
public:
	explicit XLabel(QWidget *parent = 0);

	void mousePressEvent(QMouseEvent *ev);
	void focusInEvent(QFocusEvent *ev);
	void focusOutEvent(QFocusEvent *ev);


signals:
	void got_focus(bool focused_rasta);
	void nudge_value(bool up);

public slots:

};

#endif // XLABEL_H
