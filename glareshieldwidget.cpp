
#include <QHBoxLayout>


#include "glareshieldwidget.h"



GlareShieldWidget::GlareShieldWidget(QWidget *parent) :
	QWidget(parent)
{

	QHBoxLayout *mainLayout = new QHBoxLayout();
	setLayout(mainLayout);

	AutoThrottleWidget *autoThrottleWidget = new AutoThrottleWidget();
	mainLayout->addWidget(autoThrottleWidget);
}
