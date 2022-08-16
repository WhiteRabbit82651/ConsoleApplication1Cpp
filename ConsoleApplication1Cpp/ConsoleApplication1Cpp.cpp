// ConsoleApplication1Cpp.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <windows.h>

int SendMessage();
int InputTouchInjection();
int InputTouchInjection2();
int InputTouchInjection3();
int SingleDrag();
int DoubleDrag();
int fiveDrag();
int main()
{
    std::cout << "Hello World!\n";

    const char* test = "aaaa";
    //SendMessage();
    //InputTouchInjection2();// touch
    //InputTouchInjection3();// 3点ドラッグ//うまくいかない
    //SingleDrag();//1点ドラッグ
    //DoubleDrag();//２点ドラッグ
    fiveDrag();//5点ドラッグ 画面上できてるけど、ブラウザが反応市内・・・
    return 0;
}

int SendMessage()
{
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

    printf("lResutl = %d\t", lResult);

    return 0;
}

int InputTouchInjection()
{
    // touchの初期化
    InitializeTouchInjection(1, TOUCH_FEEDBACK_INDIRECT);

    POINTER_TOUCH_INFO touchInfo;
    POINTER_INFO info;
    info.pointerType = PT_TOUCH;
    info.pointerId = 1;
    info.frameId = POINTER_FLAG_NEW;
    InjectTouchInput(1, &touchInfo);
    return 0;

}

/// <summary>
/// 
/// https://social.technet.microsoft.com/wiki/contents/articles/6460.simulating-touch-input-in-windows-8-using-touch-injection-api.aspx
/// </summary>
/// <returns></returns>
int InputTouchInjection2()
{
    // WinMain メソッドで、タッチ インジェクション API を初期化します。以下のコードを参照してください。
    POINTER_TOUCH_INFO contact;
    InitializeTouchInjection(1, TOUCH_FEEDBACK_DEFAULT); // Here number of contact point is declared as 1.
    memset(&contact, 0, sizeof(POINTER_TOUCH_INFO));

    // 接触ポイントを定義します。この定義には、接触タイプ、接触位置、接触面積、圧力、向きが含まれます。
    contact.pointerInfo.pointerType = PT_TOUCH;
    contact.pointerInfo.pointerId = 0;          //contact 0
    contact.pointerInfo.ptPixelLocation.y = 400; // Y co-ordinate of touch on screen
    contact.pointerInfo.ptPixelLocation.x = 700; // X co-ordinate of touch on screen

    contact.touchFlags = TOUCH_FLAG_NONE;
    contact.touchMask = TOUCH_MASK_CONTACTAREA | TOUCH_MASK_ORIENTATION | TOUCH_MASK_PRESSURE;
    contact.orientation = 90; // Orientation of 90 means touching perpendicular to screen.
    contact.pressure = 32000;

    // defining contact area (I have taken area of 4 x 4 pixel)
    contact.rcContact.top = contact.pointerInfo.ptPixelLocation.y - 2;
    contact.rcContact.bottom = contact.pointerInfo.ptPixelLocation.y + 2;
    contact.rcContact.left = contact.pointerInfo.ptPixelLocation.x - 2;
    contact.rcContact.right = contact.pointerInfo.ptPixelLocation.x + 2;

    // ユースケース 1 の実装、画面へのタッチダウンの注入。
    contact.pointerInfo.pointerFlags = POINTER_FLAG_DOWN | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
    InjectTouchInput(1, &contact); // Injecting the touch down on screen

    // ユース ケース 2 の実装、画面からのタッチアップの挿入。
    contact.pointerInfo.pointerFlags = POINTER_FLAG_UP;
    BOOL ret = InjectTouchInput(1, &contact); // Injecting the touch Up from screen
    if (ret)
    {
        std::cout << "InjectTouchInput's ret is true\n";
    }
    else
    {
        std::cout << "InjectTouchInput's ret is false\n";
    }

    return 0;
}

