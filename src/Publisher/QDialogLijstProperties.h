// Mathy Vanhoef
#ifndef QDIALOGLIJSTPROPERTIES_H_
#define QDIALOGLIJSTPROPERTIES_H_

#include "QDialogProperties.h"
#include "lijst.h"

class QComboBox;
class QPlainTextEdit;

/**
 *  Dialoog voor het instellen van de eigenschappen van een Lijst Component
 */
class QDialogLijstProperties : public QDialogProperties
{
protected:
	QComboBox *m_pLijstType;
	QPlainTextEdit *m_pItems;

public:
	QDialogLijstProperties(QWidget *parent = 0, Qt::WindowFlags f = 0);
	LijstType GetLijstType() const;
	void SetLijstType(LijstType type);
	list<string> GetItems() const;
	void SetItems(const QString &items);

private:
	/**
	 *  Maak de tab aan met properties specifiek aan het Lijst Component
	 */
	QWidget * createLijstProperties();
};

#endif // QDIALOGLIJSTPROPERTIES_H_