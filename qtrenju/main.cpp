#include <QtWidgets/QApplication>
#include "PlayWindow.hpp"

int main(int argc,char** argv)
{
	QApplication app(argc, argv);
	PlayWindow window;
	window.resize(800, 600);
	window.setWindowTitle("renju");
	window.show();
	return app.exec();
}