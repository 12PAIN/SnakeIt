#pragma once
class clTetris {

public:
    void Tetris(int WIDTH, int HEIGHT);
private:

    static const int M = 20; // ������ �������� ����
    static const int N = 10; // ������ �������� ����

    //���������� ����� ����
    int field[M][N] = { 0 };
    bool beginGame_1;

    int figures[7][4] =
    {
        1,3,5,7, // I
        2,4,5,7, // S
        3,5,4,6, // Z
        3,5,4,7, // T
        2,3,5,7, // L
        3,5,7,6, // J
        2,3,4,5, // O
    };

    //��������� ��� ������ ������ � ���������������� ���������
    struct Point
    {
        int x, y;
    } a[4], b[4];


    //������� �������� ��������� �� ����
    bool gameOver();

    //������� �������� ������ �� ������� ����
    bool check();

};