/// <summary>
/// 
/// https://social.technet.microsoft.com/wiki/contents/articles/6460.simulating-touch-input-in-windows-8-using-touch-injection-api.aspx
/// </summary>
/// <returns></returns>
int InputTouchInjection3()
{
    // WinMain メソッドで、タッチ インジェクション API を初期化します。以下のコードを参照してください。
    POINTER_TOUCH_INFO contact[3];
    InitializeTouchInjection(3, TOUCH_FEEDBACK_DEFAULT); // Here number of contact point is declared as 1.
    memset(&contact[0], 0, sizeof(POINTER_TOUCH_INFO));
    memset(&contact[1], 0, sizeof(POINTER_TOUCH_INFO));
    memset(&contact[2], 0, sizeof(POINTER_TOUCH_INFO));

    //Check Pointer Id is taken as 0 for contact 0
    contact[0].pointerInfo.pointerType = PT_TOUCH;
    contact[0].pointerInfo.pointerId = 0;          //Id 0 for contact 0
    contact[0].pointerInfo.ptPixelLocation.y = 400;
    contact[0].pointerInfo.ptPixelLocation.x = 580;
    //Defining Touch flag and touchmask for contact 0
    contact[0].touchFlags = TOUCH_FLAG_NONE;
    contact[0].touchMask = TOUCH_MASK_CONTACTAREA | TOUCH_MASK_ORIENTATION | TOUCH_MASK_PRESSURE;
    contact[0].orientation = 90;
    contact[0].pressure = 32000;
    contact[0].rcContact.top = contact[0].pointerInfo.ptPixelLocation.y - 2;
    contact[0].rcContact.bottom = contact[0].pointerInfo.ptPixelLocation.y + 2;
    contact[0].rcContact.left = contact[0].pointerInfo.ptPixelLocation.x - 2;
    contact[0].rcContact.right = contact[0].pointerInfo.ptPixelLocation.x + 2;

    //Check Pointer Id is taken as 1 for contact 1
    contact[1].pointerInfo.pointerType = PT_TOUCH;
    contact[1].pointerInfo.pointerId = 1;          //Id 0 for contact 1
    contact[1].pointerInfo.ptPixelLocation.y = 400;
    contact[1].pointerInfo.ptPixelLocation.x = 680;
    //Defining Touch flag and touchmask for contact 1
    contact[1].touchFlags = TOUCH_FLAG_NONE;
    contact[1].touchMask = TOUCH_MASK_CONTACTAREA | TOUCH_MASK_ORIENTATION | TOUCH_MASK_PRESSURE;
    contact[1].orientation = 90;
    contact[1].pressure = 32000;
    contact[1].rcContact.top = contact[1].pointerInfo.ptPixelLocation.y - 2;
    contact[1].rcContact.bottom = contact[1].pointerInfo.ptPixelLocation.y + 2;
    contact[1].rcContact.left = contact[1].pointerInfo.ptPixelLocation.x - 2;
    contact[1].rcContact.right = contact[1].pointerInfo.ptPixelLocation.x + 2;

    //Check Pointer Id is taken as 1 for contact 1
    contact[2].pointerInfo.pointerType = PT_TOUCH;
    contact[2].pointerInfo.pointerId = 2;          //Id 0 for contact 1
    contact[2].pointerInfo.ptPixelLocation.y = 400;
    contact[2].pointerInfo.ptPixelLocation.x = 780;
    //Defining Touch flag and touchmask for contact 1
    contact[2].touchFlags = TOUCH_FLAG_NONE;
    contact[2].touchMask = TOUCH_MASK_CONTACTAREA | TOUCH_MASK_ORIENTATION | TOUCH_MASK_PRESSURE;
    contact[2].orientation = 90;
    contact[2].pressure = 32000;
    contact[2].rcContact.top = contact[1].pointerInfo.ptPixelLocation.y - 2;
    contact[2].rcContact.bottom = contact[1].pointerInfo.ptPixelLocation.y + 2;
    contact[2].rcContact.left = contact[1].pointerInfo.ptPixelLocation.x - 2;
    contact[2].rcContact.right = contact[1].pointerInfo.ptPixelLocation.x + 2;

    //Implementing two touch down for both array of contact point in one go
    contact[0].pointerInfo.pointerFlags = POINTER_FLAG_DOWN | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
    contact[1].pointerInfo.pointerFlags = POINTER_FLAG_DOWN | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
    contact[2].pointerInfo.pointerFlags = POINTER_FLAG_DOWN | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
    BOOL ret = InjectTouchInput(3, contact);

    if (ret)
    {
        std::cout << "touch down ret is true\n";
    }
    else
    {
        std::cout << "touch down ret is false\n";
    }

    // 座標を移動させる
    contact[0].pointerInfo.pointerFlags = POINTER_FLAG_UPDATE | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
    contact[1].pointerInfo.pointerFlags = POINTER_FLAG_UPDATE | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
    contact[2].pointerInfo.pointerFlags = POINTER_FLAG_UPDATE | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
    for (int i = 0; i < 100; i++)
    {
        contact[0].pointerInfo.ptPixelLocation.x = contact[0].pointerInfo.ptPixelLocation.x + i;//Zooming in by dragging apart both contact points w.r.t each other
        contact[1].pointerInfo.ptPixelLocation.x = contact[1].pointerInfo.ptPixelLocation.x + i;//Zooming in by dragging apart both contact points w.r.t each other
        contact[2].pointerInfo.ptPixelLocation.x = contact[2].pointerInfo.ptPixelLocation.x + i;//Zooming in by dragging apart both contact points w.r.t each other
        ret = InjectTouchInput(3, contact);

        if (ret)
        {
            std::cout << "touch move ret is true\n";
        }
        else
        {
            std::cout << "touch move ret is false\n";
        }
        Sleep(1);
    }

    // touchアップする
    contact[0].pointerInfo.pointerFlags = POINTER_FLAG_UP;
    contact[1].pointerInfo.pointerFlags = POINTER_FLAG_UP;
    contact[2].pointerInfo.pointerFlags = POINTER_FLAG_UP;
    ret = InjectTouchInput(3, contact);

    if (ret)
    {
        std::cout << "touch up ret is true\n";
    }
    else
    {
        std::cout << "touch up ret is false\n";
    }

    return 0;
}

