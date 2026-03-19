#include <windows.h>    // Windows API для создания графического интерфейса
#include <cmath>        // Математические функции
#include <ctime>        // Функции для работы со временем (для инициализации rand)
#include <cstdlib>      // Стандартная библиотека C (rand, RAND_MAX)

// Базовый класс для графических объектов
class Point {
protected:
    int x, y;           // Координаты центра точки
    COLORREF color;     // Цвет объекта (RGB значение)

public:
    // Инициализация объекта
    void init(int xn, int yn, COLORREF color) {
        this->x = xn;       // Установка координаты X
        this->y = yn;       // Установка координаты Y
        this->color = color;// Установка цвета
    }

    // Виртуальные методы для отображения и скрытия объекта
    virtual void show(HDC hdc) {}   // Отобразить объект в контексте устройства (HDC)
    virtual void hide(HDC hdc) {}   // Скрыть объект (перерисовать цветом фона)

    // Получение текущих координат объекта
    void locat(int& xl, int& yl) {
        xl = x;  // Возврат X координаты через параметр
        yl = y;  // Возврат Y координаты через параметр
    }

    // Метод для "полета" - случайного перемещения объекта по экрану
    void fly(HDC hdc, int cost) {
        show(hdc);  // Показать объект в начальной позиции
        int xx, yy; // Временные переменные для новых координат

        // Бесконечный цикл перемещения (прерывается клавишей ESC)
        do {
            locat(xx, yy);  // Получаем текущие координаты

            // Генерация новой случайной координаты X
            do {
                // (rand()/(double)RAND_MAX - 0.5) дает значение от -0.5 до 0.5
                // Умножаем на cost для контроля "скорости" перемещения
                xx = xx + (int)((rand() / (double)RAND_MAX - 0.5) * cost);
            } while (xx > 0 && xx < GetSystemMetrics(SM_CXSCREEN)); // Проверка границ экрана

            // Генерация новой случайной координаты Y
            do {
                yy = yy + (int)((rand() / (double)RAND_MAX - 0.5) * cost);
            } while (yy > 0 && yy < GetSystemMetrics(SM_CYSCREEN)); // Проверка границ экрана

            hide(hdc);  // Скрыть объект в старой позиции
            x = xx;     // Обновить X координату
            y = yy;     // Обновить Y координату
            show(hdc);  // Показать объект в новой позиции

            Sleep(300); // Пауза 300 мс между перемещениями
        } while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000)); // Цикл пока не нажата ESC
    }

    // Виртуальный деструктор для корректного удаления объектов наследников
    virtual ~Point() {}
};

// Класс "Круг", наследуется от Point
class Krug : public Point {
protected:
    int radius;  // Радиус круга

public:
    Krug() {}  // Конструктор по умолчанию

    // Инициализация круга с указанием радиуса
    void init(int xn, int yn, int r, COLORREF color) {
        Point::init(xn, yn, color);  // Вызов родительского метода init
        radius = r;  // Установка радиуса
    }

    // Отображение круга
    virtual void show(HDC hdc) override {
        // Создание кисти для заливки (цветом объекта)
        HBRUSH hBrush = CreateSolidBrush(color);
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

        // Создание пера для контура (того же цвета)
        HPEN hPen = CreatePen(PS_SOLID, 1, color);
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

        // Рисование эллипса, который будет кругом (ширина=высоте=2*radius)
        // Ellipse рисует вписанный в прямоугольник эллипс
        Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);

        // Восстановление старых объектов и удаление созданных
        SelectObject(hdc, hOldBrush);
        SelectObject(hdc, hOldPen);
        DeleteObject(hBrush);
        DeleteObject(hPen);
    }

    // Скрытие круга (рисование цветом фона окна)
    virtual void hide(HDC hdc) override {
        // Получение цвета фона окна
        RECT rect;
        GetClientRect(WindowFromDC(hdc), &rect);

        // Создание кисти цвета фона окна
        HBRUSH hBrush = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

        // Создание пера цвета фона окна
        HPEN hPen = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_WINDOW));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

        // Рисование круга цветом фона (стирание)
        Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);

        // Восстановление и удаление объектов
        SelectObject(hdc, hOldBrush);
        SelectObject(hdc, hOldPen);
        DeleteObject(hBrush);
        DeleteObject(hPen);
    }
};

// Класс "Кольцо", наследуется от Krug
class Ring : public Krug {
private:
    int width;  // Ширина кольца (толщина ободка)

public:
    Ring() {}  // Конструктор по умолчанию

