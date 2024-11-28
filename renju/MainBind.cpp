#include <pybind11/embed.h>
#include <pybind11/operators.h>
#include "Renju.hpp"

namespace py = pybind11;
using namespace renju;


/*
┌┬┐
├┼┤
└┴┘
┌─┐
│┼│
└─┘
*/
//●〇■□○●◇◆△▲
//①②③④⑤⑥⑦⑧⑨⑩⑪⑫⑬⑭⑮⑯⑰⑱⑲⑳
//⑴⑵⑶⑷⑸⑹⑺⑻⑼⑽⑾⑿⒀⒁⒂⒃⒄⒅⒆⒇
//⒈⒉⒊⒋⒌⒍⒎⒏⒐⒑⒒⒓⒔⒕⒖⒗⒘⒙⒚⒛
//全角空格:"　"
const wchar_t num[][5] = {
L"　" , 
L"⑴" , L"⑵" , L"⑶" , L"⑷" , L"⑸" , L"⑹" , L"⑺" , L"⑻" , L"⑼" , L"⑽" , 
L"⑾" , L"⑿" , L"⒀" , L"⒁" , L"⒂" , L"⒃" , L"⒄" , L"⒅" , L"⒆" , L"⒇"
};
const wchar_t empty[] = L"┼";
const wchar_t black[] = L"□";
const wchar_t white[] = L"〇";

#include <iostream>

void OutputBoard(const Board& input)
{
	StoneType type;
	for (UINT_32 row(0); row <= Board::boardSize; ++row)
	{
		for (UINT_32 col(0); col <= Board::boardSize; ++col)
		{
			if (row == 0)
			{
				py::print(num[col], py::arg("end") = "");
			}
			else if(col == 0)
			{
				py::print(num[row], py::arg("end") = "");
			}
			else
			{
				type = input.GetStoneType(StonePosition(col, row));
				if (type == StoneType::none)
				{
					py::print(empty, py::arg("end") = "");
				}
				else if (type == StoneType::black)
				{
					py::print(black, py::arg("end") = "");
				}
				else if (type == StoneType::white)
				{
					py::print(white, py::arg("end") = "");
				}
			}
		}
		py::print("\n", py::arg("end") = "");
	}
}

PYBIND11_MODULE(renju, m)
{
	m.doc() = "A library which provide a environment for the game of renju";
	m.def("GetAuthorCString", &renju::GetAuthorCString);
	m.def("output_board", &OutputBoard);
	
	//enum class WinnerType
	py::enum_<WinnerType>(m, "WinnerType")
		.value("none", WinnerType::none)
		.value("draw", WinnerType::draw)
		.value("black", WinnerType::black)
		.value("white", WinnerType::white)
		.value("error", WinnerType::error)
		.export_values();
	
	//enum class StoneType
	py::enum_<StoneType>(m, "StoneType")
		.value("black", StoneType::black)
		.value("white", StoneType::white)
		.value("any", StoneType::any)
		.value("none", StoneType::none)
		.value("own", StoneType::own)
		.value("opponent", StoneType::opponent)
		.value("chose", StoneType::chose)
		.value("error", StoneType::error)
		.export_values();
	
	//class StonePosition
	py::class_<StonePosition>(m, "StonePosition")
		.def_readwrite("x", &StonePosition::x)
		.def_readwrite("y", &StonePosition::y)
		.def(py::init<>())
		.def(py::init<const UINT_32&, const UINT_32&>())
		.def("set_zero", &StonePosition::SetZero)
		.def("assign", &StonePosition::operator=);
	
	//class Board
	py::class_<Board>(m, "Board")
		.def_static("boardSize", []() { return Board::boardSize; })
		.def(py::init<>())
		.def(py::init<const Board&>())
		.def("copy", &Board::Copy)
		.def("is_board_empty", &Board::IsBoardEmpty)
		.def("is_game_end", &Board::IsGameEnd)
		.def("get_winner", &Board::GetWinner)
		.def("restart", &Board::Restart)
		.def("get_first_position", &Board::GetFirstPosition)
		.def("get_current_position", &Board::GetCurrentPosition)
		.def("get_stone_order", &Board::GetStoneOrder)
		.def("get_stone_type", &Board::GetStoneType)
		.def("get_stone_next_position", &Board::GetStoneNextPosition)
		.def("get_stone_previous_position", &Board::GetStonePreviousPosition)
		.def("get_current_type", &Board::GetCurrentType)
		.def("get_current_order", &Board::GetCurrentOrder)
		.def("do_move", &Board::DoMove)
		.def("retract_move", &Board::RetractMove)
		.def("is_move_vaild", &Board::IsMoveVaild)
		.def("get_winner_after_move", &Board::GetWinnerAfterMove);
}