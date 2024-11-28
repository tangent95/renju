#include "PlayWindow.hpp"
#include <QtWidgets\QMessageBox>
#include <QtGui\QPainter>
#include <cmath>

#include "renju\Renju.hpp"
#include "MainBoard.hpp"

BoardWindow::BoardWindow(QWidget* parent, Qt::WindowFlags flags, Notify* notify) : QWidget(parent, flags)
{
	m_notify = notify;
	InitializeUI();
	InitializeConnection();
}
BoardWindow::~BoardWindow()
{
	
}
void BoardWindow::InitializeUI()
{
	
}
void BoardWindow::InitializeConnection()
{
	
}
#include <cstdio>
void BoardWindow::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	renju::UINT_32 boardSize(renju::Min((renju::UINT_32)this->size().width(), (renju::UINT_32)this->size().height()) / renju::Board::boardSize);
	QPoint start;
	start.setX((this->size().width() - (boardSize * (renju::Board::boardSize - 1))) >> 1);
	start.setY((this->size().height() - (boardSize * (renju::Board::boardSize - 1))) >> 1);
	painter.setPen(QPen(Qt::black));
	painter.setBrush(QBrush(Qt::NoBrush));
	for (int line(0); line < renju::Board::boardSize; ++line)
	{
		//水平线
		painter.drawLine(QPoint(start.x() + line * boardSize, start.y()), QPoint(start.x() + line * boardSize, start.y() + (renju::Board::boardSize - 1) * boardSize));
		//竖直线
		painter.drawLine(QPoint(start.x(), start.y() + line * boardSize), QPoint(start.x() + (renju::Board::boardSize - 1) * boardSize, start.y() + line * boardSize));
	}
	
	if (mainBoard.IsBoardEmpty())
	{
		return;
	}
	renju::StonePosition buffer;
	QPoint drawPosition;
	buffer = mainBoard.GetFirstPosition();
	while (buffer.x != 0 && buffer.y != 0)
	{
		drawPosition.setX(start.x() + (renju::INT_32)boardSize * ((renju::INT_32)buffer.x - 1));
		drawPosition.setY(start.y() + (renju::INT_32)boardSize * ((renju::INT_32)buffer.y - 1));
		if (mainBoard.GetStoneType(buffer) == renju::StoneType::black)
		{
			painter.setBrush(QBrush(Qt::black));
		}
		else
		{
			painter.setBrush(QBrush(Qt::white));
		}
		painter.drawEllipse(drawPosition.x() - (renju::INT_32)(boardSize >> 1), drawPosition.y() - (renju::INT_32)(boardSize >> 1), boardSize, boardSize);
		buffer = mainBoard.GetStoneNextPosition(buffer);
	}
	
	if (mainBoard.IsEndForBan())
	{
		buffer = mainBoard.GetCurrentPosition();
		drawPosition.setX(start.x() + (renju::INT_32)boardSize * ((renju::INT_32)buffer.x - 1));
		drawPosition.setY(start.y() + (renju::INT_32)boardSize * ((renju::INT_32)buffer.y - 1));
		painter.drawLine(QPoint(drawPosition.x() - (boardSize >> 1), drawPosition.y() - (boardSize >> 1)), QPoint(drawPosition.x() + (boardSize >> 1), drawPosition.y() + (boardSize >> 1)));
		painter.drawLine(QPoint(drawPosition.x() - (boardSize >> 1), drawPosition.y() + (boardSize >> 1)), QPoint(drawPosition.x() + (boardSize >> 1), drawPosition.y() - (boardSize >> 1)));
		return;
	}
	for (buffer.x = 1; buffer.x <= renju::Board::boardSize; ++buffer.x)
	{
		for (buffer.y = 1; buffer.y <= renju::Board::boardSize; ++buffer.y)
		{
			if (mainBoard.GetStoneType(buffer) == renju::StoneType::none)
			{
				if (!mainBoard.IsMoveVaild(buffer, mainBoard.GetCurrentType() == renju::StoneType::black ? renju::StoneType::white : renju::StoneType::black))
				{
					drawPosition.setX(start.x() + (renju::INT_32)boardSize * ((renju::INT_32)buffer.x - 1));
					drawPosition.setY(start.y() + (renju::INT_32)boardSize * ((renju::INT_32)buffer.y - 1));
					painter.drawLine(QPoint(drawPosition.x() - (boardSize >> 1), drawPosition.y() - (boardSize >> 1)), QPoint(drawPosition.x() + (boardSize >> 1), drawPosition.y() + (boardSize >> 1)));
		painter.drawLine(QPoint(drawPosition.x() - (boardSize >> 1), drawPosition.y() + (boardSize >> 1)), QPoint(drawPosition.x() + (boardSize >> 1), drawPosition.y() - (boardSize >> 1)));
				}
			}
		}
	}
}
void BoardWindow::resizeEvent(QResizeEvent* event)
{
	this->update();
}
renju::StonePosition GetClickBoardPosition(const QSize& windowSize, const QPoint& input)
{
	//this->size().width()
	renju::UINT_32 boardSize(renju::Min((renju::UINT_32)windowSize.width(), (renju::UINT_32)windowSize.height()) / renju::Board::boardSize);
	QPoint start;
	start.setX((windowSize.width() - (boardSize * (renju::Board::boardSize - 1))) >> 1);
	start.setY((windowSize.height() - (boardSize * (renju::Board::boardSize - 1))) >> 1);
	renju::StonePosition result;
	result.x = (renju::UINT_32)round(1.0 * (input.x() - start.x()) / boardSize + 1);
	result.y = (renju::UINT_32)round(1.0 * (input.y() - start.y()) / boardSize + 1);
	return result;
}
void OutPutWinnner_MessageBox(QWidget* parent, const renju::WinnerType& winner)
{
	if (winner == renju::WinnerType::none)
	{
		return;
	}
	QMessageBox msgBox;
	if (winner == renju::WinnerType::draw)
	{
		msgBox.setText("平局");
	}
	else if (winner == renju::WinnerType::black)
	{
		msgBox.setText("黑方胜");
	}
	else if (winner == renju::WinnerType::white)
	{
		msgBox.setText("白方胜");
	}
	msgBox.exec();
}
void BoardWindow::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		renju::StonePosition position = GetClickBoardPosition(this->size(), event->pos());
		mainBoard.DoMove(position);
		this->update();
		if (m_notify)
		{
			m_notify->NotifyThis();
		}
		OutPutWinnner_MessageBox(this, mainBoard.GetWinner());
	}
	
}