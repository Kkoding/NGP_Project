// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once
#pragma comment(lib, "ws2_32")
#pragma comment(lib, "winmm.lib")
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>
#include <mmsystem.h>
using namespace std;

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// OFFICIAL HEADER
#include <WinSock2.h>
#include <iostream>
#include <list>
#include <chrono>
#include <random>
#include <atlimage.h>

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
//	NON_OFFICIAL HEADER
//#include "../../NGP_SERVER/SnakeServer/protocol.h"
#include "../../TCPServer/protocol.h"
#include "Global.h"
#include "MainGame.h"
#include "Network.h"