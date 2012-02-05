#include <QtGui/QGraphicsView>
#include <QtGui/QListView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QListWidgetItem>
#include <QtGui/QPixMap>
#include <QtGui/QGraphicsTextItem>
#include <QtGui/QGraphicsScene>

#include "Editor.h"
#include "ComponentList.h"
#include "PubGraphicsScene.h"
#include "QGraphicsTitleComp.h"
#include "QGraphicsTekstComp.h"
#include "Pagina.h"

Editor::Editor(QWidget *parent) : QWidget(parent), m_pPagina(NULL)
{
	//
	// 1 - Component lijst
	//
	m_pComp = new ComponentList();
	m_pComp->setMinimumHeight(65);
	m_pComp->setMaximumHeight(65);
	m_pComp->setMinimumWidth(420);
	m_pComp->setEnabled(false);

	//
	// 2 - Graphics view
	//

	m_pScene = new PubGraphicsScene(this);

	m_pView = new QGraphicsView(m_pScene);
	m_pView->setMinimumHeight(560);

	QVBoxLayout *vbox = new QVBoxLayout();
	vbox->addWidget(m_pComp, 0);
	vbox->addWidget(m_pView, 10);

	m_pView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

	setLayout(vbox);

	//
	// 3 - Signals en slots
	//
	connect(m_pScene, SIGNAL(changed(const QList<QRectF>&)), this, SLOT(infoHasChangedStub(const QList<QRectF>&)));
}

/*private slot*/ void Editor::infoHasChangedStub(const QList<QRectF>&)
{
	emit InfoHasChanged(m_pPagina);
}

/*public slot*/ void Editor::UpdateInfo(Pagina *pagina)
{
	m_pPagina = pagina;

	if(pagina)
	{
		m_pComp->setEnabled(true);
		m_pScene->UpdateInfo(pagina);
	}
	else
	{
		// Specificatie: bij NULL argument wordt het widget disabled.
		// Automatisch is dan ook drag en drop disabled!
		m_pComp->setEnabled(false);

		// 2 - Disable de echte editor
		m_pScene->UpdateInfo(NULL);
	}
}

void Editor::WijzigComponent(Component *comp)
{
	// forward to scene
	m_pScene->WijzigComponent(comp);
}

Pagina * Editor::GetPaginaEditing() const
{
	if(isEnabled())
	{
		return m_pPagina;
	}
	else
	{
		return NULL;
	}
}