// Mathy Vanhoef
#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QtGui/QStatusBar>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QListView>
#include <QtGui/QToolBar>
#include <QtGui/QPixmap>
#include <QtGui/QMessageBox>

#include "MainWindow.h"
#include "HierarchieManager.h"
#include "ComponentManager.h"
#include "Editor.h"
#include "LayoutManager.h"
#include "ProjectManager.h"
#include "Opties.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	// Create menu and actions
	createActions();
	createMenu();
	createToolbar();

	// Create Body
	setCentralWidget(createBody());

	// Start LayoutManager
	m_pLayoutManager = new LayoutManager();
	connect(m_aManageLayouts, SIGNAL(triggered()), m_pLayoutManager, SLOT(BeheerLayouts()));
	m_pHierManager->SetLayoutManager(m_pLayoutManager);

	// Start ProjectManager to manipulate complete projects.
	// It controls the Component and Hierarchie widgets, and the editor widget!
	m_pManager = new ProjectManager(m_pHierManager, m_pCompManager, m_pEditor);
	connect(m_aNewProject, SIGNAL(triggered()), m_pManager, SLOT(NewProject()));
	connect(m_aOpenProject, SIGNAL(triggered()), m_pManager, SLOT(OpenProject()));
	connect(m_aSaveProject, SIGNAL(triggered()), m_pManager, SLOT(SaveProject()));
	connect(m_aSaveProjectAs, SIGNAL(triggered()), m_pManager, SLOT(SaveProjectAs()));
	connect(m_aCloseProject, SIGNAL(triggered()), m_pManager, SLOT(CloseProject()));
	connect(m_aBoekInfo, SIGNAL(triggered()), m_pManager, SLOT(EditBoekInfo()));
	connect(m_aCloseProject, SIGNAL(triggered()), m_pManager, SLOT(CloseProject()));

	statusBar()->showMessage("Publisher started");
}

MainWindow::~MainWindow()
{
	delete m_pManager;
	m_pManager = NULL;
	delete m_pLayoutManager;
	m_pLayoutManager = NULL;
}

void MainWindow::createToolbar()
{
	QToolBar *toolBar = addToolBar("Toolbar");
	toolBar->addAction(m_aNewProject);
	toolBar->addAction(m_aOpenProject);
	toolBar->addAction(m_aSaveProject);
}

QWidget * MainWindow::createBody()
{
	QWidget *container = new QWidget();

	QVBoxLayout *layout = new QVBoxLayout();
	m_pHierManager = new HierarchieManager();
	layout->addWidget(m_pHierManager);
	m_pCompManager = new ComponentManager();
	layout->addWidget(m_pCompManager);

	QHBoxLayout *main = new QHBoxLayout();
	main->addLayout(layout, 0);
	m_pEditor = new Editor();
	main->addWidget(m_pEditor, 10);

	container->setLayout(main);
	return container;
}

void MainWindow::createActions()
{
	//
	// File
	//

	m_aNewProject = new QAction("&Nieuw Project", this);
	m_aNewProject->setShortcut(QKeySequence::New);
	m_aNewProject->setStatusTip("Maak een nieuw project");
	m_aNewProject->setIcon(QIcon(":/images/Resources/new.png"));

	m_aOpenProject = new QAction("&Project Openen", this);
	m_aOpenProject->setShortcut(QKeySequence::Open);
	m_aOpenProject->setStatusTip("Open een bestaand project");
	m_aOpenProject->setIcon(QIcon(":/images/Resources/open.png"));

	m_aSaveProject = new QAction("&Project Opslaan", this);
	m_aSaveProject->setShortcut(QKeySequence::Save);
	m_aSaveProject->setStatusTip("Sla het huidige project op");
	m_aSaveProject->setIcon(QIcon(":/images/Resources/opslaan.png"));

	m_aSaveProjectAs = new QAction("&Project Opslaan Als", this);
	m_aSaveProjectAs->setStatusTip("Sla het huidige project op onder een nieuwe naam");

	m_aCloseProject = new QAction("&Sluit Project", this);
	m_aCloseProject->setStatusTip("Sluit het huidige project af");

	m_aQuit = new QAction("&Afsluiten", this);
	m_aQuit->setStatusTip("Sluit publisher af");
	m_aQuit->setIcon(QIcon(":/images/Resources/quit.png"));
	connect(m_aQuit, SIGNAL(triggered()), this, SLOT(quit()));

	//
	// Layout
	//

	m_aAddLayout = new QAction("Nieuwe Layout", this);
	m_aAddLayout->setStatusTip("Maak een layout gebaseerd op de huidige pagina");
	connect(m_aAddLayout, SIGNAL(triggered()), this, SLOT(nieuweLayout()));

	m_aManageLayouts = new QAction("Beheer Layouts", this);
	m_aManageLayouts->setStatusTip("Overzicht van alle layouts");

	//
	// Tools
	//
	
	m_aInstellingen = new QAction("&Instellingen", this);
	m_aInstellingen->setStatusTip("Verander algemene instellingen en opties van de publisher");
	connect(m_aInstellingen, SIGNAL(triggered()), this, SLOT(instellingen()));

	m_aBoekInfo = new QAction("&Boek Informatie", this);
	m_aBoekInfo->setStatusTip("Wijzig informatie van het boek");

	//
	// Help
	//

	m_aAbout = new QAction("&About", this);
	m_aAbout->setStatusTip("About Publisher");
	connect(m_aAbout, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenu()
{
	QMenu *fileMenu = menuBar()->addMenu("&File");
	fileMenu->addAction(m_aNewProject);
	fileMenu->addAction(m_aOpenProject);
	fileMenu->addSeparator();
	fileMenu->addAction(m_aSaveProject);
	fileMenu->addAction(m_aSaveProjectAs);
	fileMenu->addAction(m_aCloseProject);
	fileMenu->addSeparator();
	fileMenu->addAction(m_aQuit);

	QMenu *toolsMenu = menuBar()->addMenu("&Tools");
	toolsMenu->addAction(m_aInstellingen);
	toolsMenu->addSeparator();
	toolsMenu->addAction(m_aBoekInfo);
	
	QMenu *layoutMenu = menuBar()->addMenu("&Layout");
	layoutMenu->addAction(m_aAddLayout);
	layoutMenu->addAction(m_aManageLayouts);

	QMenu *helpMenu = menuBar()->addMenu("&Help");
	helpMenu->addAction(m_aAbout);
}

void MainWindow::quit()
{
	// TODO: Are you sure?

	this->close();
}

void MainWindow::about() const
{
	QMessageBox message(QMessageBox::Information, "About Publisher",
		"Made by:\n"
		"\n"
		"Mathy Vanhoef\n"
		"Robin Timmermans");
	message.exec();
}

void MainWindow::instellingen()
{
	Opties::OpenOptiesDialog();
}

void MainWindow::nieuweLayout()
{
	Pagina *currEditing = m_pEditor->GetPaginaEditing();

	if(currEditing == NULL)
	{
		QMessageBox message(QMessageBox::Information, "Geen pagina open","Er moet een pagina geopend zijn in de editor om hiervan een layout te kunnen maken!");
		message.exec();
		return;
	}

	m_pLayoutManager->MaakLayout(currEditing);
}