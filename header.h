#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <iostream>
#include <windows.h>

using namespace std;

// Berpindah sesuai dengan koordinat (x, y)
void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Efek slow / memperlambat
void slow()
{
  float a = 1;
  do
  {
    a = a + 0.1;
  } while (a < 1000000);
}

// Membersihkan seluruh cmd
void clearCMD()
{
  system("cls");
}

// Membuat / mengkosongkan arena
void clearArena()
{
  for (int i = 1; i <= 75; i++)
  {
    for (int j = 1; j <= 25; j++)
    {
      gotoxy(i, j);
      cout << " ";
    }
  }
}

/*
  Untuk membuat menu permainan
  (key binds, score, timer)
*/
void printMenu()
{
  // Sudut kiri Atas
  gotoxy(0, 0);
  printf("%c", 201);

  // Sudut Kiri Bawah
  gotoxy(0, 26);
  printf("%c", 200);

  // Sudut Kanan Atas
  gotoxy(92, 0);
  printf("%c", 187);

  // Sudut Kanan Bawah
  gotoxy(92, 26);
  printf("%c", 188);

  for (int x = 1; x <= 91; x++)
  {
    gotoxy(x, 0);
    printf("%c", 205);
    gotoxy(x, 26);
    printf("%c", 205);
  }

  for (int x = 77; x <= 91; x++)
  {
    gotoxy(x, 3);
    printf("%c", 205);
    gotoxy(x, 8);
    printf("%c", 205);
    gotoxy(x, 15);
    printf("%c", 205);
    gotoxy(x, 20);
    printf("%c", 205);
    gotoxy(x, 23);
    printf("%c", 205);
  }

  for (int y = 1; y <= 25; y++)
  {
    gotoxy(0, y);
    printf("%c", 186);
    gotoxy(76, y);
    printf("%c", 186);
    gotoxy(92, y);
    printf("%c", 186);
  }

  gotoxy(76, 0);
  printf("%c", 203);
  gotoxy(76, 26);
  printf("%c", 202);
  gotoxy(76, 3);
  printf("%c", 204);
  gotoxy(76, 8);
  printf("%c", 204);
  gotoxy(76, 15);
  printf("%c", 204);
  gotoxy(76, 20);
  printf("%c", 204);
  gotoxy(76, 23);
  printf("%c", 204);
  gotoxy(92, 3);
  printf("%c", 185);
  gotoxy(92, 8);
  printf("%c", 185);
  gotoxy(92, 15);
  printf("%c", 185);
  gotoxy(92, 20);
  printf("%c", 185);
  gotoxy(92, 23);
  printf("%c", 185);

  gotoxy(82, 1);
  printf("TIMER");
  gotoxy(82, 4);
  printf("SCORE");
  gotoxy(81, 6);
  printf("HIGHEST");
  gotoxy(80, 9);
  printf("W  : UP");
  gotoxy(80, 10);
  printf("S  : DOWN");
  gotoxy(80, 11);
  printf("A  : LEFT");
  gotoxy(80, 12);
  printf("D  : RIGHT");
  gotoxy(80, 13);
  printf("P  : PAUSE");
  gotoxy(79, 14);
  printf("ESC : EXIT");
  gotoxy(82, 16);
  printf("ITEMS");
  gotoxy(78, 17);
  printf("S : -- SPEED");
  gotoxy(82, 18);
  printf("ENEMY");
  gotoxy(78, 19);
  printf("2 : 2x SCORE");
  gotoxy(78, 21);
  printf("COOLDOWN ITEM");
  gotoxy(78, 24);
  printf("CREATED BY <%c", 205);
  gotoxy(78, 25);
  printf("%c> maoelanaAs", 205);
}

void loadingScreen()
{
  gotoxy(35, 12);
  printf("Loading");
  for (int i = 0; i < 6; i++)
  {
    if (i < 3)
    {
      gotoxy(37 + i, 13);
      printf("*");
    }
    if (i > 2)
    {
      gotoxy(33 + i, 13);
      printf(" %c", 204);
    }
    Sleep(500);
  }
  gotoxy(35, 12);
  printf("       ");
  gotoxy(37, 13);
  printf("   ");
  gotoxy(35, 13);
  printf("Start!!");
  Sleep(500);
}

// Memberikan koordinat x secara acak
int xAcak()
{
  int x = rand();
  if ((x % 75) < 1)
  {
    return (x % 75) + 1;
  }
  else
  {
    return (x % 75);
  }
}

// Memberikan koordinat y secara acak
int yAcak()
{
  int y = rand();
  if ((y % 25) < 1)
  {
    return (y % 25) + 1;
  }
  else
  {
    return (y % 25);
  }
}

#endif