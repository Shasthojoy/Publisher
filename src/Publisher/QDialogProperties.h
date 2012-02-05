// Mathy Vanhoef
#ifndef QDIALOGPROPERTIES_H_
#define QDIALOGPROPERTIES_H_

#include <QtGui/QDialog>

class QGroupBox;
class QSpinBox;
class QLabel;
class QTabWidget;

/**
 *  Basis klasse voor een dialoog voor het instelling van de eigenschappen van een component
 */
class QDialogProperties : public QDialog
{
	Q_OBJECT


public:
	QDialogProperties(QWidget *parent = 0, Qt::WindowFlags f = 0);
	/**
	 *  Disabled de spinbox voor het instellen van de hoogte van een component.
	 *	(Het komt veel voor dat men de hoogte van een component niet kan instellen!)
	 */
	void disableHoogte();
	void SetPos(const QPoint &pos);
	void SetSize(const QSize &size);
	void SetFont(const QFont &font);
	QPoint GetPos() const;
	QSize GetSize() const;
	QFont GetFont() const;


protected:
	QSpinBox *m_pSpinX, *m_pSpinY, *m_pSpinHoogte, *m_pSpinBreedte;
	QLabel *m_pLblFont;
	QFont m_font;
	QTabWidget *m_pTab;
protected slots:
	/**
	 *  Slot gebruikt voor het reageren als de gebruiker op de Push Button klikt om
	 *  een nieuw font in te stellen.
	 */
	void getNewFont();


private:
	/**
	 *  Maakt een groupbox aan met een titel. Hierin zet het twee spinboxes met daarvoor twee labels
	 *  de de spinboxen beschrijven.
	 *	@param	spinBoxEen		Eerste spinbox die wordt gemaakt
	 *	@param	spinBoxTwee		Tweede spinbox die wordt gemaakt
	 *	@param	titel			Titel van de groupbox
	 *	@param	naamEen			Beschrijving van dee eerste spinbox
	 *	@param	naamTwee		Beschrijving van de tweede spinbox
	 */
	QGroupBox * createDefaultPropertiesBox(QSpinBox * &spinBoxEen, QSpinBox * &spinBoxTwee,
		const char *titel, const char *naamEen, const char *naamTwee);
	/**
	 *  Maak de tab aan met de algemene properties van elk component
	 */
	QWidget * createDefaultProperties();
};

#endif // QDIALOGPROPERTIES_H_