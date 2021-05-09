#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#define n 11

#define n1 0
#define n2 4
#define n3 1
#define n4 1

#define PI 3.14159265359


double** randm()
{
    double** resulting_matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) resulting_matrix[i] = (double*)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            double numbe = 2.0 * rand() / RAND_MAX;
            resulting_matrix[i][j] = numbe;
        }
    }

    return resulting_matrix;
}

int** mulmr(double coefficient, double **matrix)
{
    int** resulting_matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) resulting_matrix[i] = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            double check = matrix[i][j] * coefficient;

            if (check < 1) resulting_matrix[i][j] = 0;
            else resulting_matrix[i][j] = 1;
        }
    }

    return resulting_matrix;
}

void print_matrix(int** matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n"); //transition to a next row
    }
    printf("\n");
}

void free_int_matrix(int** matrix, int size)
{
    for (int i = 0; i < size; i++) free(matrix[i]);
    free(matrix);
}


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

const char ProgName[] = "Laboratorna robota 3";

const int window_width = 1300;
const int window_height = 750;

const int radius = 0.4 * window_height; //radius of the main arrangement

const int r = 16; //radius of a small circle with number
const int shift = 5; //for printing numbers correction


int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszCmdLine,
                   int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;

    WNDCLASS w;

    w.lpszClassName = ProgName; //ім'я програми
    w.hInstance = hInstance; //ідентифікатор застосунку
    w.lpfnWndProc = WndProc; //вказівник на функцію вікна
    w.hCursor = LoadCursor(NULL, IDC_ARROW); //завантажений курсор
    w.hIcon = 0; //піктограми не буде
    w.lpszMenuName = 0; //меню не буде
    w.hbrBackground = WHITE_BRUSH; //колір фона вікна
    w.style = CS_HREDRAW | CS_VREDRAW; //стиль: можна перемальовувати
    w.cbClsExtra = 0; //к-ть додаткових байтів для цього класу
    w.cbWndExtra = 0;

    if (!RegisterClass(&w)) return 0;

    hWnd = CreateWindow(
            ProgName, //Ім'я програми
            "Laboratorna robota 3. Vykonav Kravchenko V. O.", //заголовок
            WS_OVERLAPPEDWINDOW, //стиль вікна - комплексний1
            269, //положення верхнього кута вікна на екрані по х
            0, // положення верхнього кута вікна на екрані по y
            window_width, //ширина вікна
            window_height, //висота вікна
            (HWND)NULL, // ідентифікатор породжуючого вікна
            (HMENU)NULL, //ідентифікатор меню (немає)
            (HINSTANCE)hInstance, //ідентифікатор екземпляра вікна
            (HINSTANCE)NULL
    ); // додаткові параметри відсутні

    ShowWindow(hWnd, nCmdShow);

    while (GetMessage(&lpMsg, hWnd, 0, 0)) // повідомлення з черги
    {
        TranslateMessage(&lpMsg); //перетворення повідомлення у рядок
        DispatchMessage(&lpMsg); //Передача повідомлення до функції вікна
    }

    return (lpMsg.wParam); // кінець основної функції
}

HDC hdc; // контекст
PAINTSTRUCT ps; // екземпляр структури

double nx[n] = {};
double ny[n] = {};

double get_angle(int i, int j)
{
    COORD some_vector;
    some_vector.X = nx[i] - nx[j];
    some_vector.Y = ny[i] - ny[j];

    COORD radius_vector; //radius vector of the Ox axis
    radius_vector.X = 1;
    radius_vector.Y = 0;

    double some_vector_len = sqrt(some_vector.X * some_vector.X + some_vector.Y * some_vector.Y);
    double radius_vector_len = 1;

    double scalar_product = some_vector.X * radius_vector.X + some_vector.Y * radius_vector.Y;
    double cos_angle = scalar_product / (some_vector_len * radius_vector_len);

    double angle = acos(cos_angle);
    if (ny[i] < ny[j]) angle *= -1;

    return angle;
}

