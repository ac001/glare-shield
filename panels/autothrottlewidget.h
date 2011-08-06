#ifndef AUTOTHROTTLEWIDGET_H
#define AUTOTHROTTLEWIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QLabel>
#include <QRadioButton>

#include "widgets/gsbutton.h"
#include "widgets/gsreadoutwidget.h"

class AutoThrottleWidget : public QWidget
{
Q_OBJECT
public:
	explicit AutoThrottleWidget(QWidget *parent = 0);

	GSReadoutWidget *gsReadout;

	QRadioButton *radioSpeedWithThrottle;
	QRadioButton *radioSpeedWithPitch;

	GSButton *buttATEnabled;

signals:
	void fetch_node(QString node);
	void set_node(QString node, QString val);

public slots:

	void on_node_val(QString node, QString val);


	void on_val_changed(int val);
	void on_at_button_clicked();
};

#endif // AUTOTHROTTLEWIDGET_H
