#include <windows.h>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>

class Point {
protected:
    int x, y;
    COLORREF color;
    bool colorChanging;  // Флаг для изменения цвета
    std::vector<COLORREF> colors;  // Массив цветов для циклической смены
    int currentColorIndex;  // Текущий индекс цвета

public:
    Point() : colorChanging(false), currentColorIndex(0) {
        // Начальная инициализация цветов (можно расширить)
        colors.push_back(RGB(255, 0, 0));   // Красный
        colors.push_back(RGB(0, 255, 0));   // Зеленый
        colors.push_back(RGB(0, 0, 255));   // Синий
        colors.push_back(RGB(255, 255, 0)); // Желтый
        colors.push_back(RGB(255, 0, 255)); // Пурпурный
        colors.push_back(RGB(0, 255, 255)); // Голубой
    }

    void init(int xn, int yn, COLORREF color) {
        this->x = xn;
        this->y = yn;
        this->color = color;
        this->colorChanging = false;
        this->currentColorIndex = 0;
    }

    virtual void show(HDC hdc) {}
    virtual void hide(HDC hdc) {}

    void locat(int& xl, int& yl) {
        xl = x;
        yl = y;
    }

    // Метод для смены цвета
    void changeColor() {
        if (colors.empty()) return;

        currentColorIndex = (currentColorIndex + 1) % colors.size();
        color = colors[currentColorIndex];
    }

    // Метод для включения/выключения смены цветов
    void enableColorChanging(bool enable) {
        colorChanging = enable;
    }

    // Перегруженный метод fly с дополнительными функциями
    void fly(HDC hdc, int cost) {
        show(hdc);
        int xx, yy;
        int moveCount = 0;  // Счетчик перемещений

        do {
            locat(xx, yy);

            // Генерация новых координат
            do {
                xx = xx + (int)((rand() / (double)RAND_MAX - 0.5) * cost);
            } while (xx > 0 && xx < GetSystemMetrics(SM_CXSCREEN));

            do {
                yy = yy + (int)((rand() / (double)RAND_MAX - 0.5) * cost);
            } while (yy > 0 && yy < GetSystemMetrics(SM_CYSCREEN));

            hide(hdc);
            x = xx;
            y = yy;

            // Каждое 3-е перемещение меняем цвет
            if (colorChanging && (moveCount % 3 == 0)) {
                changeColor();
            }

            moveCount++;
            show(hdc);

            Sleep(300);
        } while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000));
    }

    // Метод для плавного перемещения с анимацией
    void flyWithAnimation(HDC hdc, int cost) {
        show(hdc);
        int xx, yy;
        int moveCount = 0;

        do {
            int startX = x;
            int startY = y;

            // Генерация целевых координат
            do {
                xx = startX + (int)((rand() / (double)RAND_MAX - 0.5) * cost);
            } while (xx > 0 && xx < GetSystemMetrics(SM_CXSCREEN));

            do {
                yy = startY + (int)((rand() / (double)RAND_MAX - 0.5) * cost);
            } while (yy > 0 && yy < GetSystemMetrics(SM_CYSCREEN));

            // Плавная анимация движения
            int steps = 20;
            for (int i = 0; i <= steps; i++) {
                hide(hdc);

                // Интерполяция координат
                x = startX + (xx - startX) * i / steps;
                y = startY + (yy - startY) * i / steps;

                // Меняем цвет каждые 5 шагов
                if (colorChanging && (moveCount % 5 == 0)) {
                    changeColor();
                }

                show(hdc);
                Sleep(20);
            }

            moveCount++;
        } while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000));
    }

    virtual ~Point() {}
};

class Krug : public Point {
protected:
    int radius;
    bool radiusChanging;  // Флаг для изменения радиуса
    int minRadius;        // Минимальный радиус
    int maxRadius;        // Максимальный радиус
    int radiusStep;       // Шаг изменения радиуса
    bool increasing;      // Направление изменения (увеличение/уменьшение)

public:
    Krug() : radiusChanging(false), increasing(true) {
        minRadius = 10;
        maxRadius = 100;
        radiusStep = 5;
    }

    void init(int xn, int yn, int r, COLORREF color) {
        Point::init(xn, yn, color);
        radius = r;
        // Устанавливаем границы радиуса
        minRadius = max(10, r / 2);
        maxRadius = min(200, r * 2);
    }

