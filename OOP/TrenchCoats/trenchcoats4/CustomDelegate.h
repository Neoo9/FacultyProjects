#pragma once
#include <qstyleditemdelegate.h>
#include <qpixmap.h>
#include <qpainter.h>
#include "Controller.h"
#include <QNetworkAccessManager>
#include <qnetworkreply.h>
#include <qurl.h>

class CustomDelegate : public QStyledItemDelegate{
private:
	Controller* cont;
public:
	CustomDelegate(Controller* cont, QWidget* parent = NULL);
	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
	QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
public slots:
	void finish(QNetworkReply* reply, QPainter* painter, const QStyleOptionViewItem& option);
};

