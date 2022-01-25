#include "main.h"
#include "function.h"
#include "Console.h"

CauTrucBang CTBang;
CauTrucO** CTO;
Timer Count;

COORD CViTriConTro;

bool BSuDungPhim = false;

short ToaDoX;
short ToaDoY;
bool BTrangThaiChoiGame = false;



void taoMang2ChieuDong()
{
	CTO = new CauTrucO * [CTBang.SDong];
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		CTO[i] = new CauTrucO[CTBang.SDong];
	}
}

void xoaMang2ChieuDong()
{
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		delete[] CTO[i];
	}
	delete[] CTO;
}

void LuuToaDoBang() {
	ToaDoX = ((ConsoleWidth / 2) - CTBang.SDong);
	ToaDoY = (((ConsoleHeigth - 6 - CTBang.SCot) / 2) + 6);
}

void khoiTao(short SDong, short SCot, short SSoBom)
{
	CTBang.SDong = SDong;
	CTBang.SCot = SCot;
	CTBang.SSoBom = SSoBom;
	CTBang.SSoODaMo = 0;
	CTBang.SSoCo = 0;

	taoMang2ChieuDong();
	taoBomNgauNhien();
	LuuToaDoBang();
	CViTriConTro = { 0, 0 };
	BTrangThaiChoiGame = true;
	VeBang();
	Status(1, 0, 0);
	// Display_time();
}

short toaDoX(short SX)
{
	return (SX * 2 + ToaDoX); // Tọa độ x vẽ bảng
}

short toaDoY(short SY)
{
	return (SY + ToaDoY); // Tọa độ y vẽ bảng
}

void VeO(short SX, short SY, short SKieu)
{
	switch (SKieu)
	{
	case 0:
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 11, "  ");
		break;
	case 1: // Số 1 chữ màu xanh dương. Từ 1 -> 8 có nền là màu trắng.
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 9, 15, "1 ");
		break;
	case 2: // Số 2 xanh lá.
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 2, 15, "2 ");
		break;
	case 3: // Số 3 đỏ.
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 15, "3 ");
		break;
	case 4:	// Số 4 xanh dương đậm.
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 1, 15, "4 ");
		break;
	case 5: // Số 5 đỏ đậm.
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 4, 15, "5 ");
		break;
	case 6: // Số 6 cyan đậm.
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 3, 15, "6 ");
		break;
	case 7: // Số 7 đen.
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 15, "7 ");
		break;
	case 8: // Số 8 hồng
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 13, 15, "8 ");
		break;
	case 9: // Bom
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 12, "B ");
		break;
	case 10: // Ô chẵn
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 6, "  ");
		break;
	case 11: // Ô lẻ
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 8, "  ");
		break;
	case 12: // Theo dõi con trỏ
		setColorBGTextXY(toaDoX(SX) + 1, toaDoY(SY), 0, 13, " ");
		break;
	case 13: // Cắm cờ
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 14, "F ");
		break;
	case 14: // Cắm cờ sai
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 15, 16, "Fx");
		break;
	case 15: // Cắm cờ đúng
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 14, "F ");
		break;
	}
}

void VeBang()
{
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		for (int j = 0; j < CTBang.SCot; ++j)
		{
			if (CTO[i][j].BCamCo) VeO(j, i, 13);
			else if (CTO[i][j].SBomLanCan) VeO(j, i, CTO[i][j].SBomLanCan);
			else if (CTO[i][j].BDaMo) VeO(j, i, 0);
			else if ((i + j) % 2) VeO(j, i, 11);
			else VeO(j, i, 10);
			if (BSuDungPhim) VeO(CViTriConTro.X, CViTriConTro.Y, 12);
		}
	}
}

void taoBomNgauNhien()
{
	short SSoBom = CTBang.SSoBom;
	short SI, SJ; //SI là vị trí dòng, SJ là vị trí cột ta sẽ random.
	srand(time(NULL));
	while (SSoBom)
	{
		SI = rand() % CTBang.SDong;
		SJ = rand() % CTBang.SCot;
		if (CTO[SI][SJ].BCoBom)
			continue;

		CTO[SI][SJ].BCoBom = true;
		--SSoBom;
	}
}



