#pragma once
#include <qwidget.h>
#include "GUIUser.h"
#include <QtCharts\qpieseries.h>
using namespace QtCharts;

class GUIChart : public QWidget{
private:
	GUIUser* parent;
	QPieSeries* pie;
	void init();
public:
	GUIChart(GUIUser* p);
	~GUIChart() = default;
};

