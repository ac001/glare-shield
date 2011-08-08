#ifndef FLAPSWIDGET_H
#define FLAPSWIDGET_H

#include <QMap>

#include <QWidget>
#include <QLabel>

#include <QSlider>
#include <QToolButton>
#include <QProgressBar>

class FlapsWidget : public QWidget
{
Q_OBJECT
public:
	explicit FlapsWidget(QWidget *parent = 0);

	QProgressBar *progressBar;
	QSlider *slider;

	QToolButton *buttUp;
	QToolButton *buttDown;
	QLabel *labelFlapsDeg;

	QMap<QString, int> flapsDeg;
	QMap<QString, int> flapsVal;


signals:
	void fetch_node(QString node);
	void set_node(QString node, QString val);

public slots:

	void on_node_val(QString node, QString val);

	void on_button_up();
	void on_button_down();
	void on_slider_moved(int);
	void send_new_flaps();

	void refresh_flaps();

};

#endif // FLAPSWIDGET_H
