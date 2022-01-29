#include "CustomDelegate.h"
#include <qeventloop.h>
#include <qimagereader.h>
#include <qimage.h>
#include <qfile.h>

CustomDelegate::CustomDelegate(Controller* cont, QWidget* parent) : cont{ cont }, QStyledItemDelegate{ parent } {}

void CustomDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const{
	int row = index.row();
	if (row < this->cont->get_basket()->get_repo()->size()) {
		if (index.column() != 5) {
			QStyledItemDelegate::paint(painter, option, index);
			return;
		}
		TrenchCoat tc = this->cont->get_basket()->get_repo()->at(row);
		QUrl url(QString::fromStdString(tc.get_photograph()));
		std::string path = "Pictures\\";
		path += tc.get_name();
		path += " - ";
		path += tc.get_size();
		QPixmap pix(QString::fromStdString(path));
		painter->drawPixmap(option.rect, pix);
	}
}

QSize CustomDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const{
	if (index.column() == 5)
		return QSize(100, 100);
	return QStyledItemDelegate::sizeHint(option, index);
}
