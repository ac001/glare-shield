#ifndef FLAPSWIDGET_H
#define FLAPSWIDGET_H

#include <QWidget>

#include <QSlider>
#include <QToolButton>
#include <QProgressBar>

class FlapsWidget : public QWidget
{
Q_OBJECT
public:
	explicit FlapsWidget(QWidget *parent = 0);

	QProgressBar *progress;
	QSlider *slider;

	QToolButton *buttUp;
	QToolButton *buttDown;


signals:
	void fetch_node(QString node);
	void set_node(QString node, QString val);
public slots:

	void on_node_val(QString node, QString val);

	void on_button_up();
	void on_button_down();
	void on_slider_value();


};

#endif // FLAPSWIDGET_H
