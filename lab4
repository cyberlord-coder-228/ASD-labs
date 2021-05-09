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

int** mirror_matrix(int** matrix)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (
                    matrix[i][j] == 1
                    && matrix[j][i] != 1
                    && i != j
                    )
            {
                matrix[j][i] = 1;
            }
        }
    }

    return matrix;
}

void print_matrix(int** matrix)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n"); //transition to a next row
    }
    printf("\n");
}

void free_int_matrix(int** matrix)
{
    for (int i = 0; i < n; i++) free(matrix[i]);
    free(matrix);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

const char ProgName[] = "Laboratorna robota 3";

const int window_width = 1000;
const int window_height = 850;

const int radius = 340; //radius of the main arrangement

const int r = 16; //radius of a small circle with number
const int shift = 5; //for a printing numbers correction

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

    hWnd = CreateWindow(ProgName, //Ім'я програми
                        "Laboratorna robota 3. Vykonav Kravchenko V. O.", //заголовок
                        WS_OVERLAPPEDWINDOW, //стиль вікна - комплексний1
                        420, //положення верхнього кута вікна на екрані по х
                        0, // положення верхнього кута вікна на екрані по y
                        window_width, //ширина вікна
                        window_height, //висота вікна
                        (HWND)NULL, // ідентифікатор породжуючого вікна
                        (HMENU)NULL, //ідентифікатор меню (немає)
                        (HINSTANCE)hInstance, //ідентифікатор екземпляра вікна
                        (HINSTANCE)NULL); // додаткові параметри відсутні

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

void line(int i, int j)
{
    MoveToEx(hdc, nx[i], ny[i], NULL);
    LineTo(hdc, nx[j], ny[j]);
}

void loop(int j)
{
    int x_sign = 1;
    int y_sign = 1;
    if (nx[j] - window_width / 2 <= 0) x_sign = -1;
    if (ny[j] - window_height / 2 <= 0) y_sign = -1;

    Arc (hdc, nx[j], ny[j], nx[j] + x_sign * 40, ny[j] + y_sign * 40, nx[j], ny[j], nx[j], ny[j]);
}

void draw_graph(HWND hWnd, int** matrix, int size)
{
    hdc = BeginPaint(hWnd, &ps);

    for (int j = 0; j < n; j++)
    {
        nx[j] = cos(2 * PI * j / n) * radius + window_width / 2;
    }
    for (int j = 0; j < n; j++)
    {
        ny[j] = sin(2 * PI * j / n) * radius + window_height / 2;
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
                else line(i, j);
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

    EndPaint(hWnd, &ps);
}


int** find_degs_directed(int** matrix)
{
    int** result = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < 2; i++) result[i] = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        int deg_i_plus = 0;
        int deg_i_minus = 0;
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == 1) deg_i_plus++;
            if (matrix[j][i] == 1) deg_i_minus++;
        }
        //if (matrix[i][i] == 1) deg_i_plus++;
        printf("deg%d+ == %d\t", i + 1, deg_i_plus);
        result[0][i] = deg_i_plus;
        printf("deg%d- == %d\n", i + 1, deg_i_minus);
        result[1][i] = deg_i_minus;
    }
    return result;
}

int* find_degs_undirected(int** matrix)
{
    int* result = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        int deg_i = 0;
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == 1) deg_i++;
        }
        if (matrix[i][i] == 1) deg_i++;
        printf("deg%d == %d\n", i + 1, deg_i);
        result[i] = deg_i;
    }
    return result;
}

void determine_if_homogenous_directed(int** matrix_of_degs)
{
    for (int i = 0; i < n - 1; i++)
    {
        if(matrix_of_degs[0][i] != matrix_of_degs[0][i+1])
        {
            printf("\ngraf isnt homogenous\n");
            return;
        }
        if(matrix_of_degs[1][i] != matrix_of_degs[1][i+1])
        {
            printf(
                    "\ngraf isnt homogenous, plus deg is %d, minus deg is %d\n",
                    matrix_of_degs[0][0],
                    matrix_of_degs[1][0]
                   );
            return;
        }
    }
    printf("\ngraf is homogenous\n");
}

void determine_if_homogenous_undirected(int* list_of_degs)
{
    for (int i = 0; i < n - 1; i++)
    {
        if(list_of_degs[i] != list_of_degs[i+1])
        {
            printf("\ngraf isnt homogenous\n");
            return;
        }
    }
    printf("\ngraf is homogenous, deg is %d \n", list_of_degs[0]);
}