void clickPhai(short SX, short SY) // Cắm cờ
{
	if (!CTO[SX][SY].BDaMo)
	{
		if (CTO[SX][SY].BCamCo)
		{
			CTO[SX][SY].BCamCo = false;
			CTBang.SSoCo--;
		}
		else
		{
			CTO[SX][SY].BCamCo = true;
			CTBang.SSoCo++;
		}
	}
	VeBang();
	deleteRow(4, 1);
	Status(1, 0, 0);
}

short demBomLanCan(short SX, short SY)
{
	short SDem = 0;
	for (int i = SX - 1; i <= SX + 1; ++i)
	{
		for (int j = SY - 1; j <= SY + 1; ++j)
		{
			if (i < 0 || i >= CTBang.SDong || j < 0 || j >= CTBang.SCot || (i == SX && j == SY))
				continue;

			if (CTO[i][j].BCoBom)
				++SDem;
		}
	}
	return SDem;
}

void moO(short SX, short SY)
{
	if (!CTO[SX][SY].BDaMo && !CTO[SX][SY].BCamCo)
	{
		CTO[SX][SY].BDaMo = true;
		if (CTO[SX][SY].BCoBom) thua();
		else
		{
			CTBang.SSoODaMo++;
			short SSoBomLanCan = demBomLanCan(SX, SY);
			if (SSoBomLanCan) CTO[SX][SY].SBomLanCan = SSoBomLanCan;
			else
			{
				for (int i = SX - 1; i <= SX + 1; ++i)
				{
					for (int j = SY - 1; j <= SY + 1; ++j)
					{
						if (i < 0 || i >= CTBang.SDong || j < 0 || j >= CTBang.SCot || (i == SX && j == SY))
							continue;

						moO(i, j);
					}
				}
			}
		}
	}
}

bool thongKeCo()
{
	if ((CTBang.SSoODaMo + CTBang.SSoBom) == (CTBang.SDong * CTBang.SCot))
		return true;
	return false;
}

void clickTrai(short SX, short SY)
{
	if (!CTO[SX][SY].BDaMo && !CTO[SX][SY].BCamCo)
	{
		moO(SX, SY);

		if (BTrangThaiChoiGame)
		{
			VeBang();
			if (thongKeCo())
				thang();
		}
	}
}

void thang()
{
	BTrangThaiChoiGame = false;
	xoaMang2ChieuDong();
	STrang = 5;
	deleteRow(3, 3);
	Status(2, 2, 0);
}

void thua()
{
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		for (int j = 0; j < CTBang.SCot; ++j)
		{
			if (CTO[i][j].BCamCo)
			{
				if (CTO[i][j].BCoBom)
					VeO(j, i, 15);
				else
					VeO(j, i, 14);
			}
			else
			{
				if (CTO[i][j].BCoBom)
					VeO(j, i, 9);
			}
		}
	}
	BTrangThaiChoiGame = false;
	xoaMang2ChieuDong();
	STrang = 4;
	deleteRow(3, 3);
	Status(3, 3, 0);
}

