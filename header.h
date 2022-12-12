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
  for (int i = 2; i <= 76; i++)
  {
    for (int j = 2; j <= 26; j++)
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
  gotoxy(1, 1);
  printf("%c", 201);

  // Sudut Kiri Bawah
  gotoxy(1, 27);
  printf("%c", 200);

  // Sudut Kanan Atas
  gotoxy(93, 1);
  printf("%c", 187);

  // Sudut Kanan Bawah
  gotoxy(93, 27);
  printf("%c", 188);

  for (int x = 2; x <= 92; x++)
  {
    gotoxy(x, 1);
    printf("%c", 205);
    gotoxy(x, 27);
    printf("%c", 205);
  }

  for (int x = 78; x <= 92; x++)
  {
    gotoxy(x, 4);
    printf("%c", 205);
    gotoxy(x, 9);
    printf("%c", 205);
    gotoxy(x, 15);
    printf("%c", 205);
    gotoxy(x, 20);
    printf("%c", 205);
    gotoxy(x, 23);
    printf("%c", 205);
  }

  for (int y = 2; y <= 26; y++)
  {
    gotoxy(1, y);
    printf("%c", 186);
    gotoxy(77, y);
    printf("%c", 186);
    gotoxy(93, y);
    printf("%c", 186);
  }

  gotoxy(77, 1);
  printf("%c", 203);
  gotoxy(77, 27);
  printf("%c", 202);
  gotoxy(77, 4);
  printf("%c", 204);
  gotoxy(77, 9);
  printf("%c", 204);
  gotoxy(77, 15);
  printf("%c", 204);
  gotoxy(77, 20);
  printf("%c", 204);
  gotoxy(77, 23);
  printf("%c", 204);
  gotoxy(93, 4);
  printf("%c", 185);
  gotoxy(93, 9);
  printf("%c", 185);
  gotoxy(93, 15);
  printf("%c", 185);
  gotoxy(93, 20);
  printf("%c", 185);
  gotoxy(93, 23);
  printf("%c", 185);

  gotoxy(83, 2);
  printf("TIMER");
  gotoxy(83, 5);
  printf("SCORE");
  gotoxy(82, 7);
  printf("HIGHEST");
  gotoxy(81, 10);
  printf("W  : UP");
  gotoxy(81, 11);
  printf("S  : DOWN");
  gotoxy(81, 12);
  printf("A  : LEFT");
  gotoxy(81, 13);
  printf("D  : RIGHT");
  gotoxy(80, 14);
  printf("ESC : EXIT");
  gotoxy(83, 16);
  printf("ITEMS");
  gotoxy(79, 17);
  printf("S : -- SPEED");
  gotoxy(83, 18);
  printf("ENEMY");
  gotoxy(79, 19);
  printf("2 : 2x SCORE");
  gotoxy(79, 21);
  printf("ITEM COOLDOWN");
  gotoxy(79, 24);
  printf("PACMAN GAME %c", 254);
  gotoxy(79, 25);
  printf("%c MODIFIED BY", 254);
  gotoxy(79, 26);
  printf("@maoelanaAs %c", 254);
}

// Loading screen awal game
void loadingScreen()
{
  gotoxy(36, 13);
  printf("Loading");
  for (int i = 0; i < 6; i++)
  {
    if (i < 3)
    {
      gotoxy(38 + i, 14);
      printf("*");
    }
    if (i > 2)
    {
      gotoxy(34 + i, 14);
      printf(" %c", 204);
    }
    Sleep(500);
  }
  gotoxy(36, 13);
  printf("       ");
  gotoxy(38, 14);
  printf("   ");
  gotoxy(36, 14);
  printf("Start!!");
  Sleep(500);
}

// Memberikan koordinat x secara acak
int xAcak()
{
  int x = rand();
  if ((x % 76) < 2)
  {
    return (x % 76) + 2;
  }
  else
  {
    return (x % 76);
  }
}

// Memberikan koordinat y secara acak
int yAcak()
{
  int y = rand();
  if ((y % 26) < 2)
  {
    return (y % 26) + 2;
  }
  else
  {
    return (y % 26);
  }
}

#endif