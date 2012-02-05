#include "QDialogBoekInfo.h"

QDialogBoekInfo::QDialogBoekInfo(QWidget *parent /*= 0*/, Qt::WindowFlags f /*= 0*/) : QDialog(parent, f)
{
	QVBoxLayout *hoofdlayout = new QVBoxLayout();
	QGroupBox *boxProp = new QGroupBox("boek properties");
	QVBoxLayout *Proplayout = new QVBoxLayout(boxProp);

	//titel
	m_pTitel = new QLineEdit();
	QHBoxLayout *TitelLayout = new QHBoxLayout();
	QHBoxLayout *Titelsublayout = new QHBoxLayout();
	QLabel *titel = new QLabel("titel:");
	Titelsublayout->addWidget(titel);
	Titelsublayout->addWidget(m_pTitel);
	TitelLayout->addLayout(Titelsublayout);
	
	
	
	//auteurs
	m_pAuteurs = new QPlainTextEdit();
	QHBoxLayout *AuteursLayout = new QHBoxLayout();
	QHBoxLayout *Auteurssublayout = new QHBoxLayout();
	QLabel *auteurs = new QLabel("auteurs:");
	Auteurssublayout->addWidget(auteurs);
	Auteurssublayout->addWidget(m_pAuteurs);
	AuteursLayout->addLayout(Auteurssublayout);
	
	
	//versie
	m_pVersie = new QLineEdit();
	QHBoxLayout *VersieLayout = new QHBoxLayout();
	QHBoxLayout *Versiesublayout = new QHBoxLayout();
	QLabel *versie = new QLabel("versie:");
	Versiesublayout->addWidget(versie);
	Versiesublayout->addWidget(m_pVersie);
	VersieLayout->addLayout(Versiesublayout);
	

	//boeksize
	m_pHoogte = new QSpinBox;
	m_pBreedte = new QSpinBox;
	m_pHoogte->setRange(100,1000);
	m_pBreedte->setRange(100,1000);
	QGroupBox *BoekSizeLayout = new QGroupBox("boekgrootte");
	QHBoxLayout *BoekSizesublayout = new QHBoxLayout(BoekSizeLayout);
	QLabel *hoogte = new QLabel("hoogte:");
	QLabel *breedte = new QLabel("breedte:");
	BoekSizesublayout->addWidget(hoogte);
	BoekSizesublayout->addWidget(m_pHoogte);
	BoekSizesublayout->addWidget(breedte);
	BoekSizesublayout->addWidget(m_pBreedte);


	//uitgeverij  vertikaal
	m_pNaamUitgeverij = new QLineEdit();
	m_pAdresUitgeverij = new QLineEdit();
	QGroupBox *UitgeverijLayout = new QGroupBox("Uitgeverij:");
	QHBoxLayout *Uitgeverijsublayout = new QHBoxLayout(UitgeverijLayout);
	QLabel *adres = new QLabel("adres:");
	QLabel *naam = new QLabel("naam:");
	Uitgeverijsublayout->addWidget(naam);
	Uitgeverijsublayout->addWidget(m_pNaamUitgeverij);
	Uitgeverijsublayout->addWidget(adres);
	Uitgeverijsublayout->addWidget(m_pAdresUitgeverij);
	

	//isbn
	m_pIsbn = new QLineEdit();
	QHBoxLayout *IsbnLayout = new QHBoxLayout();
	QHBoxLayout *Isbnsublayout = new QHBoxLayout();
	QLabel *isbn = new QLabel("isbn:");
	Isbnsublayout->addWidget(isbn);
	Isbnsublayout->addWidget(m_pIsbn);
	IsbnLayout->addLayout(Isbnsublayout);
	

	//jaardruk
	m_pJaar = new QSpinBox();
	m_pJaar->setRange(0,3000);
	QHBoxLayout *JaarLayout = new QHBoxLayout();
	QHBoxLayout *Jaarsublayout = new QHBoxLayout();
	QLabel *jaar_l = new QLabel("jaar:");
	Jaarsublayout->addWidget(jaar_l);
	Jaarsublayout->addWidget(m_pJaar);
	JaarLayout->addLayout(Jaarsublayout);

	//editie
	m_pEditie = new QLineEdit();
	QHBoxLayout *EditieLayout = new QHBoxLayout();
	QHBoxLayout *Editiesublayout = new QHBoxLayout();
	QLabel *editie = new QLabel("editie:");
	Editiesublayout->addWidget(editie);
	Editiesublayout->addWidget(m_pEditie);
	EditieLayout->addLayout(Editiesublayout);

	

	Proplayout->addLayout(TitelLayout);
	Proplayout->addLayout(EditieLayout);
	Proplayout->addLayout(JaarLayout);
	Proplayout->addWidget(UitgeverijLayout);
	Proplayout->addWidget(BoekSizeLayout);
	Proplayout->addLayout(VersieLayout);
	Proplayout->addLayout(AuteursLayout);
	Proplayout->addLayout(IsbnLayout);
	

	QDialogButtonBox *buttonBox = new QDialogButtonBox();
	buttonBox->setOrientation(Qt::Horizontal);
	buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
	QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
	

	hoofdlayout->addWidget(boxProp);
	hoofdlayout->addWidget(buttonBox);
	
	setLayout(hoofdlayout);
}