void xuLyPhim(KEY_EVENT_RECORD key)
{
	if (key.bKeyDown) // Có nhấn phím
	{
		switch (key.wVirtualKeyCode)
		{
		case VK_UP: // Mũi tên lên
			switch (STrang)
			{
			case 1: // Main menu
				if (STongMuc == 4)
				{
					if (SViTriChon == 0)
						SViTriChon = STongMuc - 1;
					else
						SViTriChon -= 1;
					MainMenu(SViTriChon);
				}
				break;
			case 2: // Choose level menu
				if (STongMuc == 5)
				{
					if (SViTriChon == 0)
						SViTriChon = STongMuc - 1;
					else
						SViTriChon -= 1;
					DifficultyMenu(SViTriChon);
				}
				break;
			case 3: // Play page
				if (BTrangThaiChoiGame)
				{
					BSuDungPhim = true;
					CViTriConTro.Y = ((CViTriConTro.Y == 0) ? CTBang.SDong - 1 : CViTriConTro.Y - 1);
					VeBang();
				}
				break;
			case 4: // Losing page
				Status(3, 3, (SViTriChon == 0) ? 1 : 0);
				break;
			case 5: // Winning page
				Status(2, 2, (SViTriChon == 0) ? 1 : 0);
				break;
			case 6: //info
				if (STongMuc == 3)
				{
					if (SViTriChon == 0)
						SViTriChon = STongMuc - 1;
					else
						SViTriChon -= 1;
					Howtoplay(SViTriChon);
				}
				break;
			case 7:
				Status(1, 1, (SViTriChon == 0) ? 1 : 0);
			}
			break;
		case VK_DOWN: // Mũi tên xuống
			switch (STrang)
			{
			case 1: // Main menu
				if (STongMuc == 4)
				{
					if (SViTriChon == STongMuc - 1)
						SViTriChon = 0;
					else
						SViTriChon += 1;
					MainMenu(SViTriChon);
				}
				break;
			case 2: // Choose level menu
				if (STongMuc == 5)
				{
					if (SViTriChon == STongMuc - 1)
						SViTriChon = 0;
					else
						SViTriChon += 1;
					DifficultyMenu(SViTriChon);
				}
				break;
			case 3: // Play page
				if (BTrangThaiChoiGame)
				{
					BSuDungPhim = true;
					CViTriConTro.Y = ((CViTriConTro.Y == CTBang.SDong - 1) ? 0 : CViTriConTro.Y + 1);
					VeBang();
				}
				break;
			case 4: // Losing page
				Status(3, 3, (SViTriChon == 0) ? 1 : 0);
				break;
			case 5: // Winning page
				Status(2, 2, (SViTriChon == 0) ? 1 : 0);
				break;
			case 6:
				if (STongMuc == 3)
				{
					if (SViTriChon == STongMuc - 1)
						SViTriChon = 0;
					else
						SViTriChon += 1;
					Howtoplay(SViTriChon);
				}
				break;
			case 7:
				Status(1, 1, (SViTriChon == 0) ? 1 : 0);
			}
			break;
		case VK_LEFT: // Mũi tên trái
			if (BTrangThaiChoiGame && STrang != 7)
			{
				BSuDungPhim = true;
				CViTriConTro.X = ((CViTriConTro.X == 0) ? CTBang.SCot - 1 : CViTriConTro.X - 1);
				VeBang();
			}
			break;
		case VK_RIGHT: // Mũi tên phải
			if (BTrangThaiChoiGame && STrang != 7)
			{
				BSuDungPhim = true;
				CViTriConTro.X = ((CViTriConTro.X == CTBang.SCot - 1) ? 0 : CViTriConTro.X + 1);
				VeBang();
			}
			break;
		case VK_RETURN: // Phím Enter
			switch (STrang)
			{
			case 1: // Main menu
				if (SViTriChon == 0)
				{
					STrang = 2;
					deleteRow(4, 5);
					DifficultyMenu(0);
				}
				else if (SViTriChon == 1)
				{

				}
				else if (SViTriChon == 2)
				{
					STrang = 6;
					deleteRow(4, 7);
					Howtoplay(0);
				}
				else exit(0);
				break;
			case 2: // Choose level menu
				if (SViTriChon == 0)
				{
					STrang = 3;
					deleteRow(4, 10);
					khoiTao(9, 9, 10);
				}
				else if (SViTriChon == 1)
				{
					STrang = 3;
					deleteRow(4, 10);
					khoiTao(16, 16, 40);
				}
				else if (SViTriChon == 2)
				{
					STrang = 3;
					deleteRow(4, 10);
					khoiTao(24, 24, 99);
				}
				else if (SViTriChon == 3)
				{
					int n, m;
					deleteRow(5, 15);
					LPCSTR STRTextMenuChinh = "  ENTER THE VALUE OF N IN NxN:  ";
					setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 9, 15, 0, STRTextMenuChinh);
					std::cin >> n;
					STRTextMenuChinh = " PLEASE ENTER THE NUMBER OF MINES:  ";
					setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 10, 15, 0, STRTextMenuChinh);
					std::cin >> m;
					STrang = 3;
					deleteRow(4, 10);
					khoiTao(n, n, m);
				}
				else if (SViTriChon == 4) {
					STrang = 1;
					deleteRow(4, 10);
					MainMenu(0);
				}
				break;
			case 4: // Losing page
				if (SViTriChon)
				{
					STrang = 1;
					deleteRow(3, ConsoleHeigth - 3);
					MainMenu(0);
				}
				else
				{
					STrang = 3;
					deleteRow(3, ConsoleHeigth - 3);
					khoiTao(CTBang.SDong, CTBang.SCot, CTBang.SSoBom);
				}
				break;
			case 5: // Winning page
				if (SViTriChon)
				{
					STrang = 1;
					deleteRow(3, ConsoleHeigth - 3);
					MainMenu(0);
				}
				break;
			case 6:
				if (SViTriChon == 2) {
					STrang = 1;
					deleteRow(3, 10);
					MainMenu(0);
				}
				break;
			case 7:
				if (SViTriChon)
				{
					STrang = 1;
					deleteRow(3, ConsoleHeigth - 3);
					MainMenu(0);
				}
				else {
					STrang = 3;
					deleteRow(3, 2);
					Status(1, 0, 0);
				}
				break;
			}
			break;
		case VK_ESCAPE: // Phím Escape
			switch (STrang)
			{
			case 1: // Main menu
				exit(0);
				break;
			case 2: // Choose level menu
				STrang = 1;
				deleteRow(4, 10);
				MainMenu(0);
				break;
			case 3:
				STrang = 7;
				Status(1, 1, 0);
			case 4: // Losing page
				break;
			case 5: // Winning page
				STrang = 1;
				deleteRow(3, ConsoleHeigth - 3);
				MainMenu(0);
				break;
			case 6:
				STrang = 1;
				deleteRow(3, ConsoleHeigth - 3);
				MainMenu(0);
				break;
			case 7:
				STrang = 3;
				deleteRow(3, 2);
				Status(1, 0, 0);
				break;
			}
			break;
		case ClickTrai: // Phím Z - mở ô
			clickTrai(CViTriConTro.Y, CViTriConTro.X);
			break;
		case ClickPhai: // Phím X - cắm cờ
			clickPhai(CViTriConTro.Y, CViTriConTro.X);
			break;
		}
	}
}
void xuLySuKien()
{
	while (1)
	{
		DWORD DWNumberOfEvents = 0; // Lưu lại sự kiện hiện tại.
		DWORD DWNumberOfEventsRead = 0; // Lưu lại số lượng sự kiện đã được lọc.

		HANDLE HConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
		GetNumberOfConsoleInputEvents(HConsoleInput, &DWNumberOfEvents);

		if (DWNumberOfEvents)
		{
			INPUT_RECORD* IREventBuffer = new INPUT_RECORD[DWNumberOfEvents];
			ReadConsoleInput(HConsoleInput, IREventBuffer, DWNumberOfEvents, &DWNumberOfEventsRead);

			for (DWORD i = 0; i < DWNumberOfEvents; ++i)
			{
				if (IREventBuffer[i].EventType == KEY_EVENT)
				{
					xuLyPhim(IREventBuffer[i].Event.KeyEvent);
				}
			}
		}
	}
}

