


#include <QtGui/QApplication>

#include "glareshieldwidget.h"


int main(int argc, char *argv[])
{

	QApplication app(argc, argv);

	QApplication::setOrganizationName("Free Flight Sim");
	QApplication::setOrganizationDomain("freeflightsim.org");
	QApplication::setApplicationName("FFS Glare Shield");
	QApplication::setApplicationVersion("0.1");



	QString styles("");
	styles.append("GlareShieldWidget{background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #909090, stop: 1 #6A6A6A);}");
	styles.append("QGroupBox{ background-color: transparent; border: 1px solid #808080;}");
	app.setStyleSheet(styles);

	GlareShieldWidget widget;
	widget.show();

	return app.exec();
}
