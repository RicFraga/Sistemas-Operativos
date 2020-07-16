segment .data
cadena db 'Programar en Ensamblador no es bonito',0xA

segment .text
global _start
_start:
  mov edx,38d
  mov ecx,cadena
  mov ebx,1
  mov eax,4
  int 0x80
  mov eax,1
  int 0x80
