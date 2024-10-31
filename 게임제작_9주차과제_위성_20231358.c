#include <stdio.h>
#include <math.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 20

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    float x, y, w; // 3D 벡터
} vec3;

typedef struct {
    float m[3][3]; // 3x3 행렬
} Matrix3x3;

// 벡터와 행렬 곱셈
vec3 MulVec3(vec3 a, Matrix3x3 b) {
    vec3 result;
    result.x = b.m[0][0] * a.x + b.m[0][1] * a.y + b.m[0][2] * a.w;
    result.y = b.m[1][0] * a.x + b.m[1][1] * a.y + b.m[1][2] * a.w;
    result.w = b.m[2][0] * a.x + b.m[2][1] * a.y + b.m[2][2] * a.w;
    return result;
}

// 행렬 곱셈
Matrix3x3 MulMatrix(Matrix3x3 a, Matrix3x3 b) {
    Matrix3x3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.m[i][j] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j] + a.m[i][2] * b.m[2][j];
        }
    }
    return result;
}

// 화면 지우기
void clearScreen() {
    system("cls");
}

// 화면 그리기
void draw(int angleO, int angleDot) {
    clearScreen();

    int pX = WIDTH / 2;
    int pY = HEIGHT / 2;

    // O의 초기 위치 (P에서 3만큼 떨어진 위치)
    vec3 o = { 0.0f, 3.0f, 1.0f }; // w = 1.0f로 설정

    // .의 초기 위치 (O에서 2만큼 떨어진 위치)
    vec3 dot = { 0.0f, 2.0f, 1.0f }; // w = 1.0f로 설정

    // 회전 행렬 생성
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

    // P를 기준으로 O 회전
    o = MulVec3(o, rotationO);
    o.x += pX; // P의 위치 추가
    o.y += pY;

    // O를 기준으로 . 회전
    dot = MulVec3(dot, rotationDot);
    dot.x += o.x; // O의 위치 추가
    dot.y += o.y;

    // 화면 출력
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == pX && y == pY) {
                printf("P"); // 중심점 표시
            }
            else if ((int)o.x == x && (int)o.y == y) {
                printf("O"); // O 표시
            }
            else if ((int)dot.x == x && (int)dot.y == y) {
                printf("."); // . 표시
            }
            else {
                printf(" "); // 빈 공간
            }
        }
        printf("\n");
    }
}

int main() {
    int angleO = 0; // O의 초기 각도
    int angleDot = 0; // .의 초기 각도

    while (1) {
        draw(angleO, angleDot); // 현재 각도로 화면 그리기

        angleO += 5; // O의 각도 증가
        angleDot += 10; // .의 각도 증가

        if (angleO >= 360) angleO -= 360; // 각도 범위 조정
        if (angleDot >= 360) angleDot -= 360; // 각도 범위 조정

        Sleep(100); // 100 밀리세컨드 대기
    }

    return 0;
}
