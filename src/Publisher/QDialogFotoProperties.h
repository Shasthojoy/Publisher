// Mathy Vanhoef
#ifndef QDIALOGFOTOPROPERTIES_H_
#define QDIALOGFOTOPROPERTIES_H_

#include "QDialogProperties.h"

class QLineEdit;

/**
 *  Dialoog voor het instellen van de eigenschappen van een Foto Component
 */
class QDialogFotoProperties : public QDialogProperties
{
	Q_OBJECT


public:
	QDialogFotoProperties(QWidget *parent = 0, Qt::WindowFlags f = 0);
	void SetLocatie(const QString &loc);
	void SetBeschrijving(const QString &beschr);
	QString GetLocatie() const;
	QString GetBeschrijving() const;


protected:
	/**
	 *  Maak de tab aan met properties specifiek aan het Foto Component
	 */
	QWidget * createFotoProperties();
protected slots:
	/**
	 *  Slot gebruikt voor het reageren als de gebruiker op de Push Button klikt om een nieuwe
	 *  afbeelding te laden.
	 */
	void getNewLocation();


private:
	QLineEdit *m_pLocatie;
	QLineEdit *m_pBeschr;
};

#endif // QDIALOGFOTOPROPERTIES_H_