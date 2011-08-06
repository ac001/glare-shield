#ifndef GSREADOUTWIDGET_H
#define GSREADOUTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QButtonGroup>
#include <QToolButton>

class GSReadoutWidget : public QWidget
{
Q_OBJECT
public:

	explicit GSReadoutWidget(QWidget *parent = 0);

	QLabel *topLabelLeft;
	QLabel *topLabelRight;
	QLabel *topLabelCenter;
	QToolButton *buttonTop;

	QButtonGroup *buttonGroup;

	QLabel *labelMain;
	QLabel *labelSide;

	int step_small;
	int step_big;
	int digit_size;

	void set_top(QString center);
	void set_top(QString left, QString right);
signals:
	//void set_node(QString node, QString value);
	void prop_val(int val);

public slots:
	void on_button(QAbstractButton *butt);

	//void node_val(QString node, QString value);

	void setup(int digit_size, int big, int small);

	void set_value(QString value);
};

#endif // GSREADOUTWIDGET_H