    // Метод для изменения радиуса (пульсация)
    void changeRadius() {
        if (!radiusChanging) return;

        if (increasing) {
            radius += radiusStep;
            if (radius >= maxRadius) {
                radius = maxRadius;
                increasing = false;
            }
        }
        else {
            radius -= radiusStep;
            if (radius <= minRadius) {
                radius = minRadius;
                increasing = true;
            }
        }
    }

    // Включение/выключение изменения радиуса
    void enableRadiusChanging(bool enable) {
        radiusChanging = enable;
    }

    // Установка параметров изменения радиуса
    void setRadiusRange(int minR, int maxR, int step) {
        minRadius = minR;
        maxRadius = maxR;
        radiusStep = step;
        radius = min(max(radius, minR), maxR);
    }

    virtual void show(HDC hdc) override {
        HBRUSH hBrush = CreateSolidBrush(color);
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
        HPEN hPen = CreatePen(PS_SOLID, 2, color);
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

        Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);

        SelectObject(hdc, hOldBrush);
        SelectObject(hdc, hOldPen);
        DeleteObject(hBrush);
        DeleteObject(hPen);
    }

    virtual void hide(HDC hdc) override {
        RECT rect;
        GetClientRect(WindowFromDC(hdc), &rect);
        HBRUSH hBrush = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
        HPEN hPen = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_WINDOW));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

        Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);

        SelectObject(hdc, hOldBrush);
        SelectObject(hdc, hOldPen);
        DeleteObject(hBrush);
        DeleteObject(hPen);
    }

    // Комплексное перемещение с изменением цвета и радиуса
    void flyWithEffects(HDC hdc, int cost) {
        show(hdc);
        int xx, yy;
        int moveCount = 0;

        do {
            locat(xx, yy);

            do {
                xx = xx + (int)((rand() / (double)RAND_MAX - 0.5) * cost);
            } while (xx > 0 && xx < GetSystemMetrics(SM_CXSCREEN));

            do {
                yy = yy + (int)((rand() / (double)RAND_MAX - 0.5) * cost);
            } while (yy > 0 && yy < GetSystemMetrics(SM_CYSCREEN));

            hide(hdc);
            x = xx;
            y = yy;

            // Каждое перемещение - эффекты
            if (moveCount % 2 == 0 && colorChanging) {
                changeColor();
            }

            if (moveCount % 3 == 0 && radiusChanging) {
                changeRadius();
            }

            moveCount++;
            show(hdc);

            Sleep(300);
        } while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000));
    }
};

class Ring : public Krug {
private:
    int width;
    bool widthChanging;      // Флаг изменения ширины кольца
    int minWidth;           // Минимальная ширина
    int maxWidth;           // Максимальная ширина
    int widthStep;          // Шаг изменения ширины
    bool widthIncreasing;   // Направление изменения ширины

    // Параметры для вырезанного сектора
    double startAngle;      // Начальный угол сектора (в градусах)
    double endAngle;        // Конечный угол сектора (в градусах)
    bool angleChanging;     // Флаг изменения углов
    double angleStep;       // Шаг изменения угла
    bool angleExpanding;    // Расширение или сужение сектора

public:
    Ring() : widthChanging(false), widthIncreasing(true),
        startAngle(0.0), endAngle(90.0), angleChanging(false),
        angleStep(5.0), angleExpanding(true) {
        minWidth = 5;
        maxWidth = 50;
        widthStep = 2;
    }

    void init(int xn, int yn, int r, COLORREF color, int wid) {
        Krug::init(xn, yn, r, color);
        width = wid;
        minWidth = max(5, wid / 2);
        maxWidth = min(r - 10, wid * 2);
        startAngle = 0.0;
        endAngle = 90.0;  // Начальный сектор 90 градусов
    }

    // Метод для изменения ширины кольца
    void changeWidth() {
        if (!widthChanging) return;

        if (widthIncreasing) {
            width += widthStep;
            if (width >= maxWidth) {
                width = maxWidth;
                widthIncreasing = false;
            }
        }
        else {
            width -= widthStep;
            if (width <= minWidth) {
                width = minWidth;
                widthIncreasing = true;
            }
        }

        // Гарантируем, что внутренний радиус не станет отрицательным
        if (width >= radius) {
            width = radius - 5;
        }
    }

