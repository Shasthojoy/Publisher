#include <assert.h>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>

#include "ProjectManager.h"
#include "HierarchieManager.h"
#include "ComponentManager.h"
#include "LayoutManager.h"
#include "Editor.h"
#include "Boek.h"
#include "xmlFile.h"
#include "QDialogBoekInfo.h"

ProjectManager::ProjectManager(HierarchieManager *hierarchie, ComponentManager *component, Editor *editor)
	 : m_pBoek(NULL), m_pHierManager(hierarchie), m_pCompManager(component), m_pEditor(editor), m_pPagina(NULL)
{
	assert(m_pHierManager != NULL);
	assert(m_pCompManager != NULL);
	assert(m_pEditor != NULL);
	// Hierarchie, Component en editor zouden standaard (bij aanmaken van het object) als standaard
	// gedisabled moeten zijn, dus dat hoeven we hier niet te doen!

	// Connect editor and component manager
	connect(m_pEditor, SIGNAL(InfoHasChanged(Pagina*)), m_pCompManager, SLOT(UpdateInfo(Pagina*)));
	connect(m_pCompManager, SIGNAL(InfoHasChanged(Pagina*)), m_pEditor, SLOT(UpdateInfo(Pagina*)));
	connect(m_pCompManager, SIGNAL(ReqWijzigComponent(Component*)), m_pEditor, SLOT(WijzigComponent(Component*)));
	// Connect hierarchiemanager to projectmanager. Projectmanager will forward information to editor and
	// component manager via helper funtions
	connect(m_pHierManager, SIGNAL(ReqOpenPagina(Pagina*)), this, SLOT(UpdatePaginaInfo(Pagina*)));
	connect(m_pHierManager, SIGNAL(ReqRefreshPagina()), this, SLOT(RefreshPagina()));
	connect(m_pHierManager, SIGNAL(willDeletePagina(Pagina *)), this, SLOT(warnDeletionPagina(Pagina*)));
	connect(m_pHierManager, SIGNAL(willDeleteDeel(Deel*)), this, SLOT(warnDeletionDeel(Deel*)));
}

ProjectManager::~ProjectManager()
{
	m_pHierManager->UpdateInfo(NULL);
	m_pCompManager->UpdateInfo(NULL);
	m_pEditor->UpdateInfo(NULL);
	delete m_pBoek;
}

void ProjectManager::NewProject()
{
	//
	// Step 1 - Show dialog
	//
	Boek *oudBoek = m_pBoek;
	m_pBoek = new Boek();
	if(!EditBoekInfo())
	{
		delete m_pBoek;
		m_pBoek = oudBoek;
		return;
	}

	delete oudBoek;
	oudBoek = NULL;

	//
	// Step 3 - show it!
	//
	UpdateBoekInfo(m_pBoek);
	UpdatePaginaInfo(NULL);
}

bool ProjectManager::EditBoekInfo()
{
	if(m_pBoek == NULL)
	{
		QMessageBox box(QMessageBox::Information, "Geen project", "Er is geen project geopend!");
		box.exec();
		return false;
	}

	QDialogBoekInfo dialog;
	dialog.SetBoekInfo(m_pBoek->GetBoekInfo());

	if(dialog.exec())
	{
		BoekInformatie *info = new BoekInformatie();
		dialog.GetBoekInfo(info);
		m_pBoek->SetBoekInfo(*info);
		delete info;

		RefreshPagina();
		return true;
	}
	return false;
}

void ProjectManager::OpenProject()
{
	QFileDialog fileDialog;
	fileDialog.setFileMode(QFileDialog::ExistingFile);

	if(fileDialog.exec())
	{
		QStringList files = fileDialog.selectedFiles();
		if(files.size() >= 1)
		{
			m_saveLocation = files.first();
			open(m_saveLocation);
		}
		else
		{
			qWarning("No files selected in QFileDialog but user still managed to click open?");
		}
	}
}

void ProjectManager::SaveProject()
{
	if(m_pBoek == NULL)
	{
		QMessageBox box(QMessageBox::Information, "Geen project", "Er is geen project geopend!");
		box.exec();
		return;
	}

	if(m_saveLocation.isEmpty())
	{
		SaveProjectAs();
	}
	else
	{
		// TODO: Is het inderdaad opgeslagen?
		save(m_saveLocation);
	}
}

void ProjectManager::SaveProjectAs()
{
	if(m_pBoek == NULL)
	{
		QMessageBox box(QMessageBox::Information, "Geen project", "Er is geen project geopend!");
		box.exec();
		return;
	}

	QFileDialog fileDialog;
	fileDialog.setFileMode(QFileDialog::AnyFile);
	fileDialog.setAcceptMode(QFileDialog::AcceptSave);

	if(fileDialog.exec())
	{
		QStringList files = fileDialog.selectedFiles();
		if(files.size() >= 1)
		{
			m_saveLocation = files.first();
			save(m_saveLocation);
		}
		else
		{
			qWarning("No files selected in QFileDialog but user still managed to click save?");
		}
	}
}

void ProjectManager::save(QString location)
{
	xmlboek::opslaan(m_pBoek, location);
}

void ProjectManager::open(QString location)
{
	Boek *boek = xmlboek::openen(location);
	if(boek == NULL)
	{
		QMessageBox box(QMessageBox::Information, "Openen Project", "Fout bij het openen van het project");
		box.exec();
		return;
	}

	delete m_pBoek;
	m_pBoek = boek;

	UpdateNewBoek();
}

void ProjectManager::CloseProject()
{
	delete m_pBoek;
	m_pBoek = NULL;

	UpdatePaginaInfo(NULL);
	UpdateBoekInfo(NULL);
}

void ProjectManager::UpdatePaginaInfo(Pagina *pagina)
{
	m_pPagina = pagina;
	m_pCompManager->UpdateInfo(pagina);
	m_pEditor->UpdateInfo(pagina);
}

void ProjectManager::UpdateBoekInfo(Boek *boek)
{
	m_pHierManager->UpdateInfo(boek);
}

void ProjectManager::UpdateNewBoek()
{
	UpdateBoekInfo(m_pBoek);
	if(m_pBoek->AantalDelen() > 0)
	{
		Deel *deel = m_pBoek->GetDeel(0);
		if(deel->AantalPaginas() > 0)
		{
			UpdatePaginaInfo(deel->GetPagina(0));
		}
	}
}

void ProjectManager::RefreshPagina()
{
	if(m_pPagina != NULL)
	{
		UpdatePaginaInfo(m_pPagina);
	}
}

void ProjectManager::warnDeletionPagina(Pagina *pagina)
{
	if(pagina != NULL && pagina == m_pPagina)
	{
		UpdatePaginaInfo(NULL);
	}
}

void ProjectManager::warnDeletionDeel(Deel *deel)
{
	if(deel != NULL && m_pPagina != NULL && deel == m_pPagina->GetParent())
	{
		UpdatePaginaInfo(NULL);
	}
}