    // Инициализация кольца с указанием ширины
    void init(int xn, int yn, int r, COLORREF color, int wid) {
        Krug::init(xn, yn, r, color);  // Вызов родительского метода init
        width = wid;  // Установка ширины кольца
    }

    // Отображение кольца
    virtual void show(HDC hdc) override {
        // Сначала рисуем внешний круг (наследуем от Krug::show)
        Krug::show(hdc);

        // Затем рисуем внутренний круг (чтобы получилось кольцо)
        // Используем штриховую кисть для наглядности
        HBRUSH hBrush = CreateHatchBrush(HS_DIAGCROSS, GetSysColor(COLOR_WINDOW));
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
        HPEN hPen = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_WINDOW));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

        // Рисуем внутренний круг радиусом (radius - width)
        // Это создает отверстие в центре, образуя кольцо
        Ellipse(hdc, x - (radius - width), y - (radius - width),
            x + (radius - width), y + (radius - width));

        // Восстановление и удаление объектов
        SelectObject(hdc, hOldBrush);
        SelectObject(hdc, hOldPen);
        DeleteObject(hBrush);
        DeleteObject(hPen);
    }
};

// Оконная процедура - обработчик сообщений окна
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    // Статические объекты (существуют все время работы окна)
    static Krug testKrug;   // Объект типа "Круг"
    static Ring testRing;   // Объект типа "Кольцо"
    static bool initialized = false;  // Флаг инициализации

    switch (message) {
    case WM_CREATE:  // Создание окна
        srand(time(NULL));  // Инициализация генератора случайных чисел
        initialized = true;

        // Инициализация круга: координаты (150,40), радиус 50, красный цвет
        testKrug.init(150, 40, 50, RGB(255, 0, 0));

        // Инициализация кольца: координаты (450,80), радиус 90, синий цвет, ширина 10
        testRing.init(450, 80, 90, RGB(0, 0, 255), 10);
        break;

    case WM_PAINT: {  // Перерисовка окна
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);  // Начало рисования

        if (initialized) {
            testKrug.show(hdc);  // Отображаем круг
            testRing.show(hdc);  // Отображаем кольцо
        }

        EndPaint(hWnd, &ps);  // Завершение рисования
        break;
    }

    case WM_KEYDOWN:  // Нажатие клавиши
        if (wParam == VK_SPACE) {  // Если нажат ПРОБЕЛ
            HDC hdc = GetDC(hWnd);  // Получаем контекст устройства
            testKrug.fly(hdc, 100);  // Запускаем "полет" круга с параметром 100
            ReleaseDC(hWnd, hdc);  // Освобождаем контекст устройства

            // Запрос на перерисовку всего окна
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;

    case WM_DESTROY:  // Закрытие окна
        PostQuitMessage(0);  // Отправка сообщения о выходе
        break;

    default:  // Обработка остальных сообщений по умолчанию
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Точка входа Windows приложения
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Используем широкие символы для совместимости с Unicode
    const wchar_t CLASS_NAME[] = L"ObjectMoveWindow";

    // Регистрация класса окна
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;       // Указатель на оконную процедуру
    wc.hInstance = hInstance;       // Дескриптор экземпляра приложения
    wc.lpszClassName = CLASS_NAME;  // Имя класса окна
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);  // Курсор - стрелка
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);  // Цвет фона окна

    RegisterClass(&wc);  // Регистрация класса окна в системе

    // Создание окна
    HWND hWnd = CreateWindowEx(
        0,                    // Дополнительные стили
        CLASS_NAME,           // Имя класса окна
        L"Moving Objects - Press SPACE to move",  // Заголовок окна
        WS_OVERLAPPEDWINDOW,  // Стиль окна (стандартное перекрывающееся окно)
        CW_USEDEFAULT,        // X позиция (по умолчанию)
        CW_USEDEFAULT,        // Y позиция (по умолчанию)
        800,                  // Ширина окна
        600,                  // Высота окна
        NULL,                 // Родительское окно
        NULL,                 // Меню
        hInstance,            // Дескриптор экземпляра
        NULL                  // Дополнительные параметры
    );

    if (hWnd == NULL) return 0;  // Если окно не создано - выход

    // Показать и обновить окно
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Цикл обработки сообщений
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);  // Трансляция сообщений клавиш
        DispatchMessage(&msg);   // Отправка сообщений в оконную процедуру
    }

    return 0;  // Завершение приложения
}
