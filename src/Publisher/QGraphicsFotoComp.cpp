#include <assert.h>
#include <algorithm>
#include <QtGui/QGraphicsTextItem>
#include <QtGui/QGraphicsPixmapItem>
#include <QtGui/QTextDocument>
#include <QtGui/QPainter>

#include "QGraphicsFotoComp.h"
#include "QDialogFotoProperties.h"
#include "Foto.h"

const int QGraphicsFotoComp::SPACE = 5;

QGraphicsFotoComp::QGraphicsFotoComp(Foto *foto, QGraphicsItem *parent /*= 0*/)
	: QGraphicsItem(parent), m_pFoto(0), m_pBeschr(0), m_pFotoIntern(foto)
{
	assert(m_pFotoIntern != NULL);

	setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

	// Stel waarden in gebaseerd op interne gegevens
	setBeschrijving(QString::fromStdString(m_pFotoIntern->GetBeschrijving()));
	setFoto(QString::fromStdString(m_pFotoIntern->GetFoto()));
	SetPunt(foto->GetPunt());
}

/*virtual*/ QRectF QGraphicsFotoComp::boundingRect() const
{
	// Hoogte = hoogte foto + russenliggende ruimte + hoogte tekst
	qreal height = m_pFoto->boundingRect().height() + SPACE + m_pBeschr->boundingRect().height();
	// Breedte = max(breedte foto, breedte tekst)
	qreal width = std::max(m_pFoto->boundingRect().width(), m_pBeschr->boundingRect().width());
	// x coordinaat: 0 tenzij de beschrijving breder is dan de tekst.
	qreal x = std::min(0.0, m_pFoto->pos().x() + m_pFoto->pixmap().size().width() / 2 - m_pBeschr->document()->size().width() / 2);

	// Geef het berekende vierkant terug
	return QRectF(x, 0, width, height);
}

void QGraphicsFotoComp::setFoto(const QString &path)
{
	// 1 - Update internal component
	m_pFotoIntern->SetFoto(path.toStdString());

	// 2 - Update GUI representation
	delete m_pFoto;
	m_pFoto = new QGraphicsPixmapItem(QPixmap(path), this);
	if(m_pFoto->pixmap().isNull()) {
		qDebug("QGraphicsFotoComp::setFoto: file not found");
		m_pFoto = new QGraphicsPixmapItem(QPixmap(":/images/Resources/foto.png"), this);
	}
	// Zet de foto op positie (1, 1) zodat als men dit item selecteerd de volledige kader zichtbaar is!
	m_pFoto->setPos(1, 1);

	updateBeschrijvingPos();
}

void QGraphicsFotoComp::setBeschrijving(const QString &beschr)
{
	if(!m_pBeschr)
	{
		m_pBeschr = new QGraphicsTextItem(this);
	}
	m_pBeschr->setPlainText(beschr);
	updateBeschrijvingPos();
}

/*private*/ void QGraphicsFotoComp::updateBeschrijvingPos()
{
	// Only able to update if both foto and beschr exists
	if(m_pBeschr && m_pFoto)
	{
		// Calculate new position of our text label
		qreal x = m_pFoto->pos().x() + m_pFoto->pixmap().size().width() / 2 - m_pBeschr->document()->size().width() / 2;
		qreal y = m_pFoto->pos().y() + m_pFoto->pixmap().size().height() + SPACE;

		m_pBeschr->setPos(x, y);
		// Also update size!
		SetSize(boundingRect().size().toSize());
	}
	else
	{
		qDebug("QGraphicsFotoItem::updateBeschrijvingPos: beschrijving en/of foto bestaan niet");
	}
}

/*virtual*/ void QGraphicsFotoComp::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	// Als het geselecteerd is, teken er dan een kader rond
	if(isSelected())
	{
		painter->setPen(QPen(Qt::DashLine));
		painter->drawRect(boundingRect());
	}

	// Noot: de kinderen (foto en beschrijving) zijn zelf QGraphicsItems en hebben dus hun >eigen< paint functies etc.
}

/*virtual*/ bool QGraphicsFotoComp::openEditDialog()
{
	QDialogFotoProperties dialog;

	// Set properties of dialog
	dialog.SetPos(pos().toPoint());
	dialog.SetSize(boundingRect().size().toSize());
	dialog.SetFont(m_pBeschr->font());
	dialog.SetBeschrijving(m_pBeschr->toPlainText());
	dialog.SetLocatie(QString::fromStdString(m_pFotoIntern->GetFoto()));

	// Open dialog
	bool rval = dialog.exec();
	if(rval)
	{
		SetPunt(dialog.GetPos());
		SetFont(dialog.GetFont());
		setFoto(dialog.GetLocatie());
		setBeschrijving(dialog.GetBeschrijving());
	}

	return rval;
}

/*virtual*/ void QGraphicsFotoComp::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *)
{
	openEditDialog();
}

/*virtual*/ void QGraphicsFotoComp::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	SetPunt(this->pos());

	// Causes a repaint of the component and more importantly: causes the scene to emit a changed() signal
	update();

	QGraphicsItem::mouseReleaseEvent(event);
}

void QGraphicsFotoComp::SetPunt(const QPoint &punt)
{
	m_pFotoIntern->SetPunt(punt);
	setPos(punt);
}

void QGraphicsFotoComp::SetPunt(const QPointF &punt)
{
	m_pFotoIntern->SetPunt(punt.toPoint());
	setPos(punt);
}

void QGraphicsFotoComp::SetSize(const QSize &size)
{
	m_pFotoIntern->SetSize(size);
}

void QGraphicsFotoComp::SetFont(const QFont &font)
{
	m_pFotoIntern->SetFont(font);
	m_pBeschr->setFont(font);
}