//PART 2 DESGIN

void Title() {
	setColor(11);
	for (int i = 0; i < ConsoleWidth; i++) {
		std::cout << "x";
	}
	LPCSTR Title_game = " MINESWEEPER ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(Title_game) / 2), 1, 14, 0, Title_game);
	setColor(11);
	cout << endl;
	for (int j = 0; j < ConsoleWidth; j++) {
		std::cout << "x";
	}
}

void Status(short STrangThai, short SCheDo, short SIndex) {
	SViTriChon = SIndex;
	STongMuc = 2;

	setColorBGTextXY(1, 3, 14, 0, "MAPS: %d x %d", CTBang.SDong, CTBang.SCot);
	setColorBGTextXY(1, 4, 14, 0, "BOOMS: %d", CTBang.SSoBom - CTBang.SSoCo);
	setColor(7);

	LPCSTR STRTextMenuCheDo;
	if (SCheDo == 1)
	{
		STRTextMenuCheDo = "  CONTINUE  ";
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuCheDo) / 2) - 1, 3, 15, ((SIndex == 0) ? 2 : 0), STRTextMenuCheDo);

	}
	if (SCheDo == 2)
	{
		STRTextMenuCheDo = "  SAVE SCORE  ";
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuCheDo) / 2), 3, 15, ((SIndex == 0) ? 2 : 0), STRTextMenuCheDo);
	}
	if (SCheDo == 3)
	{
		STRTextMenuCheDo = "  REPLAY  ";
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuCheDo) / 2) - 1, 3, 15, ((SIndex == 0) ? 2 : 0), STRTextMenuCheDo);
	}
	if (SCheDo >= 1)
	{
		STRTextMenuCheDo = "  MAIN MENU  ";
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuCheDo) / 2) - 1, 4, 15, ((SIndex == 1) ? 2 : 0), STRTextMenuCheDo);
	}



	if (STrangThai == 1) {
		setColorBGTextXY(ConsoleWidth - 16, 3, 14, 0, "STATUS: PLAYING");
	}
	if (STrangThai == 2) {
		setColorBGTextXY(ConsoleWidth - 12, 3, 14, 0, "STATUS: WIN");
	}
	if (STrangThai == 3) {
		setColorBGTextXY(ConsoleWidth - 13, 3, 14, 0, "STATUS: LOSE");
	}
}

