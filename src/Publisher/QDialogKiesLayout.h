#ifndef QDIALOGKIESLAYOUT_H_
#define QDIALOGKIESLAYOUT_H_

#include <QtGui/QDialog>

class Boek;
class QComboBox;
class Pagina;

/**
 *	Dialoog voor het selecteren van een layout
 */
class QDialogKiesLayout : public QDialog
{
	Q_OBJECT


public:
	QDialogKiesLayout(Boek *layouts, QWidget *parent = 0, Qt::WindowFlags f = 0);
	/**
	 *  Geeft de geselecteerde layout terug (geen kopie van de pointer maar een gewone pagina pointer)
	 */
	Pagina * getSelectedLayout() const;


private:
	Boek *m_pLayouts;
	QComboBox *m_pCmbLayout;
	/**
	 *	Maakt alle widgets aan die worden getoond in het dialoog
	 */
	void createWidgets();
	/**
	 *	Cleart en vult daarna de combobox met alle layouts
	 */
	void fillComboBox();
};

#endif // QDIALOGKIESLAYOUT_H_