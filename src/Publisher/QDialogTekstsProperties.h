// Mathy Vanhoef
#ifndef QDIALOGTEKSTSPROPERTIES_H_
#define QDIALOGTEKSTSPROPERTIES_H_

#include "QDialogProperties.h"

class QPlainTextEdit;

/**
 *  Dialoog voor het instellen van de eigenschappen van een Tekst Component
 */
class QDialogTekstsProperties : public QDialogProperties
{
public:
	QDialogTekstsProperties(QWidget *parent = 0, Qt::WindowFlags f = 0);
	QString GetText() const;
	void SetText(const QString text);


protected:
	QPlainTextEdit *m_pTextEdit;


private:
	/**
	 *  Maak de tab aan met properties specifiek aan het Tekst Component
	 */
	QWidget * createTekstsProperties();
};

#endif // QDIALOGTEKSTSPROPERTIES_H_