void MainMenu(short SIndex)
{
	SViTriChon = SIndex;
	STongMuc = 4;

	LPCSTR STRTextMenuChinh = "  NEW GAME  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 7, 15, ((SIndex == 0) ? 2 : 0), STRTextMenuChinh);

	STRTextMenuChinh = "  SCOREBOARD  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 8, 15, ((SIndex == 1) ? 2 : 0), STRTextMenuChinh);

	STRTextMenuChinh = "  INFORMATION  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 9, 15, ((SIndex == 2) ? 2 : 0), STRTextMenuChinh);

	STRTextMenuChinh = "  EXIT  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 10, 15, ((SIndex == 3) ? 2 : 0), STRTextMenuChinh);
}

void DifficultyMenu(short SIndex)
{
	SViTriChon = SIndex;
	STongMuc = 5;

	LPCSTR STRTextMenuChinh = "  CHOOSE LEVEL  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 4, 14, 0, STRTextMenuChinh);

	STRTextMenuChinh = "  EASY (9x9 and 10 mines)  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 7, 15, ((SIndex == 0) ? 2 : 0), STRTextMenuChinh);

	STRTextMenuChinh = "  MEDIUM (16x16 and 40 mines)  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 8, 15, ((SIndex == 1) ? 2 : 0), STRTextMenuChinh);

	STRTextMenuChinh = "  HARD (24x24 and 99 mines)  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 9, 15, ((SIndex == 2) ? 2 : 0), STRTextMenuChinh);
	STRTextMenuChinh = "  CUSTOMIZING YOUR LEVEL  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 10, 15, ((SIndex == 3) ? 2 : 0), STRTextMenuChinh);
	STRTextMenuChinh = "  RETURN  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 13, 15, ((SIndex == 4) ? 2 : 0), STRTextMenuChinh);
}

void Howtoplay(short SIndex) {
	SViTriChon = SIndex;
	STongMuc = 3;
	LPCSTR STRTextMenuChinh = "  INTRODUCTION ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 4, 14, 0, STRTextMenuChinh);
	STRTextMenuChinh = "  PRESS Z TO OPEN   ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 7, 15, ((SIndex == 0) ? 2 : 0), STRTextMenuChinh);
	STRTextMenuChinh = "  PRESS X TO FLAG   ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 8, 15, ((SIndex == 1) ? 2 : 0), STRTextMenuChinh);
	STRTextMenuChinh = " GO BACK ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 9, 15, ((SIndex == 2) ? 2 : 0), STRTextMenuChinh);

}
void Display_time() {
	// short t = STrangThai;

	Count.SSec = 0;
	Count.SMinute = 0;
	while (BTrangThaiChoiGame) {
		setColorBGTextXY(1, 5, 14, 0, "TIME: %d:%d", Count.SMinute, Count.SSec);
		//std::cout << "Timer: " << min << " : " << sec;
		Count.SSec++;
		if (Count.SSec == 60) {
			Count.SSec = 0;
			Count.SMinute++;
		}
		Sleep(1000);
	}
}