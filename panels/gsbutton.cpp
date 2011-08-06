#include "panels/gsbutton.h"

GSButton::GSButton(QWidget *parent) :
	QToolButton(parent)
{
	setCheckable(true);
	setIcon(QIcon(":/icon/butt_off"));
	setFixedWidth(50);
	setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	setStyleSheet("background-color: black; color: white; font-weight: bold; font-family: sans-serif; font-size: 11pt; padding-top: 3px;");
}

void GSButton::set_state(bool checked)
{
	setIcon( QIcon( checked ? ":/icon/butt_on" : ":/icon/butt_off") );
	if(checked != isChecked()){
		setChecked(checked);
	}
}
