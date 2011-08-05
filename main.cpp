


#include <QtGui/QApplication>

#include "glareshieldwidget.h"


int main(int argc, char *argv[])
{

	QApplication app(argc, argv);

	GlareShieldWidget widget;
	widget.show();

	return app.exec();
}
