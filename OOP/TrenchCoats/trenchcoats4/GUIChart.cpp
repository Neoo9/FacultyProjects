#include "GUIChart.h"
#include <QtCharts/qchart.h>
#include <QtCharts/qchartview.h>

GUIChart::GUIChart(GUIUser* p) :parent{ p } {
	this->init();
}

void GUIChart::init(){
	this->setAttribute(Qt::WA_DeleteOnClose);
	QMainWindow* main = new QMainWindow();
	this->pie = new QPieSeries();
	int index = 0;
	std::vector<std::string> sizes{ "S", "M", "L", "XL", "XXL" };
	for (auto& size : sizes) {
		int quantity = this->parent->cont->user_search_coats_cont(size, this->parent->temp);
		this->pie->append(QString::fromStdString(size), quantity);
		QPieSlice* slice = this->pie->slices().at(index);
		QString label;
		label += QString::fromStdString(size);
		label += ", ";
		label += QString::number(quantity);
		slice->setLabel(label);
		index++;
	}
	QChart* chart = new QChart();
	chart->addSeries(this->pie);
	chart->legend()->setAlignment(Qt::AlignRight);
	chart->setTitle("Number of sizes");
	QChartView* chart_view = new QChartView(chart);
	chart_view->setRenderHint(QPainter::Antialiasing);
	main->setCentralWidget(chart_view);
	main->setMinimumSize(400, 300);
	main->show();
}
