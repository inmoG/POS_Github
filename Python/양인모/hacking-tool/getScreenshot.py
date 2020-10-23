import win32gui, win32api, win32ui, win32con # pyWinhook module
import time
import os

def getScreenshot(): # 화면캡쳐
    hwnd = win32gui.GetDesktopWindow() 
    left, top, right, bottom = win32gui.GetWindowRect(hwnd)
    height = bottom - top
    width = right -left
    hDC = win32gui.GetWindowDC(hwnd) # DC for windows 윈도우 디바이스 컨텍스트 hDC 리턴
    pDC = win32ui.CreateDCFromHandle(hDC) # win32 API 컨텍스트 형식 >> pwin32 컨텍스트로 변환
    memDC = pDC.CreateCompatibleDC() # 지정된 디바이스 컨텍스트에 호환되는 메모리 디바이스 컨텍스트 생성

    screenshot = win32ui.CreateBitmap() # 비트맵 객체 생성
    screenshot.CreateCompatibleBitmap(pDC, width, height) # PDC와 호환되는 전체 화면 크기 구성
    memDC.SelectObject(screenshot)

    memDC.BitBlt((0,0), (width, height), pDC, (left,top), win32con.SRCCOPY)
    screenshot.SaveBitmapFile(memDC, 'C:\Windows\Temp\screenshot.bmp')
    # 지정된 디바이스 컨텍스트 즉 추출하려는 윈도우로부터 지정된 크기의 직사각형 영역 픽셀에 대응하는 컬러데이터를 memDC에 비트 블록 단위로 전송

    memDC.DeleteDC() # 객체 제거
    win32gui.DeleteObject(screenshot.GetHandle()) # 객체 제거

def main():
   getScreenshot()

if __name__ == '__main__':
    main()