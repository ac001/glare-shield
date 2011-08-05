
#include <QHBoxLayout>


#include "glareshieldwidget.h"

#include "network/servercall.h"

GlareShieldWidget::GlareShieldWidget(QWidget *parent) :
	QWidget(parent)
{

	QHBoxLayout *mainLayout = new QHBoxLayout();
	setLayout(mainLayout);

	AutoThrottleWidget *autoThrottleWidget = new AutoThrottleWidget();
	mainLayout->addWidget(autoThrottleWidget);


	serverCall = new ServerCall(this);
	connect(autoThrottleWidget, SIGNAL(fetch_node(QString)), serverCall, SLOT(fetch_node(QString)));
}
