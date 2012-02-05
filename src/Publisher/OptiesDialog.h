// Mathy Vanhoef
#ifndef OPTIESDIALOG_H_
#define OPTIESDIALOG_H_

#include <QtGui/QDialog>
#include <QtGui/QSpinBox>

class QLabel;

/**
 *	Dialoog om de instellingen te veranderen
 */
class OptiesDialog : public QDialog
{
	Q_OBJECT


public:
	OptiesDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);
	void SetFont(const QFont &font);
	QFont GetFont() const { return m_font; }
	void SetBreedte(int breedte) { m_pSpinBreedte->setValue(breedte); }
	int GetBreedte() const { return m_pSpinBreedte->value(); }


private:
	QLabel *m_pLblFont;
	QFont m_font;
	QSpinBox *m_pSpinBreedte;
private slots:
	/**
	 *	Slot om te reageren als de gebruiker op wijzig lettertype heeft geklikt
	 */
	void getNewFont();
};

#endif // OPTIESDIALOG_H_