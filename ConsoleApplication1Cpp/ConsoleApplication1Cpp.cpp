// ConsoleApplication1Cpp.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <windows.h>

int main()
{
    std::cout << "Hello World!\n";

    const char* test = "aaaa";

    //HWND hWnd = FindWindow(NULL, (LPCWSTR)test);
    HWND hWnd = FindWindow(NULL, L"WindowName");
    if (hWnd == 0)
    {
        printf("ハンドル取得エラー");
        return -1;
    }

    // タッチ用パラメータ
    TOUCHINPUT inputData;
    memset(&inputData, 0, sizeof(inputData));
    inputData.hSource = NULL;
    inputData.dwID = 1;
    inputData.x = 123;
    inputData.y = 456;
    inputData.dwFlags = 0 | TOUCHEVENTF_DOWN;
    LPARAM lParam;
    WPARAM wParam;
    wParam = 1;

    lParam = MAKELPARAM(450, 780);
    //LRESULT lResult = SendMessage(hWnd, WM_LBUTTONDOWN, 0, lParam);
    //LRESULT lResult = SendMessage(hWnd, WM_TOUCH, 0, lParam);
    //LRESULT lResult = SendMessage(hWnd, WM_TOUCH, 1, (LPARAM)&inputData);
    //LRESULT lResult = SendMessage(HWND_BROADCAST, WM_LBUTTONDOWN, 0, MAKELPARAM(0, 0));
    //lParam = (LPARAM)&inputData;
    //LRESULT lResult = PostMessage(hWnd, WM_TOUCH, 1, lParam);
    //LRESULT lResult = SendMessage(hWnd, WM_POINTERDOWN, 0, lParam);
    //LRESULT lResult = SendMessage(HWND_BROADCAST, WM_TOUCH, 1, lParam);

    HTOUCHINPUT hInput;
    hInput = (HTOUCHINPUT)lParam;
    PTOUCHINPUT pInputs;
    pInputs = new (std::nothrow) TOUCHINPUT[1];
    pInputs->x = 123;
    pInputs->y = 456;
    hInput = (HTOUCHINPUT)pInputs;
    LRESULT lResult = PostMessage(hWnd, WM_TOUCH, wParam, lParam);

    printf("lResutl = %d\t",lResult);

    return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
