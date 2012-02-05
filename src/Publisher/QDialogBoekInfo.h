// Robin Timmermans
#ifndef QDIALOGBOEKINFO_H_
#define QDIALOGBOEKINFO_H_

#include <string>
#include <list>
using namespace std;

#include <QtGui/QDialog>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtGui/QGroupBox>
#include <QtGui/QLineEdit>
#include <QtGui/QSpinBox>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QTextDocument>
#include <QtGui/QTextBlock>
#include "boekinformatie.h"


class QDialogBoekInfo : public QDialog
{
private:
	QLineEdit *m_pTitel;
	QPlainTextEdit *m_pAuteurs;
	QLineEdit *m_pVersie;
	QLineEdit *m_pNaamUitgeverij;
	QLineEdit *m_pAdresUitgeverij;
	QLineEdit *m_pIsbn;
	QLineEdit *m_pEditie;
	QSpinBox *m_pJaar;
	QSpinBox *m_pHoogte;
	QSpinBox *m_pBreedte;


public:
	QDialogBoekInfo(QWidget *parent = 0, Qt::WindowFlags f = 0);
	QString GetNaamUitgeverij()const {return m_pNaamUitgeverij->text();}
	void SetNaamUitgeverij(const QString naam){m_pNaamUitgeverij->setText(naam);}
	QString GetAdresUitgeverij()const {return m_pAdresUitgeverij->text();}
	void SetAdresUitgeverij(const QString adres){m_pAdresUitgeverij->setText(adres);}
	QString GetIsbn()const{return m_pIsbn->text();}
	void SetIsbn(const QString isbn){m_pIsbn->setText(isbn);}
	int GetJaarDruk()const{return m_pJaar->value();}
	void SetJaarDruk(int jaar){m_pJaar->setValue(jaar);}
	int GetHoogte()const{return m_pHoogte->value();}
	void SetHoogte(int hoogte){m_pHoogte->setValue(hoogte);}
	int GetBreedte(){return m_pBreedte->value();}
	void SetBreedte(int breedte){m_pBreedte->setValue(breedte);}
	QString GetEditie()const {return m_pEditie->text();}
	void SetEditie(const QString editie) {m_pEditie->setText(editie);}
	QString GetVersie()const {return m_pVersie->text();}
	void SetVersie(const QString versie) {m_pVersie->setText(versie);}
	QString GetTitel()const {return m_pTitel->text();}
	void SetTitel(const QString titel){m_pTitel->setText(titel);}
	list<string> GetAuteurs();
	void SetAuteurs(list<string> auteurs);
	void SetBoekInfo(BoekInformatie & info);
	//de functie getboekinfo krijgt een pointer doel mee want anders
	//moet er teveel worden gereturnd
	void GetBoekInfo(BoekInformatie * doel);
	
};

#endif // QDIALOGBOEKINFO_H_