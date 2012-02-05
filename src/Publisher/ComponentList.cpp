#include <QVariant>
#include <QMimeData>
#include <QtGui/QDrag>

#include "ComponentList.h"
#include "Component.h"
#include "lijst.h"

const int ComponentList::ICON_HEIGHT = 45;
const int ComponentList::ICON_WIDTH = 45;

ComponentList::ComponentList(QWidget *parent /*= 0*/) : QListWidget(parent)
{
	// Get icon mode working
	setViewMode(QListView::IconMode);
	setIconSize(QSize(ICON_WIDTH, ICON_HEIGHT));
	setSpacing(5);
	setAcceptDrops(false);

	insertDefaultComponents();
}

void ComponentList::insertDefaultComponents()
{
	QListWidgetItem *pieceItem = new QListWidgetItem(this);
	pieceItem->setIcon(QIcon(":/images/Resources/tekst.png"));
	pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
	pieceItem->setData(Qt::UserRole, QVariant(CT_TEKST));

	pieceItem = new QListWidgetItem(this);
	pieceItem->setIcon(QIcon(":/images/Resources/bloklijst.png"));
	pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
	pieceItem->setData(Qt::UserRole, QVariant(CT_LIJST));
	pieceItem->setData(Qt::UserRole + 1, QVariant(LT_PUNTEN));

	pieceItem = new QListWidgetItem(this);
	pieceItem->setIcon(QIcon(":/images/Resources/cijferlijst.png"));
	pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
	pieceItem->setData(Qt::UserRole, QVariant(CT_LIJST));
	pieceItem->setData(Qt::UserRole + 1, QVariant(LT_NUMMERS));

	pieceItem = new QListWidgetItem(this);
	pieceItem->setIcon(QIcon(":/images/Resources/foto.png"));
	pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
	pieceItem->setData(Qt::UserRole, QVariant(CT_FOTO));

	pieceItem = new QListWidgetItem(this);
	pieceItem->setIcon(QIcon(":/images/Resources/inhoudsopgave.png"));
	pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
	pieceItem->setData(Qt::UserRole, QVariant(CT_INHOUDSOPGAVE));

	pieceItem = new QListWidgetItem(this);
	pieceItem->setIcon(QIcon(":/images/Resources/titel.png"));
	pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
	pieceItem->setData(Qt::UserRole, QVariant(CT_TITEL));

	pieceItem = new QListWidgetItem(this);
	pieceItem->setIcon(QIcon(":/images/Resources/boekinfo.png"));
	pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
	pieceItem->setData(Qt::UserRole, QVariant(CT_BOEKINFO));
}

/*virtual*/ void ComponentList::startDrag(Qt::DropActions)
{
	QListWidgetItem *item = currentItem();

	QByteArray itemData;
	QDataStream dataStream(&itemData, QIODevice::WriteOnly);

	QVariant test(CT_FOTO);
	dataStream << item->data(Qt::UserRole) << item->data(Qt::UserRole + 1);

	QMimeData *mimeData = new QMimeData();
	mimeData->setData("publisher/new-comp-drag", itemData);

	QDrag *drag = new QDrag(this);
	drag->setMimeData(mimeData);
	drag->setPixmap(item->icon().pixmap(QSize(ICON_WIDTH, ICON_HEIGHT)));
	drag->setHotSpot(QPoint());

	drag->exec(Qt::MoveAction);
}