int SingleDrag()
{
    // WinMain メソッドで、タッチ インジェクション API を初期化します。以下のコードを参照してください。
    POINTER_TOUCH_INFO contact;
    InitializeTouchInjection(1, TOUCH_FEEDBACK_DEFAULT); // Here number of contact point is declared as 1.
    memset(&contact, 0, sizeof(POINTER_TOUCH_INFO));

    // 接触ポイントを定義します。この定義には、接触タイプ、接触位置、接触面積、圧力、向きが含まれます。
    contact.pointerInfo.pointerType = PT_TOUCH;
    contact.pointerInfo.pointerId = 0;          //contact 0
    contact.pointerInfo.ptPixelLocation.y = 400; // Y co-ordinate of touch on screen
    contact.pointerInfo.ptPixelLocation.x = 700; // X co-ordinate of touch on screen

    contact.touchFlags = TOUCH_FLAG_NONE;
    contact.touchMask = TOUCH_MASK_CONTACTAREA | TOUCH_MASK_ORIENTATION | TOUCH_MASK_PRESSURE;
    contact.orientation = 90; // Orientation of 90 means touching perpendicular to screen.
    contact.pressure = 32000;

    // defining contact area (I have taken area of 4 x 4 pixel)
    contact.rcContact.top = contact.pointerInfo.ptPixelLocation.y - 2;
    contact.rcContact.bottom = contact.pointerInfo.ptPixelLocation.y + 2;
    contact.rcContact.left = contact.pointerInfo.ptPixelLocation.x - 2;
    contact.rcContact.right = contact.pointerInfo.ptPixelLocation.x + 2;

    // ユースケース 1 の実装、画面へのタッチダウンの注入。
    contact.pointerInfo.pointerFlags = POINTER_FLAG_DOWN | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
    InjectTouchInput(1, &contact); // Injecting the touch down on screen

    // ドラッグ
    contact.pointerInfo.pointerFlags = POINTER_FLAG_UPDATE | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
    for (int i = 0; i < 100; i++) {
        contact.pointerInfo.ptPixelLocation.x--; // updating the X Co-ordinate to x-100 pixels
        InjectTouchInput(1, &contact);
    }

    // touchアップ
    // Lifts the touch input UP
    contact.pointerInfo.pointerFlags = POINTER_FLAG_UP;
    InjectTouchInput(1, &contact);

    return 0;
}

