#include "PlayWindow.hpp"
#include <QtWidgets\QMessageBox>
#include <QtGui\QPainter>

#include "MainBoard.hpp"
#include "MCTS\RolloutMCTS.hpp"

//#ifdef MSVC
#pragma execution_character_set("utf-8")
//#endif

PlayWindow::PlayWindow(QWidget* parent, Qt::WindowFlags flags) : QWidget(parent, flags)
{
	InitializeUI();
	InitializeConnection();
}
PlayWindow::~PlayWindow()
{
	
}
void SetStatusText(QLabel* label)
{
	QString text;
	text += "第";
	if (mainBoard.IsBoardEmpty())
	{
		text += QString::number(0 + 1);
	}
	else
	{
		text += QString::number(mainBoard.GetCurrentOrder() + 1);
	}
	text += "步\n";
	
	text += "轮走方:";
	if (mainBoard.IsBoardEmpty())
	{
		text += "黑";
	}
	else
	{
		if (mainBoard.GetCurrentType() == renju::StoneType::black)
		{
			text += "白";
		}
		else
		{
			text += "黑";
		}
	}
	label->setText(text);
}
void PlayWindow::NotifyThis()
{
	SetStatusText(statusLabel);
}
void PlayWindow::InitializeUI()
{
	mainLayout = new QHBoxLayout;
	controlLayout = new QVBoxLayout;
	boardWindow = new BoardWindow(nullptr, Qt::WindowFlags(), this);
	boardWindow->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	statusLabel = new QLabel;
	SetStatusText(statusLabel);
	statusLabel->setSizePolicy(statusLabel->sizePolicy().horizontalPolicy(), QSizePolicy::Minimum);
	statusLabel->setStyleSheet("border: 1px solid black;");
	restartButton = new QPushButton("重新开始");
	retractButton = new QPushButton("悔棋");
	scorePlaceButton = new QPushButton("打分落子");
	MCTSPlaceButton = new QPushButton("MCTS落子");
	
	controlLayout->setSpacing(2);
	controlLayout->addWidget(statusLabel, 0, Qt::AlignTop);
	controlLayout->addWidget(restartButton, 0, Qt::AlignTop);
	controlLayout->addWidget(retractButton, 0, Qt::AlignTop);
	controlLayout->addWidget(scorePlaceButton, 0, Qt::AlignTop);
	controlLayout->addWidget(MCTSPlaceButton, 0, Qt::AlignTop);
	
	mainLayout->addWidget(boardWindow);
	mainLayout->addLayout(controlLayout);
	this->setLayout(mainLayout);
}
#include <cstdlib>
#include <ctime>
void PlayWindow::InitializeConnection()
{
	connect(restartButton, &QPushButton::clicked, [&]() { mainBoard.Restart(); boardWindow->update(); NotifyThis(); });
	connect(retractButton, &QPushButton::clicked, [&]() { mainBoard.RetractMove(); boardWindow->update(); NotifyThis(); });
	connect(MCTSPlaceButton, &QPushButton::clicked, [&]() { 
		renju::RolloutMCTS mcts;
		mcts.SetLimitation(renju::LimitationType::iteration, 0, 200000, 100);
		mainBoard.DoMove(mcts.GetMove(mainBoard, 2));
		boardWindow->update();
		NotifyThis();
		});
	connect(scorePlaceButton, &QPushButton::clicked, [&]() { 
		renju::RolloutMCTS mcts;
		mcts.ScorePlace(mainBoard, rand());
		boardWindow->update();
		NotifyThis();
		});
	srand((renju::UINT_32)time(NULL));
}
void PlayWindow::resizeEvent(QResizeEvent* event)
{
	
}
void PlayWindow::mousePressEvent(QMouseEvent *event)
{
	
}