#ifndef LANDINGGEARWIDGET_H
#define LANDINGGEARWIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QToolButton>


class LandingGearWidget : public QWidget
{
Q_OBJECT
public:
	explicit LandingGearWidget(QWidget *parent = 0);

	QButtonGroup *buttonGroup;
	QToolButton *buttGearUp;
	QToolButton *buttGearDown;

signals:

public slots:

	void on_button(int);
};

#endif // LANDINGGEARWIDGET_H