int DoubleDrag()
{
    // WinMain メソッドで、タッチ インジェクション API を初期化します。以下のコードを参照してください。
    POINTER_TOUCH_INFO contact[2];
    InitializeTouchInjection(2, TOUCH_FEEDBACK_DEFAULT); // Here number of contact point is declared as 1.
    memset(&contact[0], 0, sizeof(POINTER_TOUCH_INFO));
    memset(&contact[1], 0, sizeof(POINTER_TOUCH_INFO));

    // 接触ポイントを定義します。この定義には、接触タイプ、接触位置、接触面積、圧力、向きが含まれます。
    contact[0].pointerInfo.pointerType = PT_TOUCH;
    contact[0].pointerInfo.pointerId = 0;          //contact 0
    contact[0].pointerInfo.ptPixelLocation.y = 400; // Y co-ordinate of touch on screen
    contact[0].pointerInfo.ptPixelLocation.x = 700; // X co-ordinate of touch on screen

    contact[0].touchFlags = TOUCH_FLAG_NONE;
    contact[0].touchMask = TOUCH_MASK_CONTACTAREA | TOUCH_MASK_ORIENTATION | TOUCH_MASK_PRESSURE;
    contact[0].orientation = 90; // Orientation of 90 means touching perpendicular to screen.
    contact[0].pressure = 32000;

    // defining contact area (I have taken area of 4 x 4 pixel)
    contact[0].rcContact.top = contact[0].pointerInfo.ptPixelLocation.y - 2;
    contact[0].rcContact.bottom = contact[0].pointerInfo.ptPixelLocation.y + 2;
    contact[0].rcContact.left = contact[0].pointerInfo.ptPixelLocation.x - 2;
    contact[0].rcContact.right = contact[0].pointerInfo.ptPixelLocation.x + 2;


    // 接触ポイントを定義します。この定義には、接触タイプ、接触位置、接触面積、圧力、向きが含まれます。
    contact[1].pointerInfo.pointerType = PT_TOUCH;
    contact[1].pointerInfo.pointerId = 1;          //contact 0
    contact[1].pointerInfo.ptPixelLocation.y = 400; // Y co-ordinate of touch on screen
    contact[1].pointerInfo.ptPixelLocation.x = 600; // X co-ordinate of touch on screen

    contact[1].touchFlags = TOUCH_FLAG_NONE;
    contact[1].touchMask = TOUCH_MASK_CONTACTAREA | TOUCH_MASK_ORIENTATION | TOUCH_MASK_PRESSURE;
    contact[1].orientation = 90; // Orientation of 90 means touching perpendicular to screen.
    contact[1].pressure = 32000;

    // defining contact area (I have taken area of 4 x 4 pixel)
    contact[1].rcContact.top = contact[1].pointerInfo.ptPixelLocation.y - 2;
    contact[1].rcContact.bottom = contact[1].pointerInfo.ptPixelLocation.y + 2;
    contact[1].rcContact.left = contact[1].pointerInfo.ptPixelLocation.x - 2;
    contact[1].rcContact.right = contact[1].pointerInfo.ptPixelLocation.x + 2;



    // ユースケース 1 の実装、画面へのタッチダウンの注入。
    contact[0].pointerInfo.pointerFlags = POINTER_FLAG_DOWN | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
    contact[1].pointerInfo.pointerFlags = POINTER_FLAG_DOWN | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
    InjectTouchInput(2, contact); // Injecting the touch down on screen

    // ドラッグ
    contact[0].pointerInfo.pointerFlags = POINTER_FLAG_UPDATE | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
    contact[1].pointerInfo.pointerFlags = POINTER_FLAG_UPDATE | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
    for (int i = 0; i < 100; i++) {
        contact[0].pointerInfo.ptPixelLocation.x--; // updating the X Co-ordinate to x-100 pixels
        contact[1].pointerInfo.ptPixelLocation.x--; // updating the X Co-ordinate to x-100 pixels
        InjectTouchInput(2, contact);
    }

    // touchアップ
    // Lifts the touch input UP
    contact[0].pointerInfo.pointerFlags = POINTER_FLAG_UP;
    contact[1].pointerInfo.pointerFlags = POINTER_FLAG_UP;
    InjectTouchInput(2, contact);

    return 0;
}

