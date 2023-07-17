/* File Name: frame.h
 * PROGRAMMER: DB6
 * DATE: 21.07.2022
 */
#ifndef __frame_h_
#define __frame_h_

#include <iostream>
#include <fstream>

#include <windows.h>
#pragma pack(push, 1)
#include <tgahead.h>
#pragma pack(pop)

#include "cmpl.h"

/* Frame represetation type */
struct frame
{
  static constexpr INT W = 1920 / 2, H = 1080 / 2; // frame size
  DWORD Image[W * H] = {0};            // pixels array
  //HWND hWnd;
  //HDC hDC;
  //PAINTSTRUCT ps;
  //static HDC hMemDC;
  //static HBITMAP hBm;
  //MINMAXINFO *minmax;

  frame( VOID )
  {
  }

  ~frame( VOID )
  {
  }

  /* Put pixel on frame method.
   *   ARGUMENTS:
   *   - pixel coordinates:
   *       INT X, Y;
   *   - pixel color:
   *       DWORD Color;
   * RETURNS: None.
   */
  VOID PutPixel( INT X, INT Y, DWORD Color )
  {
    if (X >= W || X < 0 || Y >= H || Y < 0)
      return;

    Image[Y * W + X] = Color;
  } 
  /* End of 'PutPixel' method */

  /* Put pixel on frame method.
   * ARGUMENTS:
   *   - pixel coordinates:
   *       INT X, Y;
   *   - pixel color components:
   *       UCHAR R, G, B;
   * RETURNS: None.
   */
  VOID PutPixel( INT X, INT Y, UCHAR R, UCHAR G, UCHAR B, UCHAR A = 255 )
  {
    if (X >= W || X < 0 || Y >= H || Y < 0)
      return;

    Image[Y * W + X] = A << 24 | R << 16 | G << 8 | B;
  } /* End of 'PutPixel' method */

  /* Draw frame method.
   * ARGUMENTS:
   *   - link at device context handle:
   *       HDC &hDC;
   * RETURNS: None.
   */
  VOID Draw( HDC &hDC )
  {
    DBL X0 = -3, X1 = 3, Y0 = -3, Y1 = 3;
    for (INT Ys = 0; Ys < H; Ys++)
      for (INT Xs = 0; Xs < W; Xs++)
      {
        cmpl Z(Xs * (X1 - X0) / W + X0, Ys * (Y1 - Y0) / H + Y0);
        int i = 0;
        while (i < 128 && !Z < 6)
          Z = Z - ((Z.Sin() + 4.7).Cos() * Z * Z * Z * 2.8 ) * sin(30.0 * i + 4.7) / ((-Z.Sin() * Z.Cos() * Z * Z * Z * 2.8) + (Z * Z * 3 * 2.8 *(Z.Sin() + 4.7).Cos())), i++;
        PutPixel(Xs, Ys, i, i * 3, i * i / 8);
        //PutPixel(Xs, Ys, 0x00007777);
      }

    BITMAPINFOHEADER bmih = {0};
    bmih.biSize = sizeof(BITMAPINFOHEADER);
    bmih.biBitCount = 32;
    bmih.biPlanes = 1;
    bmih.biCompression = BI_RGB;
    bmih.biWidth = W;
    bmih.biHeight = H;
    bmih.biSizeImage = W * H * sizeof(DWORD);

    SetDIBitsToDevice(hDC, 0, 0, W, H, 0, 0, 0, H, Image, (BITMAPINFO*)&bmih, DIB_RGB_COLORS);
  } /* End of 'Draw' method */ 

 /* Save frame to file function.
  * ARGUMENTS: None;
  * RETURNS: None.
  */
  VOID Save ( void )
  {
    CHAR FileName[102];
    SYSTEMTIME st;

    GetLocalTime(&st);
    wsprintf(FileName, "%04d%02d%02d_%02d%02d%02d_%03d.tga", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    std::fstream F(FileName, std::fstream::out | std::fstream::binary);

    if (!F)
      return;

    CHAR Copyright[] = "DB6's picture";
    tgaFILEHEADER Header =
    {
      sizeof(Copyright),
      0, // No palette
      2, // Uncompressed RGB image
      0, 0, 0, // color map info (absent)
      0, 0, // Start (X,Y)
      W, H, // Image size
      32,   // Bits per pixel
      0x28, // Upper-left image orign, 8-bit alpha-channel
    };

    F.write((const CHAR *)&Header, sizeof(Header));
    F.write(Copyright, sizeof(Copyright));
    F.write((const CHAR *)Image, W * H * 4);
    F.write(TGA_EXT_SIGNATURE, sizeof(TGA_EXT_SIGNATURE));
  } /* End of 'Save' function */
};
#endif //__frame_h_
/* END OF 'cmpl.h' FILE */
  