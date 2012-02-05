#include <assert.h>
#include <QtGui/QWidget>
#include <QtGui/QGraphicsSceneMouseEvent>
#include <QtGui/QGraphicsSceneDragDropEvent>
#include <QtGui/QPainter>
#include <QtGui/QStyleOptionGraphicsItem>
#include <QtGui/QGraphicsItem>
#include <QtGui/QDrag>
#include <QtGui/QKeyEvent>
#include <QMimeData>
#include <QByteArray>
#include <QDataStream>

#include "PubGraphicsScene.h"
#include "QGraphicsTekstComp.h"
#include "QGraphicsTitleComp.h"
#include "QGraphicsFotoComp.h"
#include "QGraphicsLijstComp.h"
#include "QGraphicsBoekInfoComp.h"
#include "QGraphicsInhoudComp.h"
#include "Pagina.h"
#include "Opties.h"

PubGraphicsScene::PubGraphicsScene(QObject *parent) : QGraphicsScene(0, 0, 420 - 2, 560 - 2, parent),
	m_isEnabled(false), m_pPagina(NULL), holdingShift(false)
{
	disable();
}

void PubGraphicsScene::render(Pagina *pagina)
{
	assert(pagina != NULL);

	clear();

	int aantal = pagina->AantalComponenten();
	for(int i = 0; i < aantal; ++i)
	{
		Component *comp = pagina->GetComponent(i);

		// We moeten deze nu in de juiste "gui container" zetten. We moeten dus precies weten welk type het is!!
		switch(comp->GetType())
		{
		case CT_TEKST:
			addItem(new QGraphicsTekstComp(dynamic_cast<Tekst*>(comp)));
			break;

		case CT_FOTO:
			addItem(new QGraphicsFotoComp(dynamic_cast<Foto*>(comp)));
			break;

		case CT_TITEL:
			addItem(new QGraphicsTitleComp(dynamic_cast<Titel*>(comp)));
			break;
		
		case CT_LIJST:
			addItem(new QGraphicsLijstComp(dynamic_cast<Lijst*>(comp)));
			break;

		case CT_INHOUDSOPGAVE:
			addItem(new QGraphicsInhoudComp(dynamic_cast<InhoudsOpgave*>(comp)));
			break;

		case CT_BOEKINFO:
			addItem(new QGraphicsBoekInfoComp(dynamic_cast<BoekInfo*>(comp)));
			break;

		default:
			qWarning("PubGraphicsScene::render: No support to display this type %d!", comp->GetType());
			break;
		}
	}
}

void PubGraphicsScene::disable()
{
	m_isEnabled = false;

	// Set gray background
	setBackgroundBrush(Qt::lightGray);
	// Removes all items
	clear();
}

void PubGraphicsScene::enable()
{
	m_isEnabled = true;

	// Set gray background to nothing
	setBackgroundBrush(Qt::NoBrush);
}

void PubGraphicsScene::UpdateInfo(Pagina *pagina)
{
	m_pPagina = pagina;

	if(pagina)
	{
		render(pagina);
		enable();
	}
	else
	{
		disable();
	}
}

void PubGraphicsScene::WijzigComponent(Component *comp)
{
	QList<QGraphicsItem*> items = this->items();

	for(QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); ++it)
	{
		QGraphicsItem *item = *it;
		// Alleen componenten die IGraphicsComp implementeren hebben we nodig. In render voegen we alleen componenten
		// toe die deze "interface" implementeren. Helaas hebben deze items soms kinderen die deze interface
		// natuurlijk niet implementeren. Deze kinderen worden gezien als gewone elementen van de scene.
		// Hierdoor zijn er ook items in de scene die IGraphicsScene niet implementeren. We moeten dus eerst
		// m.b.v. RTTI kijken als dit wel een IGraphicsComp is! (Inheritance kan dit probleem niet oplossen
		// aangezien we niets aan QGraphicsItem kunnen veranderen!)
		IGraphicsComp *graphicsComp = dynamic_cast<IGraphicsComp*>(item);
		if(graphicsComp == NULL)
		{
			// Als het er geen is, ga naar de volgende
			continue;
		}

		// Als dit het juiste component is ..
		if(graphicsComp->compare(comp))
		{
			// .. dan open het dialoog om eigenschappen hiervan te editeren ..
			graphicsComp->openEditDialog();
			// .. En ga uit de functie
			return;
		}
	}
}