int fiveDrag()
{
    // WinMain メソッドで、タッチ インジェクション API を初期化します。以下のコードを参照してください。
    POINTER_TOUCH_INFO contact[5];
    InitializeTouchInjection(5, TOUCH_FEEDBACK_DEFAULT); // Here number of contact point is declared as 1.
    memset(&contact[0], 0, sizeof(POINTER_TOUCH_INFO));
    memset(&contact[1], 0, sizeof(POINTER_TOUCH_INFO));
    memset(&contact[2], 0, sizeof(POINTER_TOUCH_INFO));
    memset(&contact[3], 0, sizeof(POINTER_TOUCH_INFO));
    memset(&contact[4], 0, sizeof(POINTER_TOUCH_INFO));


    // 接触ポイントを定義します。この定義には、接触タイプ、接触位置、接触面積、圧力、向きが含まれます。
    contact[0].pointerInfo.pointerType = PT_TOUCH;
    contact[0].pointerInfo.pointerId = 0;          //contact 0
    contact[0].pointerInfo.ptPixelLocation.y = 400; // Y co-ordinate of touch on screen
    contact[0].pointerInfo.ptPixelLocation.x = 700; // X co-ordinate of touch on screen

    contact[0].touchFlags = TOUCH_FLAG_NONE;
    contact[0].touchMask = TOUCH_MASK_CONTACTAREA | TOUCH_MASK_ORIENTATION | TOUCH_MASK_PRESSURE;
    contact[0].orientation = 90; // Orientation of 90 means touching perpendicular to screen.
    contact[0].pressure = 32000;

    // defining contact area (I have taken area of 4 x 4 pixel)
    contact[0].rcContact.top = contact[0].pointerInfo.ptPixelLocation.y - 2;
    contact[0].rcContact.bottom = contact[0].pointerInfo.ptPixelLocation.y + 2;
    contact[0].rcContact.left = contact[0].pointerInfo.ptPixelLocation.x - 2;
    contact[0].rcContact.right = contact[0].pointerInfo.ptPixelLocation.x + 2;



    // 接触ポイントを定義します。この定義には、接触タイプ、接触位置、接触面積、圧力、向きが含まれます。
    contact[1].pointerInfo.pointerType = PT_TOUCH;
    contact[1].pointerInfo.pointerId = 1;          //contact 0
    contact[1].pointerInfo.ptPixelLocation.y = 400; // Y co-ordinate of touch on screen
    contact[1].pointerInfo.ptPixelLocation.x = 600; // X co-ordinate of touch on screen

    contact[1].touchFlags = TOUCH_FLAG_NONE;
    contact[1].touchMask = TOUCH_MASK_CONTACTAREA | TOUCH_MASK_ORIENTATION | TOUCH_MASK_PRESSURE;
    contact[1].orientation = 90; // Orientation of 90 means touching perpendicular to screen.
    contact[1].pressure = 32000;

    // defining contact area (I have taken area of 4 x 4 pixel)
    contact[1].rcContact.top = contact[1].pointerInfo.ptPixelLocation.y - 2;
    contact[1].rcContact.bottom = contact[1].pointerInfo.ptPixelLocation.y + 2;
    contact[1].rcContact.left = contact[1].pointerInfo.ptPixelLocation.x - 2;
    contact[1].rcContact.right = contact[1].pointerInfo.ptPixelLocation.x + 2;


    // 接触ポイントを定義します。この定義には、接触タイプ、接触位置、接触面積、圧力、向きが含まれます。
    contact[2].pointerInfo.pointerType = PT_TOUCH;
    contact[2].pointerInfo.pointerId = 2;          //contact 0
    contact[2].pointerInfo.ptPixelLocation.y = 400; // Y co-ordinate of touch on screen
    contact[2].pointerInfo.ptPixelLocation.x = 500; // X co-ordinate of touch on screen

    contact[2].touchFlags = TOUCH_FLAG_NONE;
    contact[2].touchMask = TOUCH_MASK_CONTACTAREA | TOUCH_MASK_ORIENTATION | TOUCH_MASK_PRESSURE;
    contact[2].orientation = 90; // Orientation of 90 means touching perpendicular to screen.
    contact[2].pressure = 32000;

    // defining contact area (I have taken area of 4 x 4 pixel)
    contact[2].rcContact.top = contact[2].pointerInfo.ptPixelLocation.y - 2;
    contact[2].rcContact.bottom = contact[2].pointerInfo.ptPixelLocation.y + 2;
    contact[2].rcContact.left = contact[2].pointerInfo.ptPixelLocation.x - 2;
    contact[2].rcContact.right = contact[2].pointerInfo.ptPixelLocation.x + 2;



    // 接触ポイントを定義します。この定義には、接触タイプ、接触位置、接触面積、圧力、向きが含まれます。
    contact[3].pointerInfo.pointerType = PT_TOUCH;
    contact[3].pointerInfo.pointerId = 3;          //contact 0
    contact[3].pointerInfo.ptPixelLocation.y = 400; // Y co-ordinate of touch on screen
    contact[3].pointerInfo.ptPixelLocation.x = 400; // X co-ordinate of touch on screen

    contact[3].touchFlags = TOUCH_FLAG_NONE;
    contact[3].touchMask = TOUCH_MASK_CONTACTAREA | TOUCH_MASK_ORIENTATION | TOUCH_MASK_PRESSURE;
    contact[3].orientation = 90; // Orientation of 90 means touching perpendicular to screen.
    contact[3].pressure = 32000;

    // defining contact area (I have taken area of 4 x 4 pixel)
    contact[3].rcContact.top = contact[3].pointerInfo.ptPixelLocation.y - 2;
    contact[3].rcContact.bottom = contact[3].pointerInfo.ptPixelLocation.y + 2;
    contact[3].rcContact.left = contact[3].pointerInfo.ptPixelLocation.x - 2;
    contact[3].rcContact.right = contact[3].pointerInfo.ptPixelLocation.x + 2;



    // 接触ポイントを定義します。この定義には、接触タイプ、接触位置、接触面積、圧力、向きが含まれます。
    contact[4].pointerInfo.pointerType = PT_TOUCH;
    contact[4].pointerInfo.pointerId = 4;          //contact 0
    contact[4].pointerInfo.ptPixelLocation.y = 400; // Y co-ordinate of touch on screen
    contact[4].pointerInfo.ptPixelLocation.x = 300; // X co-ordinate of touch on screen

    contact[4].touchFlags = TOUCH_FLAG_NONE;
    contact[4].touchMask = TOUCH_MASK_CONTACTAREA | TOUCH_MASK_ORIENTATION | TOUCH_MASK_PRESSURE;
    contact[4].orientation = 90; // Orientation of 90 means touching perpendicular to screen.
    contact[4].pressure = 32000;

    // defining contact area (I have taken area of 4 x 4 pixel)
    contact[4].rcContact.top = contact[4].pointerInfo.ptPixelLocation.y - 2;
    contact[4].rcContact.bottom = contact[4].pointerInfo.ptPixelLocation.y + 2;
    contact[4].rcContact.left = contact[4].pointerInfo.ptPixelLocation.x - 2;
    contact[4].rcContact.right = contact[4].pointerInfo.ptPixelLocation.x + 2;




    // ユースケース 1 の実装、画面へのタッチダウンの注入。
    contact[0].pointerInfo.pointerFlags = POINTER_FLAG_DOWN | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
    contact[1].pointerInfo.pointerFlags = POINTER_FLAG_DOWN | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
    contact[2].pointerInfo.pointerFlags = POINTER_FLAG_DOWN | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
    contact[3].pointerInfo.pointerFlags = POINTER_FLAG_DOWN | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
    contact[4].pointerInfo.pointerFlags = POINTER_FLAG_DOWN | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
    InjectTouchInput(5, contact); // Injecting the touch down on screen

    // ドラッグ
    contact[0].pointerInfo.pointerFlags = POINTER_FLAG_UPDATE | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
    contact[1].pointerInfo.pointerFlags = POINTER_FLAG_UPDATE | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
    contact[2].pointerInfo.pointerFlags = POINTER_FLAG_UPDATE | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
    contact[3].pointerInfo.pointerFlags = POINTER_FLAG_UPDATE | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
    contact[4].pointerInfo.pointerFlags = POINTER_FLAG_UPDATE | POINTER_FLAG_INRANGE | POINTER_FLAG_INCONTACT;
    for (int i = 0; i < 100; i++) {
        contact[0].pointerInfo.ptPixelLocation.x--; // updating the X Co-ordinate to x-100 pixels
        contact[1].pointerInfo.ptPixelLocation.x--; // updating the X Co-ordinate to x-100 pixels
        contact[2].pointerInfo.ptPixelLocation.x--; // updating the X Co-ordinate to x-100 pixels
        contact[3].pointerInfo.ptPixelLocation.x--; // updating the X Co-ordinate to x-100 pixels
        contact[4].pointerInfo.ptPixelLocation.x--; // updating the X Co-ordinate to x-100 pixels
        InjectTouchInput(5, contact);
    }

    // touchアップ
    // Lifts the touch input UP
    contact[0].pointerInfo.pointerFlags = POINTER_FLAG_UP;
    contact[1].pointerInfo.pointerFlags = POINTER_FLAG_UP;
    contact[2].pointerInfo.pointerFlags = POINTER_FLAG_UP;
    contact[3].pointerInfo.pointerFlags = POINTER_FLAG_UP;
    contact[4].pointerInfo.pointerFlags = POINTER_FLAG_UP;
    InjectTouchInput(5, contact);


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
