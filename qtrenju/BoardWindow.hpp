#ifndef HEADER_QT_BOARDWINDOW
#define HEADER_QT_BOARDWINDOW
#include <QtCore\QObject>
#include <QtWidgets\QWidget>
#include <QtWidgets\QPushButton>
#include <QtWidgets\QLabel>
#include <QtGui\QResizeEvent>
#include <QtGui\QMouseEvent>


#include "renju\Renju.hpp"
#include "Notify.hpp"

class BoardWindow : public QWidget
{
public:
	BoardWindow(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags(), Notify* notify = nullptr);
	~BoardWindow();
protected:
	void InitializeUI();
	void InitializeConnection();
	void paintEvent(QPaintEvent *event) override;
	void resizeEvent(QResizeEvent* event) override;
	void mousePressEvent(QMouseEvent *event) override;
private:
	Notify* m_notify;
};

#endif