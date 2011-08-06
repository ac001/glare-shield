#ifndef GSREADOUTWIDGET_H
#define GSREADOUTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QButtonGroup>

class GSReadoutWidget : public QWidget
{
Q_OBJECT
public:

	explicit GSReadoutWidget(QWidget *parent = 0);

	QButtonGroup *buttonGroup;

	QLabel *labelMain;
	QLabel *labelSide;

	int step_small;
	int step_big;

signals:
	//void set_node(QString node, QString value);
	void prop_val(int val);

public slots:
	void on_button(QAbstractButton *butt);

	//void node_val(QString node, QString value);

	void set_steps(int big, int small);
};

#endif // GSREADOUTWIDGET_H