void arrow(double fi, double px, double py)
{
    px += r * 0.9 * cos(fi);
    py += r * 0.9 * sin(fi);
    double lx = px + r * 0.9 * cos(fi + 0.3);
    double rx = px + r * 0.9 * cos(fi - 0.3);
    double ly = py + r * 0.9 * sin(fi + 0.3);
    double ry = py + r * 0.9 * sin(fi - 0.3);

    MoveToEx(hdc, lx, ly, NULL);
    LineTo(hdc, px, py);
    LineTo(hdc, rx, ry);
}

void line(int i, int j)
{
    double fi = get_angle(i, j);

    MoveToEx(
            hdc,
             nx[i] - r * 0.9 * cos(fi),
             ny[i] - r * 0.9 * sin(fi),
             NULL
    );
    LineTo(
            hdc,
           nx[j] + r * 0.9 * cos(fi),
           ny[j] + r * 0.9 * sin(fi)
    );

    arrow(fi, nx[j], ny[j]);
}

void loop(int j)
{
    int x_sign = 1;
    int y_sign = 1;
    if (nx[j] - window_width / 2 <= 0) x_sign = -1;
    if (ny[j] - window_height / 2 <= 0) y_sign = -1;

    Arc (hdc, nx[j], ny[j], nx[j] + x_sign * 40, ny[j] + y_sign * 40, nx[j], ny[j], nx[j], ny[j]);

    if (x_sign == 1 && y_sign == -1) arrow(-0.15, nx[j], ny[j] + 3);
    if (x_sign == -1 && y_sign == -1) arrow(4.6, nx[j] + 3, ny[j]);
    if (x_sign == -1 && y_sign == 1) arrow(3, nx[j], ny[j] - 3);
    if (x_sign == 1 && y_sign == 1) arrow(1.5, nx[j] - 3, ny[j]);
}

void offset_line(int i, int j)
{
    double angle = get_angle(i, j);

    double distance = 15;
    double dx1 = nx[i] - distance * cos(angle - PI / 8);
    double dy1 = ny[i] - distance * sin(angle - PI / 8);
    double dx2 = nx[j] + distance * cos(angle + PI / 8);
    double dy2 = ny[j] + distance * sin(angle + PI / 8);

    MoveToEx(hdc, dx1, dy1, NULL);
    LineTo(hdc, dx2, dy2);
    arrow(angle, dx2 - 15 * cos(angle), dy2 - 15 * sin(angle));
}

void draw_graph(HWND hWnd, int** matrix, int radius, int x_center, int y_center)
{
    for (int j = 0; j < n; j++)
    {
        nx[j] = cos(2 * PI * j / n) * radius + x_center;
    }
    for (int j = 0; j < n; j++)
    {
        ny[j] = sin(2 * PI * j / n) * radius + y_center;
    }

    HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
    HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

    SelectObject(hdc, KPen);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == 1)
            {
                if (i == j) loop(i);
                else
                {
                    if (matrix[j][i] == 1 && i > j) offset_line(i, j);
                    else line(i, j);
                }
            }
        }
    }

    SelectObject(hdc, BPen);
    for (int i = 0; i < n; i++)
    {
        Ellipse(hdc, nx[i] - r, ny[i] - r, nx[i] + r, ny[i] + r);
        char* nn = malloc(2 * sizeof(char*));
        sprintf(nn, "%d", i + 1);
        TextOut(hdc, nx[i] - shift, ny[i] - r / 2, nn, 2);
        free(nn);
    }
}

void recolor_vertex(HWND hWnd, int vertex, int R, int G, int B)
{
    int x = nx[vertex];
    int y = ny[vertex];

    HPEN myPen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
    SelectObject(hdc, myPen);

    Ellipse(
            hdc,
            x - r,
            y - r,
            x + r,
            y + r
    );
    char* nn = malloc(2 * sizeof(char*));
    sprintf(nn, "%d", vertex + 1);
    TextOut(
            hdc,
            x - shift,
            y - r / 2,
            nn,
            2
    );
    free(nn);
}

void highlight_connection(HWND hWnd, int first_vertex, int second_vertex)
{
    HPEN GPen = CreatePen(PS_SOLID, 1, RGB(200, 200, 100));
    SelectObject(hdc, GPen);

    line(first_vertex, second_vertex);
}


