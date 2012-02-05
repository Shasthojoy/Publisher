#include <assert.h>
#include <QtGui/QGraphicsSceneHoverEvent>
#include <QtGui/QCursor>
#include <QtGui/QTextDocument>
#include "QGraphicsTekstComp.h"
#include "QDialogTekstsProperties.h"

#include "tekst.h"

QGraphicsTekstComp::QGraphicsTekstComp(Tekst *tekst, QGraphicsItem *parent /*= 0*/)
	: QGraphicsSmartTextItem(tekst, parent), m_pTekstIntern(tekst)
{
	assert(m_pTekstIntern != NULL);

	setPlainText(QString::fromStdString(m_pTekstIntern->GetInhoud()));
	// SetFont, SetPos en setTextWidth worden in de constructor van SmartTextItem al opgeroepen!

	connect(document(), SIGNAL(contentsChanged()), this, SLOT(saveText()));
}

// Need to override the one from smartTextItem
/*virtual*/ void QGraphicsTekstComp::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if(isBottomRight(event->pos()))
	{
		// If clicked in the corner, resize
		m_resizing = true;
	}
	else if(!isSelected())
	{
		// Allow the user to drag the component
		setTextInteractionFlags(Qt::NoTextInteraction);
	}
	else
	{
		// If clicked a second time, open editor
		setTextInteractionFlags(Qt::TextEditorInteraction);
	}

	QGraphicsTextItem::mousePressEvent(event);
}

/*virtual*/ bool QGraphicsTekstComp::openEditDialog()
{
	QDialogTekstsProperties dialog;

	// Set properties of dialog
	dialog.SetPos(pos().toPoint());
	dialog.SetSize(boundingRect().size().toSize());
	dialog.SetFont(font());
	dialog.SetText(toPlainText());

	// Open dialog
	bool rval = dialog.exec();
	if(rval)
	{
		SetPunt(dialog.GetPos());
		SetFont(dialog.GetFont());
		SetInhoud(dialog.GetText());
		SetSize(dialog.GetSize().width());
	}

	return rval;
}

void QGraphicsTekstComp::SetInhoud(const QString &inhoud)
{
	setPlainText(inhoud);
	m_pTekstIntern->SetInhoud(inhoud.toStdString());
}

/*private slot*/ void QGraphicsTekstComp::saveText()
{
	m_pTekstIntern->SetInhoud(toPlainText().toStdString());
}