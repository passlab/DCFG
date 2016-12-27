# Disassemble main from 0000000000400674 to 0000000000400710

../a.out:     file format elf64-x86-64


Disassembly of section .text:

0000000000400674 <main>:
  400674:	55                   	push   %rbp
  400675:	48 89 e5             	mov    %rsp,%rbp
  400678:	48 83 ec 20          	sub    $0x20,%rsp
  40067c:	c7 45 f0 04 00 00 00 	movl   $0x4,-0x10(%rbp)
  400683:	c7 45 f4 04 00 00 00 	movl   $0x4,-0xc(%rbp)
  40068a:	8b 45 f4             	mov    -0xc(%rbp),%eax
  40068d:	48 63 d0             	movslq %eax,%rdx
  400690:	8b 45 f0             	mov    -0x10(%rbp),%eax
  400693:	48 98                	cltq   
  400695:	48 0f af c2          	imul   %rdx,%rax
  400699:	48 c1 e0 03          	shl    $0x3,%rax
  40069d:	48 89 c7             	mov    %rax,%rdi
  4006a0:	e8 fb fd ff ff       	callq  4004a0 <malloc@plt>
  4006a5:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  4006a9:	c7 45 ec 00 00 00 00 	movl   $0x0,-0x14(%rbp)
  4006b0:	eb 25                	jmp    4006d7 <main+0x63>
  4006b2:	8b 45 ec             	mov    -0x14(%rbp),%eax
  4006b5:	48 98                	cltq   
  4006b7:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  4006be:	00 
  4006bf:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  4006c3:	48 01 d0             	add    %rdx,%rax
  4006c6:	66 0f ef c0          	pxor   %xmm0,%xmm0
  4006ca:	f2 0f 2a 45 ec       	cvtsi2sdl -0x14(%rbp),%xmm0
  4006cf:	f2 0f 11 00          	movsd  %xmm0,(%rax)
  4006d3:	83 45 ec 01          	addl   $0x1,-0x14(%rbp)
  4006d7:	8b 45 f4             	mov    -0xc(%rbp),%eax
  4006da:	0f af 45 f0          	imul   -0x10(%rbp),%eax
  4006de:	3b 45 ec             	cmp    -0x14(%rbp),%eax
  4006e1:	7f cf                	jg     4006b2 <main+0x3e>
  4006e3:	8b 55 f4             	mov    -0xc(%rbp),%edx
  4006e6:	8b 4d f0             	mov    -0x10(%rbp),%ecx
  4006e9:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  4006ed:	89 ce                	mov    %ecx,%esi
  4006ef:	48 89 c7             	mov    %rax,%rdi
  4006f2:	e8 bf fe ff ff       	callq  4005b6 <array1to2>
  4006f7:	bf a0 07 40 00       	mov    $0x4007a0,%edi
  4006fc:	e8 6f fd ff ff       	callq  400470 <puts@plt>
  400701:	b8 00 00 00 00       	mov    $0x0,%eax
  400706:	c9                   	leaveq 
  400707:	c3                   	retq   
  400708:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  40070f:	00 
