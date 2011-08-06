


#include <QtGui/QApplication>

#include "glareshieldwidget.h"


int main(int argc, char *argv[])
{

	QApplication app(argc, argv);

	QApplication::setOrganizationName("Free Flight Sim");
	QApplication::setOrganizationDomain("freeflightsim.org");
	QApplication::setApplicationName("FFS Glare Shield");
	QApplication::setApplicationVersion("0.1");

	GlareShieldWidget widget;
	widget.show();

	return app.exec();
}