void find_dangling_edges_and_isolated_vertices_directed(int** matrix_of_degs)
{
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        if (matrix_of_degs[0][i] == 0 && matrix_of_degs[1][i] == 0)
            printf("\nvertice %d is an isolated vertice\n", i + 1);
        if (
                (matrix_of_degs[0][i] == 1 && matrix_of_degs[1][i] == 0)
                || (matrix_of_degs[1][i] == 1 && matrix_of_degs[0][i] == 0)
            )
            printf("\nvertice %d is a danling edge\n", i + 1);
    }
}

void find_dangling_edges_and_isolated_vertices_undirected(int* list_of_degs)
{
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        if (list_of_degs[i] == 0)  printf("vertice %d is an isolated vertice\n", i + 1);
        if (list_of_degs[i] == 1)  printf("vertice %d is a danling edge\n", i + 1);

    }
}

int** find_pathlength_two(int** matrix)
{
    int** result = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) result[i] = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            result[i][j] = 0;
        }
    }

    for (int vertex = 0; vertex < n; vertex++)
    {
        for(int i = 0; i < n; i++)
        {
            if (matrix[vertex][i] == 1)
            {
                for(int j = 0; j < n; j++)
                {
                    if (matrix[i][j] == 1)
                    {
                        result[vertex][j] = 1;
                    }
                }
            }
        }
    }

    return result;
}

void print_paths_two_and_three(int** original_matrix)
{
    for (int a = 0; a < n; a++)
    {
        for (int b = 0; b < n; b++)
        {
            if (original_matrix[a][b] == 1)
            {
                for (int c = 0; c < n; c++)
                {
                    if(original_matrix[b][c] == 1)
                    {
                        printf("%d->%d->%d    ", a + 1, b + 1, c + 1);
                        for (int d = 0; d < n; d++)
                        {
                            if(original_matrix[c][d] == 1) printf("%d->%d->%d->%d    ", a + 1, b + 1, c + 1, d + 1);
                        }
                    }
                }
            }
        }
    }
}

int** reachability_matrix(int** matrix)
{
    int** result = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) result[i] = (int*)malloc(n * sizeof(int));

    int** matrix_of_last_pathlength = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) matrix_of_last_pathlength[i] = (int*)malloc(n * sizeof(int));

    for (int raffaello = 0; raffaello < n - 1; raffaello++)
    {
        if (raffaello == 0)
        {
            matrix_of_last_pathlength = matrix;
        }
        else
        {
            matrix_of_last_pathlength = find_pathlength_two(matrix_of_last_pathlength);
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                result[i][j] = 0;
                if (result[i][j] != 1 && matrix_of_last_pathlength[i][j] == 1)
                    result[i][j] = 1;
            }
        }
    }

    return result;
}

int** connectivity_matrix(int** reachability_matrix)
{
    int** result = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) result[i] = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (reachability_matrix[i][j] != reachability_matrix[j][i])
            {
                result[i][j] = 0;
                result[j][i] = 0;
            }
            else
            {
                result[i][j] = reachability_matrix[i][j];
                result[j][i] = reachability_matrix[j][i];
            }
        }
    }

    return result;
}

int compare_rows(int* row_1, int* row_2)
{
    for (int i = 0; i < n; i++)
    {
        if (row_1[i] != row_2[i]) return 0;
    }
    return 1;
}

int check_for_unique(int* row)
{
    for (int i = 0; i < n; i++)
    {
        if (row[i] == -1) return i;
        else if (row[i] == -5) return -3;
    }
    return -3;
}