list<string> QDialogBoekInfo::GetAuteurs()
{
	list<string> auteurs;

	QTextDocument *teksts = m_pAuteurs->document();

	for(QTextBlock it = teksts->begin(); it != teksts->end(); it = it.next())
	{
		auteurs.push_back(it.text().toStdString());
	}

	return auteurs;
}

void QDialogBoekInfo::SetAuteurs(std::list<string> auteurs)
{
	list<string>::iterator ITT;
	string text = "";
	
	ITT = auteurs.begin();

	while(ITT != auteurs.end())
	{
		text.append(*ITT);
		text.append("\n");
		ITT++;
	}
	QString auteur(text.c_str());
	m_pAuteurs->setPlainText(auteur);
}

void QDialogBoekInfo::SetBoekInfo(BoekInformatie & info)
{
	//de getauteurs geeft een vector
	//deze moet omgezet worden naar een list voor  setauteur
	list<string> aut;
	vector<string> autget;
	vector<string>::iterator ITT;

	autget = info.GetAuteurs();
	ITT= autget.begin();
	while(ITT != autget.end())
	{
		aut.push_back(*ITT);
		ITT++;
	}
	QString naam(info.GetNaamUitgeverij().c_str());
	QString adres(info.GetAdresUitgeverij().c_str());
	QString titel(info.GetTitel().c_str());
	QString editie(info.GetEditie().c_str());
	QString versie(info.GetVersie().c_str());
	QString isbn(info.GetIsbn().c_str());
	
	SetNaamUitgeverij(naam);
	SetAdresUitgeverij(adres);
	SetTitel(titel);
	SetJaarDruk(info.GetJaarDruk());
	SetEditie(editie);
	SetVersie(versie);
	SetAuteurs(aut);
	QSize afmetingen = info.GetSize();
	SetHoogte(afmetingen.rheight());
	SetBreedte(afmetingen.rwidth());
	SetIsbn(isbn);
}
void QDialogBoekInfo::GetBoekInfo(BoekInformatie * doel)
{
	doel->SetAdresUitgeverij(GetAdresUitgeverij().toStdString());
	doel->SetNaamUitgeverij(GetNaamUitgeverij().toStdString());
	doel->SetIsbn(GetIsbn().toStdString());
	doel->SetEditie(GetEditie().toStdString());
	doel->SetVersie(GetVersie().toStdString());
	doel->SetEditie(GetEditie().toStdString());
	doel->SetJaarDruk(GetJaarDruk());
	doel->SetTitel(GetTitel().toStdString());

	QSize afmetingen ;
	afmetingen.setHeight(GetHoogte());
	afmetingen.setWidth(GetBreedte());
	
	doel->SetSize(afmetingen);

	//auteurs van list naar vector omzetten
	list<string> autget;
	vector<string> aut;
	list<string>::iterator ITT;

	autget = GetAuteurs();
	ITT = autget.begin();
	while(ITT != autget.end())
	{
		aut.push_back(*ITT);
		ITT++;
	}

	doel->SetAuteurs(aut);
}