/*virtual*/ void PubGraphicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
	if(m_isEnabled && event->mimeData()->hasFormat("publisher/new-comp-drag"))
	{
		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

/*virtual*/ void PubGraphicsScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
	if(m_isEnabled && event->mimeData()->hasFormat("publisher/new-comp-drag"))
	{
		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

/*virtual*/ void PubGraphicsScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
	if(event->mimeData()->hasFormat("publisher/new-comp-drag"))
	{
		QByteArray pieceData = event->mimeData()->data("publisher/new-comp-drag");
		QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
         
		QVariant type, arg;
		dataStream >> type >> arg;

		ComponentType compType = (ComponentType)type.toInt();
		createNewComponent(event->scenePos(), compType, arg);

		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

/*virtual*/ void PubGraphicsScene::keyPressEvent(QKeyEvent *keyEvent)
{
	// Save if we're holding shift
	if(keyEvent->key() == Qt::Key_Shift)
	{
		holdingShift = true;
	}
	QGraphicsScene::keyPressEvent(keyEvent);
}

/*virtual*/ void PubGraphicsScene::keyReleaseEvent(QKeyEvent *keyEvent)
{
	// We moeten bijhouden als shift is ingedrukt of niet
	if(keyEvent->key() == Qt::Key_Shift)
	{
		holdingShift = false;
		QGraphicsScene::keyReleaseEvent(keyEvent);
		return;
	}
	// We moeten alleen iets dan als we shift inhouden en op delete drukken, anders niets!
	else if(!holdingShift || keyEvent->key() != Qt::Key_Delete)
	{
		QGraphicsScene::keyReleaseEvent(keyEvent);
		return;
	}

	// We weten nu dat de combinatie SHIFT+DEL is
	// Verwijder dus de geselecteerde componenten
	QList<QGraphicsItem*> lijst = selectedItems();
	for(QList<QGraphicsItem*>::iterator it = lijst.begin(); it != lijst.end(); ++it)
	{
		QGraphicsItem *item = *it;
		// Idem zoals bij wijzigComponent waarom we dynamic_cast nodig hebben!
		IGraphicsComp *graphicsComp = dynamic_cast<IGraphicsComp*>(item);
		if(graphicsComp == NULL)
		{
			// Als het er geen is, ga naar de volgende
			continue;
		}

		Component *toDel = graphicsComp->getComponent();

		m_pPagina->DelComponent(toDel);
	}

	UpdateInfo(m_pPagina);
}

/** Maakt een nieuwe component in zowel de interne pagina als op het QGraphicsScene.
 *  Dit als het resultaat van een drop actie.
 *
 *  Bij het toevoegen van een component dat informatie (kan) weergeven van zijn parent,
 *  zoals BoekInfoComp, InhoudComp en TitleComp maken we eerste een component ZONDER parent aan.
 *  Hiermee maken we dan een QGraphics component aan. Deze MOET dus checken als het wel een parent
 *  heeft, en indien niet eeen standaard text tonen ipv de echte inhoud.
 *  Eens de component is toegevoegd en deze dus een parent heeft, laten we de editor zichzelf refeshen.
 **/
void PubGraphicsScene::createNewComponent(const QPointF &pos, ComponentType type, QVariant &arg)
{
	// Locale variablen
	bool rval = false;
	Component *comp = NULL;
	QGraphicsItem *graphicsItem = NULL;

	switch(type)
	{
	case CT_TEKST:
		rval = addTekstComp(pos.toPoint(), &comp, &graphicsItem);
		break;

	case CT_FOTO:
		rval = addFotoComp(pos.toPoint(), &comp, &graphicsItem);
		break;

	case CT_TITEL:
		rval = addTitelComp(pos.toPoint(), &comp, &graphicsItem, m_pPagina);
		break;
	
	case CT_LIJST:
		rval = addLijstComp(pos.toPoint(), (LijstType)arg.toInt(), &comp, &graphicsItem);
		break;

	case CT_INHOUDSOPGAVE:
		rval = addIHComp(pos.toPoint(), &comp, &graphicsItem, m_pPagina);
		break;

	case CT_BOEKINFO:
		rval = addBoekInfoComp(pos.toPoint(), &comp, &graphicsItem, m_pPagina);
		break;

	default:
		qWarning("PubGraphicsScene::createNewComponent: No support to create this type %d!", type);
		rval = false;
		break;
	}

	// Moet dit component nog aan de lijst toegevoegd of is het al toegevoegd?
	if(rval)
	{
		m_pPagina->AddComponent(comp);
	}

	if(graphicsItem != NULL)
	{
		this->addItem(graphicsItem);
	}
}

bool PubGraphicsScene::addTekstComp(const QPoint pos, Component **comp, QGraphicsItem **item)
{
	// Create internal and GUI object
	Tekst *tekst = new Tekst(pos, QSize(Opties::GetBreedte(), 0), Opties::GetFont(), string("Typ uw tekst hier"));
	QGraphicsTekstComp *graphTekstComp = new QGraphicsTekstComp(tekst);

	// Call edit dialog
	if(graphTekstComp->openEditDialog() == false)
	{
		delete tekst;
		*comp = tekst =  NULL;
		delete graphTekstComp;
		*item = graphTekstComp = NULL;
		return false;
	}

	// Return created pointers
	*comp = tekst;
	*item = graphTekstComp;
	return true;
}

bool PubGraphicsScene::addTitelComp(const QPoint pos, Component **comp, QGraphicsItem **item, Pagina *parent)
{
	// Create internal and GUI object
	Titel *titel = new Titel(pos, QSize(), Opties::GetFont(), NULL, string("Titel"), false);
	parent->AddComponent(titel);
	QGraphicsTitleComp *graphTitleComp = new QGraphicsTitleComp(titel);

	// Call edit dialog
	if(graphTitleComp->openEditDialog() == false)
	{
		// Component geheugen wordt door deze functie automatisch vrijgegeven
		parent->DelComponent(titel);
		*comp = titel =  NULL;
		delete graphTitleComp;
		*item = graphTitleComp = NULL;
		return false;
	}

	// Return created pointers
	*comp = titel;
	*item = graphTitleComp;
	return false;
}

bool PubGraphicsScene::addFotoComp(const QPoint pos, Component **comp, QGraphicsItem **item)
{
	// Create internal and GUI object
	Foto *foto = new Foto(pos, QSize(), Opties::GetFont(), string(":/images/Resources/foto.png"), string("Een foto"));
	QGraphicsFotoComp *graphFotoComp = new QGraphicsFotoComp(foto);

	// Call edit dialog
	if(graphFotoComp->openEditDialog() == false)
	{
		delete foto;
		*comp = foto =  NULL;
		delete graphFotoComp;
		*item = graphFotoComp = NULL;
		return false;
	}

	// Return created pointers
	*comp = foto;
	*item = graphFotoComp;
	return true;
}

bool PubGraphicsScene::addLijstComp(const QPoint pos, LijstType type, Component **comp, QGraphicsItem **item)
{
	// Create internal and GUI object
	Lijst *lijst = new Lijst(pos, QSize(Opties::GetBreedte(), 0), Opties::GetFont());
	lijst->SetLijstType(type);
	lijst->AddItem(string("Item 1"));
	QGraphicsLijstComp *graphLijstComp = new QGraphicsLijstComp(lijst);

	// Call edit dialog
	if(graphLijstComp->openEditDialog() == false)
	{
		delete lijst;
		*comp = lijst =  NULL;
		delete graphLijstComp;
		*item = graphLijstComp = NULL;
		return false;
	}

	// Return created pointers
	*comp = lijst;
	*item = graphLijstComp;
	return true;
}

bool PubGraphicsScene::addIHComp(const QPoint pos, Component **comp, QGraphicsItem **item, Pagina *parent)
{
	// Create internal and GUI object
	InhoudsOpgave *ih = new InhoudsOpgave(pos, QSize(Opties::GetBreedte(), 0), Opties::GetFont());
	parent->AddComponent(ih);
	QGraphicsInhoudComp *graphInhoudComp = new QGraphicsInhoudComp(ih);

	// Call edit dialog
	if(graphInhoudComp->openEditDialog() == false)
	{
		// Component geheugen wordt door deze functie automatisch vrijgegeven
		parent->DelComponent(ih);
		*comp = ih =  NULL;
		delete graphInhoudComp;
		*item = graphInhoudComp = NULL;
		return false;
	}

	// Return created pointers
	*comp = ih;
	*item = graphInhoudComp;
	// Geef false terug, want component is automatisch al toegevoegd!
	return false;
}

bool PubGraphicsScene::addBoekInfoComp(const QPoint pos, Component **comp, QGraphicsItem **item, Pagina *parent)
{
	// Create internal and GUI object
	BoekInfo *info = new BoekInfo(pos, QSize(Opties::GetBreedte(), 0), Opties::GetFont());
	parent->AddComponent(info);
	QGraphicsBoekInfoComp *graphInfoComp = new QGraphicsBoekInfoComp(info);

	// Call edit dialog
	if(graphInfoComp->openEditDialog() == false)
	{
		// Component geheugen wordt door deze functie automatisch vrijgegeven
		parent->DelComponent(info);
		*comp = info =  NULL;
		delete graphInfoComp;
		*item = graphInfoComp = NULL;
		return false;
	}

	// Return created pointers
	*comp = info;
	*item = graphInfoComp;
	// Geef false terug, want component is automatisch al toegevoegd!
	return false;
}