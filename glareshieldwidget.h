#ifndef GLARESHIELDWIDGET_H
#define GLARESHIELDWIDGET_H

#include <QWidget>

#include "panels/autothrottlewidget.h"

class GlareShieldWidget : public QWidget
{
Q_OBJECT
public:
	explicit GlareShieldWidget(QWidget *parent = 0);


	AutoThrottleWidget *autoThrottleWidget;

signals:

public slots:

};

#endif // GLARESHIELDWIDGET_H
