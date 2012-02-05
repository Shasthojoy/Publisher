// Mathy Vanhoef
#include <iostream>
#include <QtGui/QApplication>
#include <QtXml/QDomDocument>
#include <QtXml/QDomText>
#include "MainWindow.h"

// Visual Leak Detector
//#include <vld.h>

int main(int argc, char *argv[])
{
	Q_INIT_RESOURCE(resources);
	QApplication qapp(argc, argv);

	MainWindow main;
	main.show();

	return qapp.exec();
}


