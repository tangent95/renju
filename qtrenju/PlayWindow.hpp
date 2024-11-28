#ifndef HEADER_QT_PLAYWINDOW
#define HEADER_QT_PLAYWINDOW
#include <QtCore\QObject>
#include <QtWidgets\QWidget>
#include <QtWidgets\QPushButton>
#include <QtWidgets\QLabel>
#include <QtGui\QResizeEvent>
#include <QtGui\QMouseEvent>
#include <QtWidgets\QHBoxLayout>
#include <QtWidgets\QVBoxLayout>

#include "BoardWindow.hpp"
#include "Notify.hpp"

class PlayWindow : public QWidget, public Notify
{
public:
	PlayWindow(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
	~PlayWindow();
	void NotifyThis() override;
protected:
	void InitializeUI();
	void InitializeConnection();
	void resizeEvent(QResizeEvent* event) override;
	void mousePressEvent(QMouseEvent *event) override;
public:
	QPushButton* restartButton;
	QPushButton* retractButton;
	QPushButton* scorePlaceButton;
	QPushButton* MCTSPlaceButton;
	QLabel* statusLabel;
	
	QHBoxLayout* mainLayout;
	QVBoxLayout* controlLayout;
	BoardWindow* boardWindow;
};
#endif