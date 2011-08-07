#ifndef HEADINGWIDGET_H
#define HEADINGWIDGET_H

#include <QWidget>

#include "widgets/gsreadoutwidget.h"
#include "widgets/gsbutton.h"

class HeadingWidget : public QWidget
{
Q_OBJECT
public:
	explicit HeadingWidget(QWidget *parent = 0);

	GSReadoutWidget *gsHeading;

	GSButton *buttHeadingHoldEnabled;

signals:

	void set_node(QString node, QString val);

public slots:


	void on_node_val(QString node, QString value);

	void on_heading_button_clicked();
	void on_heading_changed(int val);

	void on_top_button();

};

#endif // HEADINGWIDGET_H
