!   Copyright 2011-2014,2016 Theo Berkau
!
!   This file is part of MPGROMDUMP.
!
!   MPGROMDUMP is free software; you can redistribute it and/or modify
!   it under the terms of the GNU General Public License as published by
!   the Free Software Foundation; either version 2 of the License, or
!   (at your option) any later version.
!
!   MPGROMDUMP is distributed in the hope that it will be useful,
!   but WITHOUT ANY WARRANTY; without even the implied warranty of
!   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
!   GNU General Public License for more details.
!
!   You should have received a copy of the GNU General Public License
!   along with MPGROMDUMP; if not, write to the Free Software
!   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

! Based on Bart's Custom Sega Saturn Start-Up Code

.section .text

!
! Entry point
!
.global start
start:
    ! Disable interrupts
    mov     #0xf,r0
    shll2   r0
    shll2   r0
    ldc     r0,sr

lprog_end:
    
    !
    ! Clear BSS
    !
    mov.l   bss_start,r0
    mov.l   bss_end,r1
    mov     #0,r2
lbss:
    cmp/hs  r1, r0
    bt      lbss_end
    mov.b   r2,@r0
    add     #1,r0
    bra     lbss
    nop
lbss_end:

    !
    ! Set initial stack pointer. Stack is from 0x6002000-0x6003FFF
    !
    mov.l   stack_ptr,r15

    !
    ! Jump to main()
    !
    mov.l   main_ptr,r0
    jsr @r0
    nop

    !
    ! Once main() has terminated, disable interrupts and loop infinitely
    !
    mov     #0xf,r0
    shll2   r0
    shll2   r0
    ldc     r0,sr
end:
    bra     end
    nop
.align 4
main_ptr:   .long _main
stack_ptr:  .long 0x06004000 ! stack is from 0x06002000-0x06003FFF
bss_start:  .long __bss_start
bss_end:    .long __bss_end
rom_start:  .long 0x06004000
prog_start: .long start
prog_end:   .long _end

! This is to keep libc happy

.global _atexit
_atexit:
   bra end
   nop
