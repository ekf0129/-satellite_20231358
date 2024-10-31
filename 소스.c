#include <stdio.h>
#include <math.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 20

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    float x, y, w; // 3D ����
} vec3;

typedef struct {
    float m[3][3]; // 3x3 ���
} Matrix3x3;

// ���Ϳ� ��� ����
vec3 MulVec3(vec3 a, Matrix3x3 b) {
    vec3 result;
    result.x = b.m[0][0] * a.x + b.m[0][1] * a.y + b.m[0][2] * a.w;
    result.y = b.m[1][0] * a.x + b.m[1][1] * a.y + b.m[1][2] * a.w;
    result.w = b.m[2][0] * a.x + b.m[2][1] * a.y + b.m[2][2] * a.w;
    return result;
}

// ��� ����
Matrix3x3 MulMatrix(Matrix3x3 a, Matrix3x3 b) {
    Matrix3x3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.m[i][j] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j] + a.m[i][2] * b.m[2][j];
        }
    }
    return result;
}

// ȭ�� �����
void clearScreen() {
    system("cls");
}

// ȭ�� �׸���
void draw(int angleO, int angleDot) {
    clearScreen();

    int pX = WIDTH / 2;
    int pY = HEIGHT / 2;

    // O�� �ʱ� ��ġ (P���� 3��ŭ ������ ��ġ)
    vec3 o = { 0.0f, 3.0f, 1.0f }; // w = 1.0f�� ����

    // .�� �ʱ� ��ġ (O���� 2��ŭ ������ ��ġ)
    vec3 dot = { 0.0f, 2.0f, 1.0f }; // w = 1.0f�� ����

    // ȸ�� ��� ����
    Matrix3x3 rotationO = {
        .m = {
            {cos(angleO * M_PI / 180.0), -sin(angleO * M_PI / 180.0), 0},
            {sin(angleO * M_PI / 180.0), cos(angleO * M_PI / 180.0), 0},
            {0, 0, 1}
        }
    };

    Matrix3x3 rotationDot = {
        .m = {
            {cos(angleDot * M_PI / 180.0), -sin(angleDot * M_PI / 180.0), 0},
            {sin(angleDot * M_PI / 180.0), cos(angleDot * M_PI / 180.0), 0},
            {0, 0, 1}
        }
    };

    // P�� �������� O ȸ��
    o = MulVec3(o, rotationO);
    o.x += pX; // P�� ��ġ �߰�
    o.y += pY;

    // O�� �������� . ȸ��
    dot = MulVec3(dot, rotationDot);
    dot.x += o.x; // O�� ��ġ �߰�
    dot.y += o.y;

    // ȭ�� ���
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == pX && y == pY) {
                printf("P"); // �߽��� ǥ��
            }
            else if ((int)o.x == x && (int)o.y == y) {
                printf("O"); // O ǥ��
            }
            else if ((int)dot.x == x && (int)dot.y == y) {
                printf("."); // . ǥ��
            }
            else {
                printf(" "); // �� ����
            }
        }
        printf("\n");
    }
}

int main() {
    int angleO = 0; // O�� �ʱ� ����
    int angleDot = 0; // .�� �ʱ� ����

    while (1) {
        draw(angleO, angleDot); // ���� ������ ȭ�� �׸���

        angleO += 5; // O�� ���� ����
        angleDot += 10; // .�� ���� ����

        if (angleO >= 360) angleO -= 360; // ���� ���� ����
        if (angleDot >= 360) angleDot -= 360; // ���� ���� ����

        Sleep(100); // 100 �и������� ���
    }

    return 0;
}