    // Метод для изменения вырезанного сектора
    void changeSector() {
        if (!angleChanging) return;

        if (angleExpanding) {
            // Расширяем сектор
            endAngle += angleStep;
            if (endAngle - startAngle >= 360) {
                endAngle = startAngle + 360;
                angleExpanding = false;
            }
        }
        else {
            // Сужаем сектор
            endAngle -= angleStep;
            if (endAngle - startAngle <= 10) {
                endAngle = startAngle + 10;
                angleExpanding = true;
            }
        }

        // Нормализуем углы
        if (endAngle > 360) {
            startAngle = 0;
            endAngle = endAngle - 360;
        }
    }

    // Включение/выключение изменения ширины
    void enableWidthChanging(bool enable) {
        widthChanging = enable;
    }

    // Включение/выключение изменения сектора
    void enableSectorChanging(bool enable) {
        angleChanging = enable;
    }

    // Установка параметров сектора
    void setSector(double start, double end, double step) {
        startAngle = start;
        endAngle = end;
        angleStep = step;
    }

    // Переопределенный метод show для рисования кольца с сектором
    virtual void show(HDC hdc) override {
        // Сначала рисуем полное кольцо
        HBRUSH hBrush = CreateSolidBrush(color);
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
        HPEN hPen = CreatePen(PS_SOLID, 2, color);
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

        // Внешний круг
        Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);

        // Внутренний круг (создает отверстие)
        HBRUSH hBrushWhite = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
        SelectObject(hdc, hBrushWhite);
        HPEN hPenWhite = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_WINDOW));
        SelectObject(hdc, hPenWhite);

        Ellipse(hdc, x - (radius - width), y - (radius - width),
            x + (radius - width), y + (radius - width));

        // Теперь рисуем вырезанный сектор (заполняем его цветом фона)
        // Для этого используем Pie или Arc для создания сектора
        if (angleChanging && (endAngle - startAngle) < 360) {
            // Преобразуем градусы в радианы для тригонометрических функций
            const double pi = 3.14159265358979323846;

            // Рассчитываем точки для сектора
            int outerStartX = x + (int)(radius * cos(startAngle * pi / 180.0));
            int outerStartY = y - (int)(radius * sin(startAngle * pi / 180.0));
            int outerEndX = x + (int)(radius * cos(endAngle * pi / 180.0));
            int outerEndY = y - (int)(radius * sin(endAngle * pi / 180.0));

            int innerStartX = x + (int)((radius - width) * cos(startAngle * pi / 180.0));
            int innerStartY = y - (int)((radius - width) * sin(startAngle * pi / 180.0));
            int innerEndX = x + (int)((radius - width) * cos(endAngle * pi / 180.0));
            int innerEndY = y - (int)((radius - width) * sin(endAngle * pi / 180.0));

            // Рисуем сектор цветом фона (вырезаем его)
            // Используем Polygon для заполнения сектора
            POINT sectorPoints[4];
            sectorPoints[0].x = outerStartX;
            sectorPoints[0].y = outerStartY;
            sectorPoints[1].x = outerEndX;
            sectorPoints[1].y = outerEndY;
            sectorPoints[2].x = innerEndX;
            sectorPoints[2].y = innerEndY;
            sectorPoints[3].x = innerStartX;
            sectorPoints[3].y = innerStartY;

            // Заполняем сектор цветом фона
            Polygon(hdc, sectorPoints, 4);
        }

        // Восстановление и удаление объектов
        SelectObject(hdc, hOldBrush);
        SelectObject(hdc, hOldPen);
        DeleteObject(hBrush);
        DeleteObject(hPen);
        DeleteObject(hBrushWhite);
        DeleteObject(hPenWhite);
    }

    // Комплексное перемещение со всеми эффектами
    void flyWithAllEffects(HDC hdc, int cost) {
        show(hdc);
        int xx, yy;
        int moveCount = 0;

        do {
            int startX = x;
            int startY = y;

            // Генерация целевых координат
            do {
                xx = startX + (int)((rand() / (double)RAND_MAX - 0.5) * cost);
            } while (xx > 0 && xx < GetSystemMetrics(SM_CXSCREEN));

            do {
                yy = startY + (int)((rand() / (double)RAND_MAX - 0.5) * cost);
            } while (yy > 0 && yy < GetSystemMetrics(SM_CYSCREEN));

            // Плавная анимация движения с эффектами
            int steps = 15;
            for (int i = 0; i <= steps; i++) {
                hide(hdc);

                // Интерполяция координат
                x = startX + (xx - startX) * i / steps;
                y = startY + (yy - startY) * i / steps;

                // Применяем эффекты на определенных шагах
                if (i % 3 == 0) {
                    if (colorChanging) changeColor();
                    if (radiusChanging) changeRadius();
                    if (widthChanging) changeWidth();
                    if (angleChanging) changeSector();
                }

                show(hdc);
                Sleep(30);
            }

            moveCount++;
        } while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000));
    }

    // Упрощенный метод для демонстрации всех эффектов
    void flyWithSimpleEffects(HDC hdc, int cost) {
        show(hdc);
        int xx, yy;
        int moveCount = 0;

        do {
            locat(xx, yy);

            do {
                xx = xx + (int)((rand() / (double)RAND_MAX - 0.5) * cost);
            } while (xx > 0 && xx < GetSystemMetrics(SM_CXSCREEN));

            do {
                yy = yy + (int)((rand() / (double)RAND_MAX - 0.5) * cost);
            } while (yy > 0 && yy < GetSystemMetrics(SM_CYSCREEN));

            hide(hdc);
            x = xx;
            y = yy;

            // Применяем все эффекты одновременно
            if (colorChanging) changeColor();
            if (radiusChanging) changeRadius();
            if (widthChanging) changeWidth();
            if (angleChanging) changeSector();

            moveCount++;
            show(hdc);

            Sleep(250);
        } while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000));
    }
};

