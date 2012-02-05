#ifndef QDIALOGBEHEERLAYOUTS_H_
#define QDIALOGBEHEERLAYOUTS_H_

#include <QtGui/QDialog>

class Boek;
class QPushButton;
class QListWidget;

/**
 *	Dialoog voor het verwijderen van layouts, en voor het veranderen van het eigenschappen van layouts.
 */
class QDialogBeheerLayouts : public QDialog
{
	Q_OBJECT


public:
	QDialogBeheerLayouts(Boek *layouts, QWidget *parent = 0, Qt::WindowFlags f = 0);


private:
	Boek *m_pLayouts;
	QListWidget *m_pListLayout;
	QPushButton *m_pBtnVerwijder;
	QPushButton *m_pBtnWijzig;
	/**
	 *	Maakt alle widgets aan die worden getoond in het dialoog
	 */
	void createWidgets();
	/**
	 *	Cleart en vult daarna de lijst met alle layouts
	 */
	void fillList();
	/** 
	 *	Geeft true terug als een item is geselecteerd. Het geselecteerd item is dan opgeslagen
	 *	in het out argument
	 *	@param	index	[out] index dat is geselecteerd
	 */
	bool getSelectedIndex(int *index) const;
private slots:
	/**
	 *	Slot voor te reageren als de gebruiker op Verwijder heeft geklikt
	 */
	void verwijderLayout();
	/**
	 *	Slot voor te reageren als de gebruiker op Wijzig heeft geklikt
	 */
	void wijzigLayout();
};

#endif // QDIALOGBEHEERLAYOUTS_H_