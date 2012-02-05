// Mathy Vanhoef
#ifndef QDIALOGDEELPROPERTIES_H_
#define QDIALOGDEELPROPERTIES_H_

#include <QtGui/QDialog>
#include <QtGui/QLineEdit>

/**
 *	Dialog om eigenschappen van een Deel te veranderen
 */
class QDialogDeelProperties : public QDialog
{
public:
	QDialogDeelProperties(QWidget *parent = 0, Qt::WindowFlags f = 0);
	QString GetTitel() const { return m_pTitel->text(); }
	void SetTitel(const QString titel) { m_pTitel->setText(titel); }


private:
	QLineEdit *m_pTitel;
};

#endif // QDIALOGDEELPROPERTIES_H_