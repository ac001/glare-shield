#ifndef ALTITUDEWIDGET_H
#define ALTITUDEWIDGET_H

#include <QWidget>

#include "widgets/gsreadoutwidget.h"
#include "widgets/gsbutton.h"

class AltitudeWidget : public QWidget
{
Q_OBJECT
public:
	explicit AltitudeWidget(QWidget *parent = 0);

	GSReadoutWidget *gsReadout;

	GSButton *buttVNavEnabled;



signals:
	void set_node(QString node, QString val);


public slots:

	void on_val_changed(int val);

	void on_node_val(QString node, QString value);

};

#endif // ALTITUDEWIDGET_H