struct Node
{
    int data;
    struct Node* next; // Pointer to next node in DLL
    struct Node* prev; // Pointer to previous node in DLL
};

/*void free_list_memory_recursive(struct Node* element)
{
    if (element->next != NULL) free_list_memory_recursive(element->next);
    free(element);
}

void free_list_memory(struct Node* element)
{
    while (element->prev) element = element->prev;
    free_list_memory_recursive(element);
}*/

void add(struct Node** head_ref, int new_data)
{
    //allocate node
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    //put in the data
    new_node->data = new_data;

    //Make next of new node as head and previous as NULL
    new_node->next = (*head_ref);
    new_node->prev = NULL;

    //change prev of head node to new node
    if ((*head_ref) != NULL) (*head_ref)->prev = new_node;

    // move the head to point to the new node
    (*head_ref) = new_node;
}

void add_without_headshift(struct Node** head_ref, int new_data)
{
    struct Node* last_node = (struct Node*)malloc(sizeof(struct Node));
    if ((*head_ref)->prev) last_node = (*head_ref)->prev;
    else last_node = (*head_ref);
    while (last_node->prev) last_node = last_node->prev;

    //allocate node
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    //put in the data
    new_node->data = new_data;

    //Make next of new node as head and previous as NULL
    new_node->next = last_node;
    new_node->prev = NULL;

    //change prev of head node to new node
    last_node->prev = new_node;

    //free(last_node);
}

int detect_element_in_array(int* array, int arr_length, int desired)
{
    for (int i = 0; i < arr_length; i++)
    {
        if (array[i] == desired) return 1;
    }
    return 0;
}

int detect_element_in_list(struct Node* element, int desired)
{
    struct Node* node;
    if (element->next != NULL) node = element->next;
    else node = element;
    while (node->next) node = node->next;

    while (node != NULL)
    {
        if (node->data == desired)
        {
            printf("element %d deteceted in the queue\n\n", desired + 1);
            return 1;
        }
        node = node->prev;
    }

    printf("element %d not detected in the queue\n", desired + 1);
    free(node);
    return 0;
}


int** breadth_first_search(HWND hWnd, int **matrix)
{
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
    printf("\nbfs started, \n");

    int output[n] = {};
    struct Node* my_queue = NULL;
    int visited[n] = {};

    int** search_tree = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) search_tree[i] = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            search_tree[i][j] = 0;
        }
    }

    output[0] = 0;
    add(&my_queue, 0); // ads 0 vertex to the queue
    visited[0] = 0;

    if (my_queue == NULL) printf("ffffffffuck\n\n");

    int noe = 1; //number of output elements
    for (int counter = 0; my_queue != NULL; counter++)
    {
        if (MessageBox(
                hWnd,
                "click to advance",
                "BUTTON",
                MB_OK))
        {

            SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),
                                    FOREGROUND_GREEN | FOREGROUND_RED);
            printf("\nexamined vertex is %d\n", my_queue->data + 1);
            SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),
                                    FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

            recolor_vertex(hWnd, my_queue->data, 200, 200, 100);
            if (my_queue->next != NULL) recolor_vertex(hWnd, my_queue->next->data, 100, 100, 100);
        }
        for (int j = 0; j < n; j++)
        {
            if (
                    matrix[my_queue->data][j] == 1
                    && !detect_element_in_list(my_queue, j)
            )
            {
                add_without_headshift(&my_queue, j);

                highlight_connection(hWnd, my_queue->data, j);

                output[noe] = j;
                search_tree[my_queue->data][j] = 1;
                noe++;

                //printf("value is %d, so ", matrix[my_queue->data][j] == 1);
                printf("element %d added\n\n", j + 1);
            }
        }
        my_queue = my_queue->prev;
    }

    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
    printf("\nbfs output: ");
    for (int i = 0; i < n; i++)
    {
        printf(" %d ", output[i] + 1);
    }

    return search_tree;
}

