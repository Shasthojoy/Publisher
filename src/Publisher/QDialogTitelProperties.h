// Mathy Vanhoef
#ifndef QDIALOGTITELPROPERTIES_H_
#define QDIALOGTITELPROPERTIES_H_

#include "QDialogProperties.h"

class QLineEdit;
class QCheckBox;

/**
 *  Dialoog voor het instellen van de eigenschappen van een Titel Component
 */
class QDialogTitelProperties : public QDialogProperties
{
	Q_OBJECT


public:
	QDialogTitelProperties(QWidget *parent = 0, Qt::WindowFlags f = 0);
	QString GetTitel() const;
	bool GetDeelTitel() const;
	void SetTitel(const QString &titel);
	void SetDeelTitel(bool isDeelTitel);


protected:
	QCheckBox *m_pDeelTitel;
	QLineEdit *m_pTitel;
protected slots:
	/**
	 *  Slot die de titel disabled als state true is, en anders titen enabled.
	 */
	void setCheckboxState(bool state);


private:
	/**
	 *  Maak de tab aan met properties specifiek aan het Titel Component
	 */
	QWidget * createTitelProperties();
};

#endif // QDIALOGTITELPROPERTIES_H_