// Mathy Vanhoef
#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QtGui/QMainWindow>

class QAction;
class ProjectManager;
class HierarchieManager;
class ComponentManager;
class LayoutManager;
class Editor;

/**
 * Het hoofdscherm van Publisher
 */
class MainWindow : public QMainWindow
{
	Q_OBJECT


public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();


private:
	// Project manager
	ProjectManager *m_pManager;
	// Actions
	QAction *m_aNewProject;
	QAction *m_aOpenProject;
	QAction *m_aSaveProject;
	QAction *m_aSaveProjectAs;
	QAction *m_aCloseProject;
	QAction *m_aQuit;
	QAction *m_aInstellingen;
	QAction *m_aAddLayout;
	QAction *m_aManageLayouts;
	QAction *m_aBoekInfo;
	QAction *m_aAbout;
	// Important widgets
	HierarchieManager *m_pHierManager;
	ComponentManager *m_pCompManager;
	Editor *m_pEditor;
	LayoutManager *m_pLayoutManager;
	void createActions();
	void createMenu();
	void createToolbar();
	QWidget * createBody();
private slots:
	void quit();
	void about() const;
	void instellingen();
	void nieuweLayout();
};

#endif // MAINWINDOW_H_