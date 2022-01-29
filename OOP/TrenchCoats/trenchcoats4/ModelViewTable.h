#pragma once
#include <qabstractitemmodel.h>
#include "Controller.h"
#include "Observer.h"

class ModelViewTable : public QAbstractTableModel, public Observer{
private:
	Controller* cont;
public:
	ModelViewTable(Controller* cont, QObject* parent = NULL);
	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
	int columnCount(const QModelIndex& parent = QModelIndex{}) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	void update();
};