// Обновленная оконная процедура для демонстрации новых функций
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static Krug testKrug;
    static Ring testRing;
    static bool initialized = false;

    switch (message) {
    case WM_CREATE:
        srand(time(NULL));
        initialized = true;

        // Инициализация круга с включенными эффектами
        testKrug.init(150, 40, 50, RGB(255, 0, 0));
        testKrug.enableColorChanging(true);
        testKrug.enableRadiusChanging(true);
        testKrug.setRadiusRange(20, 80, 3);

        // Инициализация кольца со всеми эффектами
        testRing.init(450, 80, 90, RGB(0, 0, 255), 15);
        testRing.enableColorChanging(true);
        testRing.enableRadiusChanging(true);
        testRing.enableWidthChanging(true);
        testRing.enableSectorChanging(true);
        testRing.setSector(0, 120, 10);
        testRing.setRadiusRange(50, 120, 4);
        break;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // Рисуем инструкции
        HFONT hFont = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial");
        HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
        SetTextColor(hdc, RGB(0, 0, 0));

        TextOut(hdc, 10, 10, L"Управление:", 10);
        TextOut(hdc, 10, 40, L"1 - Движение круга с эффектами", 30);
        TextOut(hdc, 10, 70, L"2 - Движение кольца со всеми эффектами", 37);
        TextOut(hdc, 10, 100, L"3 - Простое движение кольца", 27);
        TextOut(hdc, 10, 130, L"ESC - Выход из режима движения", 29);

        SelectObject(hdc, hOldFont);
        DeleteObject(hFont);

        if (initialized) {
            testKrug.show(hdc);
            testRing.show(hdc);
        }

        EndPaint(hWnd, &ps);
        break;
    }

    case WM_KEYDOWN:
        if (wParam == '1') {
            // Круг с эффектами изменения цвета и радиуса
            HDC hdc = GetDC(hWnd);
            testKrug.flyWithEffects(hdc, 100);
            ReleaseDC(hWnd, hdc);
            InvalidateRect(hWnd, NULL, TRUE);
        }
        else if (wParam == '2') {
            // Кольцо со всеми эффектами
            HDC hdc = GetDC(hWnd);
            testRing.flyWithAllEffects(hdc, 120);
            ReleaseDC(hWnd, hdc);
            InvalidateRect(hWnd, NULL, TRUE);
        }
        else if (wParam == '3') {
            // Кольцо с простыми эффектами
            HDC hdc = GetDC(hWnd);
            testRing.flyWithSimpleEffects(hdc, 80);
            ReleaseDC(hWnd, hdc);
            InvalidateRect(hWnd, NULL, TRUE);
        }
        else if (wParam == VK_SPACE) {
            // Простое движение круга (оригинальный функционал)
            HDC hdc = GetDC(hWnd);
            testKrug.fly(hdc, 100);
            ReleaseDC(hWnd, hdc);
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"EnhancedObjectMoveWindow";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    HWND hWnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Движущиеся объекты с эффектами - 1,2,3 для разных режимов",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 850, 700,
        NULL, NULL, hInstance, NULL
    );

    if (hWnd == NULL) return 0;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
