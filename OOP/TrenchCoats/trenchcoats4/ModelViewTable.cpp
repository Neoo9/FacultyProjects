#include "ModelViewTable.h"

ModelViewTable::ModelViewTable(Controller* cont, QObject* parent) :cont{ cont }, QAbstractTableModel{ parent } {}

int ModelViewTable::rowCount(const QModelIndex& parent) const{
	return this->cont->get_controller()->get_repo()->size();
}

int ModelViewTable::columnCount(const QModelIndex& parent) const {
	return 6;
}

QVariant ModelViewTable::data(const QModelIndex& index, int role) const {
	int row = index.row();
	int col = index.column();
	if (role == Qt::DisplayRole && row < this->cont->get_basket()->get_repo()->size()) {
		TrenchCoat tc = this->cont->get_basket()->get_repo()->at(row);
		switch (col) {
		case 0:
			return QString::fromStdString(tc.get_name());
		case 1:
			return QString::fromStdString(tc.get_size());
		case 2:
			return QString::fromStdString(tc.get_colour());
		case 3:
			return QString::number(tc.get_price());
		case 4:
			return QString::number(tc.get_quantity());
		case 5:
			return QString::fromStdString("placeholder");
		default:
			break;
		}
	}
	return QVariant();
}

QVariant ModelViewTable::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			switch (section) {
			case 0:
				return QString("Trench coat name");
			case 1:
				return QString("Size");
			case 2:
				return QString("Colour");
			case 3:
				return QString("Price");
			case 4:
				return QString("Quantity");
			case 5:
				return QString("Picture");
			default:
				break;
			}
		}
	}
	return QVariant();
}

void ModelViewTable::update() {
	endResetModel();
}
