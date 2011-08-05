#ifndef AUTOTHROTTLEWIDGET_H
#define AUTOTHROTTLEWIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>



class AutoThrottleWidget : public QWidget
{
Q_OBJECT
public:
	explicit AutoThrottleWidget(QWidget *parent = 0);

	QButtonGroup *buttGroupSpeed;
	QLabel *labelSpeed;

	QRadioButton *radioSpeedWithThrottle;
	QRadioButton *radioSpeedWithPitch;

	QPushButton *buttATEnabled;

signals:
	void fetch_node(QString node);
	void set_node(QString node, QString val);

public slots:
	void on_speed_button(QAbstractButton *butt);
	void on_node_val(QString node, QString val);
	//void on_node_vals(QHash<QString,QString>);
	void on_at_button_clicked();
};

#endif // AUTOTHROTTLEWIDGET_H