int** create_and_print_condense_matrix(int** unq_groups, int num_of_unq_groups, int** reach_matrix)
{
    int** cond_matrix = (int**)malloc(num_of_unq_groups * sizeof(int*));
    for (int i = 0; i < num_of_unq_groups; i++) cond_matrix[i] = (int*)malloc(num_of_unq_groups * sizeof(int));

    for (int i = 0; i < num_of_unq_groups; i++)
    {
        for (int j = 0; j < num_of_unq_groups; j++)
        {
            cond_matrix[i][j] = 0;
        }
    }

    for (int K = 0; K < num_of_unq_groups - 1; K++)
    {
        for (int counter = 0; counter < num_of_unq_groups - 1; counter++)
        {
            int i = -1;
            for (int c = 0; i < 0; c++) i = unq_groups[counter][c];
            int j = -1;
            for (int c = 0; j < 0; c++) j = unq_groups[counter + 1][c];

            if (reach_matrix[unq_groups[counter][i]][unq_groups[counter + 1][j]] == 1)
            {
                cond_matrix[K][K + counter + 1] = 1;
            }
            else
            {
                cond_matrix[K + counter + 1][K] = 1;
            }
        }
    }

    printf("condense matrix is:\n");
    for (int i = 0; i < num_of_unq_groups; i++)
    {
        for (int j = 0; j < num_of_unq_groups; j++)
        {
            printf("%d ", cond_matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    return cond_matrix;
}

int** find_condense_matrix_and_print_graph(HWND hWnd, int** conn_matrix, int** reach_matrix)
{
    int** result_matrix = (int**)malloc(n * sizeof(int*));
    result_matrix[0] = (int*)malloc(n * sizeof(int));
    result_matrix[0][0] = 0;

    int nug = 1; //number_of_unique_groups

    for (int counter = 0; ; )
    {
        for (int i = 0; i < n; i++)
        {
            if (compare_rows(conn_matrix[counter], conn_matrix[i]) == 1)
                result_matrix[nug - 1][i] = i;
            else
            {
                if (nug == 1) result_matrix[nug - 1][i] = -1;
                else
                {
                    if (result_matrix[nug - 2][i] == -1) result_matrix[nug - 1][i] = -1;
                    else result_matrix[nug - 1][i] = -5;
                }
            }
        }

        int check = check_for_unique(result_matrix[nug - 1]);
        if (check == -3) //there are no other unique rows
        {
            printf("groups of unique rows:\n");
            for (int i = 0; i < nug; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (result_matrix[i][j] >= 0) printf("%d ", result_matrix[i][j]);
                }
                printf("\n");
            }
            printf("\n");

            int** cond_matrix = create_and_print_condense_matrix(result_matrix, nug, reach_matrix);
            if (hWnd) draw_graph(hWnd, cond_matrix, nug);
            return cond_matrix;
        }
        else //continue finding unique groups
        {
            nug++;
            result_matrix[nug - 1] = (int*)malloc(n * sizeof(int));
            counter = check;
        }
    }
}

void analyze_graph(HWND hWnd, int** matrix)
{
    int** A2; //matrix of power 2
    int** A3; //matrix of power 3
    int** R;  //reachability matrix
    int** C;  //connectivity matrix
    int** condense_matrix;

    printf("Directed adjacency matrix:\n\n");
    print_matrix(matrix);

    //first row is a list of plus degs, second row is a list of minus degs
    int** lists_of_degs = find_degs_directed(matrix);
    determine_if_homogenous_directed(lists_of_degs);
    find_dangling_edges_and_isolated_vertices_directed(lists_of_degs);

    A2 = find_pathlength_two(matrix);
    A3 = find_pathlength_two(A2);
    printf("\npath-lengths of 2 of directed matrix:\n");
    print_matrix(A2);
    free_int_matrix(A2);
    printf("path-lengths of 3 of directed matrix:\n");
    print_matrix(A3);
    free_int_matrix(A3);
    print_paths_two_and_three(matrix);


    printf("\nreachability matrix:\n");
    R = reachability_matrix(matrix);
    print_matrix(R);

    printf("connectivity matrix:\n");
    C = connectivity_matrix(R);
    print_matrix(C);

    //printf("groups of unique rows:\n");
    condense_matrix = find_condense_matrix_and_print_graph(hWnd, C, R);

    free_int_matrix(R);
    free_int_matrix(C);

    matrix = mirror_matrix(matrix);

    printf("\n\nUndirected adjacency matrix:\n\n", n, n);
    print_matrix(matrix);

    int* list_of_degs = find_degs_undirected(matrix);
    determine_if_homogenous_undirected(list_of_degs);
    find_dangling_edges_and_isolated_vertices_undirected(list_of_degs);

    A2 = find_pathlength_two(matrix);
    A3 = find_pathlength_two(A2);
    printf("\npath-lengths of 2 of undirected matrix:\n");
    print_matrix(A2);
    printf("\npath-lengths of 3 of undirected matrix:\n");
    print_matrix(A3);
    print_paths_two_and_three(matrix);

    /*
    printf("\nreachability matrix:\n");
    R = reachability_matrix(matrix);
    print_matrix(R);
    printf("connectivity matrix:\n");
    C = connectivity_matrix(R);
    print_matrix(C);
    printf("groups of unique rows:\n");
    condense_matrix = find_condense_matrix(C);
     */

    free_int_matrix(R);
    free_int_matrix(C);
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
            //first matrix
            printf("First graph:\n\n");
            A = mulmr((1.0 - n3 * 0.01 - n4 * 0.01 - 0.3), T);
            //draw_graph(hWnd, A, n);
            analyze_graph(NULL, A);
            //draw_graph(hWnd, A, n);

            //second matrix
            printf("\n\nSecond graph:\n\n");
            A = mulmr((1.0 - n3 * 0.005 - n4 * 0.005 - 0.27), T);
            analyze_graph(NULL, A);
            draw_graph(hWnd, A, n);

            for (int i = 0; i < n; i++) free(T[i]);
            free(T);

            //draw_graph(hWnd, A, n);

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
