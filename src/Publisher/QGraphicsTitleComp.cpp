#include <assert.h>
#include <QtGui/QFontDialog>
#include <QtGui/QGraphicsWidget>
#include <QtGui/QPainter>
#include <QtGui/QTextDocument>
#include <QRectF>

#include "QGraphicsTitleComp.h"
#include "QDialogTitelProperties.h"
#include "titel.h"
#include "pagina.h"
#include "deel.h"

QGraphicsTitleComp::QGraphicsTitleComp(Titel *titel, QGraphicsItem *parent /*= 0*/)
	: QGraphicsTextItem(parent), m_pTitelIntern(titel)
{
	assert(m_pTitelIntern != NULL);

	// Stel waarden in gebaseerd op interne gegevens
	setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
	setPos(m_pTitelIntern->GetPunt());
	setFont(m_pTitelIntern->GetFont());
	UpdateTitel();

	connect(document(), SIGNAL(contentsChanged()), this, SLOT(saveText()));
}

/*virtual*/ void QGraphicsTitleComp::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if(!isSelected() || m_pTitelIntern->GetDeelTitel())
	{
		// Een deel titel mag niet worden veranderd. Voor een normale titel disablen we nu tekst
		// interactie zodat hij het component kan verslepen.
		setTextInteractionFlags(Qt::NoTextInteraction);
	}
	else
	{
		// Laat de gebruiker toe de titel te veranderen als het geen deel titel is, en het
		// component al geselecteerd is.
		setTextInteractionFlags(Qt::TextEditorInteraction);
	}

	QGraphicsTextItem::mousePressEvent(event);
}

/*virtual*/ void QGraphicsTitleComp::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	SetPunt(this->pos());
	SetSize(boundingRect().size().toSize());

	// Causes a repaint of the component and more importantly: causes the scene to emit a changed() signal
	update();

	QGraphicsTextItem::mouseReleaseEvent(event);
}

/*virtual*/ bool QGraphicsTitleComp::openEditDialog()
{
	QDialogTitelProperties dialog;

	// Set properties of dialog
	dialog.SetPos(pos().toPoint());
	dialog.SetSize(boundingRect().size().toSize());
	dialog.SetFont(font());
	dialog.SetTitel(toPlainText());
	dialog.SetDeelTitel(m_pTitelIntern->GetDeelTitel());

	// Open dialog
	bool rval = dialog.exec();
	if(rval)
	{
		SetPunt(dialog.GetPos());
		SetFont(dialog.GetFont());
		if(dialog.GetDeelTitel()) {
			SetDeelTitel(true);
		}
		else {
			SetDeelTitel(false);
			SetTitel(dialog.GetTitel());
		}
	}

	return rval;
}

/*virtual*/ void QGraphicsTitleComp::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *)
{
	openEditDialog();
}

void QGraphicsTitleComp::SetPunt(const QPoint &punt)
{
	m_pTitelIntern->SetPunt(punt);
	setPos(punt);
}

void QGraphicsTitleComp::SetPunt(const QPointF &punt)
{
	m_pTitelIntern->SetPunt(punt.toPoint());
	setPos(punt);
}

void QGraphicsTitleComp::SetSize(const QSize &)
{
	m_pTitelIntern->SetSize(boundingRect().size().toSize());
}

void QGraphicsTitleComp::SetFont(const QFont &font)
{
	m_pTitelIntern->SetFont(font);
	setFont(font);
}

void QGraphicsTitleComp::SetTitel(const QString &titel)
{
	m_pTitelIntern->SetInhoud(titel.toStdString());
	UpdateTitel();
}

void QGraphicsTitleComp::UpdateTitel()
{
	if(m_pTitelIntern->GetDeelTitel())
	{
		// Haal het deel op waarin deze titel zet
		Pagina *pagina = m_pTitelIntern->GetParent();
		assert(pagina != NULL);
		Deel *deel = pagina->GetParent();
		assert(pagina != NULL);

		// Haal nu de titel op
		setPlainText(QString::fromStdString(deel->GetTitel()));
	}
	else
	{
		setPlainText(QString::fromStdString(m_pTitelIntern->GetInhoud()));
	}
}

void QGraphicsTitleComp::SetDeelTitel(bool isDeelTitel)
{
	m_pTitelIntern->SetDeelTitel(isDeelTitel);
	UpdateTitel();
}

/*private slot*/ void QGraphicsTitleComp::saveText()
{
	m_pTitelIntern->SetInhoud(toPlainText().toStdString());
}
