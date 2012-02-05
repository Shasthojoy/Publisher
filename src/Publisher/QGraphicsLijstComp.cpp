#include <assert.h>
#include <sstream>
#include <QtGui/QGraphicsSceneMouseEvent>
using std::stringstream;

#include "QGraphicsLijstComp.h"
#include "QDialogLijstProperties.h"
#include "lijst.h"

QGraphicsLijstComp::QGraphicsLijstComp(Lijst *lijst, QGraphicsTextItem *parent /*= 0*/)
	 : QGraphicsSmartTextItem(lijst, parent), m_pLijstIntern(lijst)
{
	assert(m_pLijstIntern != NULL);

	// SetFont, SetPos en setTextWidth worden in de constructor van SmartTextItem al opgeroepen!

	updateText();
}

/*virtual*/ bool QGraphicsLijstComp::openEditDialog()
{
	QDialogLijstProperties dialog;
	dialog.SetFont(font());
	dialog.SetLijstType(m_pLijstIntern->GetLijstType());
	dialog.SetPos(pos().toPoint());
	dialog.SetSize(boundingRect().size().toSize());
	dialog.SetItems(lijstToText(false));

	bool rval = dialog.exec();
	if(rval)
	{
		textToLijst(dialog.GetItems());
		SetFont(dialog.GetFont());
		SetPunt(dialog.GetPos());
		SetSize(dialog.GetSize());
		SetLijstType(dialog.GetLijstType());

		updateText();
	}

	return rval;
}

/*virtual*/ void QGraphicsLijstComp::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QGraphicsTextItem::paint(painter, option, widget);
}

string QGraphicsLijstComp::prefixLijst(int no, LijstType type)
{
	string prefix;
	stringstream out;

	switch(type)
	{
	case LT_NUMMERS:
		out << no;
		prefix = out.str();
		prefix += ".  ";
		break;

	case LT_PUNTEN:
		prefix = "*   ";
		break;
	}

	return prefix;
}

QString QGraphicsLijstComp::lijstToText(bool includePrefix)
{
	string teksts;
	LijstType type = m_pLijstIntern->GetLijstType();

	// Zet de eerste n - 1 items om naar een string, met een newline op het einde
	int aantal = m_pLijstIntern->AantalItems();
	for(int i = 0; i < aantal - 1; ++i)
	{
		if(includePrefix) {
			teksts += prefixLijst(i + 1, type);
		}
		teksts += m_pLijstIntern->GetItem(i) + '\n';
	}

	// Zet het laatste item om naar een string, nu ZONDER een newline!
	if(aantal > 0) {
		if(includePrefix) {
			teksts += prefixLijst(aantal, type);
		}
		teksts += m_pLijstIntern->GetItem(aantal - 1);
	}

	return QString::fromStdString(teksts);
}

void QGraphicsLijstComp::textToLijst(const list<string> &lijst)
{
	m_pLijstIntern->clear();

	for(list<string>::const_iterator it = lijst.begin(); it != lijst.end(); ++it)
	{
		m_pLijstIntern->AddItem(*it);
	}
}

inline void QGraphicsLijstComp::updateText()
{
	setPlainText(lijstToText(true));
}

void QGraphicsLijstComp::SetLijstType(LijstType type)
{
	m_pLijstIntern->SetLijstType(type);
	updateText();
}