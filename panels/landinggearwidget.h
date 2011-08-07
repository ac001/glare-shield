#ifndef LANDINGGEARWIDGET_H
#define LANDINGGEARWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QToolButton>


class LandingGearWidget : public QWidget
{
Q_OBJECT
public:
	explicit LandingGearWidget(QWidget *parent = 0);


	QToolButton *buttGearUp;
	QToolButton *buttGearDown;

	QLabel *lblGear1;
	QLabel *lblGear2;
	QLabel *lblGear3;

signals:
	void set_node(QString node, QString value);
	void fetch_node(QString node);
public slots:

	void on_node_val(QString, QString);

	void on_gear_down_button(bool);
	void on_gear_up_button(bool);
	void set_butt_style();

	void set_indicator_style(int state);
	void set_indicator_text(QString label);
	void clear_indicator_text();

	void refresh_gear_pos();

};

#endif // LANDINGGEARWIDGET_H