int** depth_first_search(HWND hWnd, int **matrix)
{
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),
                            FOREGROUND_GREEN);
    printf("\n\ndfs started, \n");

    int** search_tree = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) search_tree[i] = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            search_tree[i][j] = 0;
        }
    }

    int output[n] = {};
    struct Node* my_stack = NULL;
    int visited[n] = {};

    output[0] = 0;
    add(&my_stack, 0); // ads 0 vertex to the queue
    visited[0] = 0;

    if (my_stack == NULL) printf("ffffffffuck\n\n");

    int noe = 1; //number of output elements
    for (int counter = 0; my_stack != NULL; counter++)
    {
        if (MessageBox(
                hWnd,
                "click to advance",
                "BUTTON",
                MB_OK))
        {
            SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),
                                    FOREGROUND_GREEN  | FOREGROUND_RED);
            printf("\nexamined vertex is %d\n", my_stack->data + 1);
            SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),
                                    FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

            if (my_stack->prev == NULL)
            {
                recolor_vertex(hWnd, my_stack->data, 200, 200, 100);
                if (my_stack->next != NULL) recolor_vertex(hWnd, my_stack->next->data, 100, 100, 100);
            }
            else
            {
                recolor_vertex(hWnd, my_stack->data, 6, 200, 9);
                recolor_vertex(hWnd, my_stack->prev->data, 100, 100, 100);
            }
        }
        for (int j = 0; j < n; j++)
        {
            if (
                    matrix[my_stack->data][j] == 1
                    && !detect_element_in_array(output, n, j)
            )
            {
                highlight_connection(hWnd, my_stack->data, j);
                search_tree[my_stack->data][j] = 1;

                add(&my_stack, j);

                output[noe] = j;
                noe++;

                //printf("value is %d, so ", matrix[my_queue->data][j] == 1);
                printf("element %d added\n", j + 1);

                //my_stack = my_stack->prev;
                break;
            }
            else if(j == n - 1) my_stack = my_stack->next;
        }
    }

    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
    printf("\ndfs output: ");
    for (int i = 0; i < n; i++)
    {
        printf(" %d ", output[i] + 1);
    }
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),
                            BACKGROUND_BLUE & BACKGROUND_GREEN & BACKGROUND_RED
                            | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    //free_list_memory(my_stack);

    return search_tree;
}


LRESULT CALLBACK WndProc(
        HWND hWnd,
        UINT messg,
        WPARAM wParam,
        LPARAM lParam
)
{
    switch(messg)
    {
        case WM_PAINT:
            //main
            srand(1000 * n1 + 100 * n2 + 10 * n3 + n4);

            double** T = randm();
            int** A;
            A = mulmr(( 1.0 - n3 * 0.01 - n4 * 0.005 - 0.15), T);

            printf("adjacency matrix is:\n");
            print_matrix(A, n);

            hdc = BeginPaint(hWnd, &ps);
            draw_graph(hWnd, A, radius, window_width / 3, window_height / 2);

            //depth_first_search(hWnd, A);
            draw_graph(
                    hWnd,
                    breadth_first_search(hWnd, A),
                    radius * 0.45,
                    window_width * 0.77,
                    window_height * 0.25
            );
            TextOut(
                    hdc,
                    window_width * 0.77 - radius * 0.45,
                    window_height * 0.25 - radius * 0.45,
                    "BFS:",
                    4
            );

            //reset graph outlook
            draw_graph(hWnd, A, radius, window_width / 3, window_height / 2);

            //depth_first_search(hWnd, A);
            draw_graph(
                    hWnd,
                    depth_first_search(hWnd, A),
                    radius * 0.45,
                    window_width * 0.77,
                    window_height * 0.7
            );
            TextOut(
                    hdc,
                    window_width * 0.77 - radius * 0.45,
                    window_height * 0.7 - radius * 0.45,
                    "DFS:",
                    4
            );

            for (int i = 0; i < n; i++) free(T[i]);
            free(T);

            for (int i = 0; i < n; i++) free(A[i]);
            free(A);

            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return (DefWindowProc(hWnd, messg, wParam, lParam));
    }
}
