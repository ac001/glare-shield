#ifndef AUTOTHROTTLEWIDGET_H
#define AUTOTHROTTLEWIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QLCDNumber>




class AutoThrottleWidget : public QWidget
{
Q_OBJECT
public:
	explicit AutoThrottleWidget(QWidget *parent = 0);

	QButtonGroup *buttGroupSpeed;
	QLCDNumber *lcdSpeed;



signals:
	void fetch_node(QString node);

public slots:
	void on_speed_button(QAbstractButton *butt);


};

#endif // AUTOTHROTTLEWIDGET_H
