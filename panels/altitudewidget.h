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

	GSReadoutWidget *gsAltitudeHold;
	GSReadoutWidget *gsVerticalSpeed;

	GSButton *buttAltitudeHoldEnabled;
	GSButton *buttVSEnabled;


signals:
	void set_node(QString node, QString val);


public slots:


	void on_vs_fpa();

	void on_node_val(QString node, QString value);

	void on_vs_button_clicked();
	void on_vs_changed(int val);

	void on_alt_changed(int val);
	void on_alt_hold_button_clicked();
};

#endif // ALTITUDEWIDGET_H
