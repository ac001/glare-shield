#ifndef GSBUTTON_H
#define GSBUTTON_H

#include <QToolButton>

class GSButton : public QToolButton
{
Q_OBJECT
public:
	explicit GSButton(QWidget *parent = 0);

signals:

public slots:
	void set_state(bool checked);
};

#endif // GSBUTTON_H
