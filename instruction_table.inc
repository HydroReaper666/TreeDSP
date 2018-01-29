R"(
D4FBh add  MemImm16@16, Ax@8
A600h add  MemImm8@0, Ax@8
86C0h add  Imm16@16, Ax@8
C600h add  Imm8u@0, Ax@8
D4DBh add  MemR7Imm16@16, Ax@8
4600h add  MemR7Imm7s@0, Ax@8
)";
const std::string moo = R"(
8680h add  MemRn@0, Ax@8 || Rn@0stepZIDS@3
86A0h add  RegisterP0@0, Ax@8
D2DAh add  Ab@10, Bx@0
5DF0h add  Bx@1, Ax@0
9070h add  MemR01@8, sv, Abh@2 || sub MemR01@8offsZI@0, sv, Abl@2 || mov Abl@2, MemR45@8 || R01@8stepII2@0, R45@8stepII2@1
5DB0h add  MemR04@1, sv, Abh@2 || sub MemR04@1offsZI@0, sv, Abl@2 || R04@1stepII2@0
6F80h add  MemR45@2, MemR01@2, Abh@3 || add MemR45@2offsZI@1, MemR01@2offsZI@0, Abl@3 || R01@2stepII2@0, R45@2stepII2@1
6FA0h add  MemR45@2, MemR01@2, Abh@3 || sub MemR45@2offsZI@1, MemR01@2offsZI@0, Abl@3 || R01@2stepII2@0, R45@2stepII2@1
5E30h add  MemR45@8, sv, Abh@2 || sub MemR45@8offsZI@1, sv, Abl@2 || mov Abl@2, MemR01@8 || R01@8stepII2@0, R45@8stepII2@1
5DC0h add  p0, p1, Ab@2
D782h add  p1, Ax@0
5DF8h add  Px@1, Bx@0
D38Bh add  r6, Ax@4
4590h add3 p0, p1, Ab@2
4592h add3a p0, p1, Ab@2
4593h add3aa p0, p1, Ab@2
5DC1h adda p0, p1, Ab@2
B200h addh MemImm8@0, Ax@8
9280h addh MemRn@0, Ax@8 || Rn@0stepZIDS@3
92A0h addh Register@0, Ax@8
9464h addh r6, Ax@0
90E0h addhp MemR0425@2, Px@4, Ax@8 || R0425@2stepII2D2S@0 ;p=ProgMem? Px?
B400h addl MemImm8@0, Ax@8
9480h addl MemRn@0, Ax@8 || Rn@0stepZIDS@3
94A0h addl Register@0, Ax@8
9466h addl r6, Ax@0
906Ch addsub  p0, p1, Ab@0
49C2h addsub  p1, p0, Ab@4
916Ch addsuba p0, p1, Ab@0
49C3h addsuba p1, p0, Ab@4
E700h addv Imm16@16, MemImm8@0
86E0h addv Imm16@16, MemRn@0 || Rn@0stepZIDS@3
87E0h addv Imm16@16, Register@0
47BBh addv Imm16@16, r6
D4F9h and  MemImm16@16, Ax@8
A200h and  MemImm8@0, Ax@8
82C0h and  Imm16@16, Ax@8
C200h and  Imm8u@0, Ax@8
D4D9h and  MemR7Imm16@16, Ax@8
4200h and  MemR7Imm7s@0, Ax@8
8280h and  MemRn@0, Ax@8 || Rn@0stepZIDS@3
82A0h and  RegisterP0@0, Ax@8
6770h and  Ab@2, Ab@0, Ax@12                ;TL2 only
D389h and  r6, Ax@4
4B80h banke BankFlags6@0  ;{r0}{,r1}{,r4}{,cfgi}{,r7}{,cfgj}
8CDFh bankr       ;without operand ?
8CDCh bankr Ar@0
8CD0h bankr Ar@2, Arp@0
8CD8h bankr Arp@0
5EB8h bitrev Rn@0
D7E8h bitrev Rn@0, dbrv
D7E0h bitrev Rn@0, ebrv
5C00h bkrep NoReverse, Imm8u@0, Address16@16
5D00h bkrep NoReverse, Register@0, Address18@16and5
8FDCh bkrep NoReverse, r6, Address18@16and0
DA9Ch bkreprst MemR0425@0
5F48h bkreprst MemSp, Unused2@0
DADCh bkrepsto MemR0425@0, Unused1@10
9468h bkrepsto MemSp, Unused3@0
4180h br   Address18@16and4, Cond@0
D3C0h break               ;break
5000h brr  RelAddr7@4, Cond@0
41C0h call Address18@16and4, Cond@0
D480h calla Axl@8
D381h calla Ax@4
1000h callr RelAddr7@4, Cond@0
9068h cbs  Axh@0, Axh@not0, r0, ge
9168h cbs  Axh@0, Axh@not0, r0, gt
D49Eh cbs  Axh@8, Bxh@5, r0, ge
D49Fh cbs  Axh@8, Bxh@5, r0, gt
D5C0h cbs  MemR01@2, MemR45@2, ge || R01@2stepII2@0, R45@2stepII2@1
D5C8h cbs  MemR01@2, MemR45@2, gt || R01@2stepII2@0, R45@2stepII2@1
E500h chng Imm16@16, MemImm8@0
84E0h chng Imm16@16, MemRn@0 || Rn@0stepZIDS@3
85E0h chng Imm16@16, Register@0
47BAh chng Imm16@16, r6
0038h chng Imm16@16, SttMod@0
6760h clr  Implied ConstZero, Ax@12, Cond@0  ;aX=0
6F60h clr  Implied ConstZero, Bx@12, Cond@0  ;bX=0
8ED0h clr  Implied ConstZero, Ab@2, Ab@0
5DFEh clrp p0
5DFFh clrp p0, p1
5DFDh clrp p1
67C0h clrr Implied Const8000h, Ax@12, Cond@0 ;aX=8000h
6F70h clrr Implied Const8000h, Bx@12, Cond@0 ;bX=8000h
8DD0h clrr Implied Const8000h, Ab@2, Ab@0
D4FEh cmp  MemImm16@16, Ax@8
AC00h cmp  MemImm8@0, Ax@8
8CC0h cmp  Imm16@16, Ax@8
CC00h cmp  Imm8u@0, Ax@8
D4DEh cmp  MemR7Imm16@16, Ax@8
4C00h cmp  MemR7Imm7s@0, Ax@8
8C80h cmp  MemRn@0, Ax@8 || Rn@0stepZIDS@3
8CA0h cmp  RegisterP0@0, Ax@8
4D8Ch cmp  Ax@1, Bx@0
D483h cmp  b0, b1
D583h cmp  b1, b0
DA9Ah cmp  Bx@10, Ax@0
8B63h cmp  p1, Ax@4
D38Eh cmp  r6, Ax@4
BE00h cmpu MemImm8@0, Ax@8
9E80h cmpu MemRn@0, Ax@8 || Rn@0stepZIDS@3
9EA0h cmpu Register@0, Ax@8
8A63h cmpu r6, Ax@3
ED00h cmpv Imm16@16, MemImm8@0
8CE0h cmpv Imm16@16, MemRn@0 || Rn@0stepZIDS@3
8DE0h cmpv Imm16@16, Register@0
47BEh cmpv Imm16@16, r6
D390h cntx r  ;restore shadows
D380h cntx s  ;store shadows
67F0h copy Implied Ax@not12,   Ax@12, Cond@0 ;aX=aY
67E0h dec  Implied Const1,     Ax@12, Cond@0 ;aX=aX-1
43C0h dint        ;IE=0, interrupt disable
0E00h divs MemImm8@0, Ax@8
4380h eint        ;IE=1, interrupt enable
9460h exp  Bx@0, Implied sv
9060h exp  Bx@0, Implied sv, Ax@8
9C40h exp  MemRn@0, Implied sv || Rn@0stepZIDS@3
9840h exp  MemRn@0, Implied sv, Ax@8 || Rn@0stepZIDS@3
9040h exp  RegisterP0@0, Implied sv, Ax@8
9440h exp  RegisterP0@0, Implied sv
D7C1h exp  r6, Implied sv
D382h exp  r6, Implied sv, Ax@4
67D0h inc  Implied Const1,     Ax@12, Cond@0 ;aX=aX+1
49C0h lim  a0     ;aka a0,a0
49D0h lim  a0, a1
49F0h lim  a1     ;aka a1,a1
49E0h lim  a1, a0
4D80h load Imm2u@0, ps               ;st1.bit11-10=imm2
DB80h load Imm7s@0, stepi            ;cfgi.LSB=imm7
DF80h load Imm7s@0, stepj            ;cfgj.LSB=imm7
0400h load Imm8u@0, page             ;st1.LSBs=imm8 ;aka "lpg"
0200h load Imm9u@0, modi             ;cfgi.MSB=imm9
0A00h load Imm9u@0, modj             ;cfgj.MSB=imm9
D7D8h load Imm2u@1, movpd, Unused1@0 ;stt2.bit6.7 (page for ProgMem)
0010h load Imm4u@0, ps01             ;mod0.bit10-11,13-14 and st1.10-11 ?
D400h maa  MemR45@2, MemR0123@0, Ax@11 || R0123@0stepZIDS@3, R45@2stepZIDS@5
8400h maa  MemRn@0, Imm16@16, Ax@11 || Rn@0stepZIDS@3
8420h maa  y0, MemRn@0, Ax@11 || Rn@0stepZIDS@3
8440h maa  y0, Register@0, Ax@11
E400h maa  y0, MemImm8@0, Ax@11
5EA8h maa  y0, r6, Ax@0
D700h maasu MemR45@2, MemR0123@0, Ax@11 || R0123@0stepZIDS@3, R45@2stepZIDS@5
8700h maasu MemRn@0, Imm16@16, Ax@11 || Rn@0stepZIDS@3
8720h maasu y0, MemRn@0, Ax@11 || Rn@0stepZIDS@3
8740h maasu y0, Register@0, Ax@11
5EAEh maasu y0, r6, Ax@0
D200h mac  MemR45@2, MemR0123@0, Ax@11 || R0123@0stepZIDS@3, R45@2stepZIDS@5
8200h mac  MemRn@0, Imm16@16, Ax@11 || Rn@0stepZIDS@3
8220h mac  y0, MemRn@0, Ax@11 || Rn@0stepZIDS@3
8240h mac  y0, Register@0, Ax@11
E200h mac  y0, MemImm8@0, Ax@11
5EA4h mac  y0, r6, Ax@0
4D84h mac  y0, x1, Ax@1, Unused1@0
5E28h mac1 MemR45@2, MemR01@2, Ax@8 || R01@2stepII2@0, R45@2stepII2@1
D600h macsu MemR45@2, MemR0123@0, Ax@11 || R0123@0stepZIDS@3, R45@2stepZIDS@5
8600h macsu MemRn@0, Imm16@16, Ax@11 || Rn@0stepZIDS@3
E600h macsu y0, MemImm8@0, Ax@11
8620h macsu y0, MemRn@0, Ax@11 || Rn@0stepZIDS@3
8640h macsu y0, Register@0, Ax@11
5EACh macsu y0, r6, Ax@0
D300h macus MemR45@2, MemR0123@0, Ax@11 || R0123@0stepZIDS@3, R45@2stepZIDS@5
8300h macus MemRn@0, Imm16@16, Ax@11 || Rn@0stepZIDS@3
8320h macus y0, MemRn@0, Ax@11 || Rn@0stepZIDS@3
8340h macus y0, Register@0, Ax@11
5EA6h macus y0, r6, Ax@0
D500h macuu MemR45@2, MemR0123@0, Ax@11 || R0123@0stepZIDS@3, R45@2stepZIDS@5
8500h macuu MemRn@0, Imm16@16, Ax@11 || Rn@0stepZIDS@3
8520h macuu y0, MemRn@0, Ax@11 || Rn@0stepZIDS@3
8540h macuu y0, Register@0, Ax@11
5EAAh macuu y0, r6, Ax@0
8460h max  NoReverse, Ax@8, Implied Ax@not8, Bogus MemR0, ge, Implied mixp, Implied r0 || R0stepZIDS@3   ;when aY >= aX
8660h max  NoReverse, Ax@8, Implied Ax@not8, Bogus MemR0, gt, Implied mixp, Implied r0 || R0stepZIDS@3   ;when aY > aX
5E21h max  a0h, a1h || max a0l, a1l || vtrshr
5F21h max  a1h, a0h || max a1l, a0l || vtrshr
D784h max  Axh@1, Bxh@0 || max Axl@1, Bxl@0 || vtrshr
4A40h max  Axh@3, Bxh@4 || max Axl@3, Bxl@4 || mov Axl@not3, MemR04@1 || vtrshr || R04@1stepII2@0
4A44h max  Axh@3, Bxh@4 || max Axl@3, Bxl@4 || mov Axh@not3, MemR04@1 || vtrshr || R04@1stepII2@0
45A0h max  Axh@4, Bxh@3 || max Axl@4, Bxl@3 || mov Axh@not4, MemR45@2 || mov Axl@not4, MemR01@2 || vtrshr || R01@2stepII2@0, R45@2stepII2@1
D590h max  Axh@6, Bxh@5 || max Axl@6, Bxl@5 || mov Axh@not6, MemR01@2 || mov Axl@not6, MemR45@2 || vtrshr || R01@2stepII2@0, R45@2stepII2@1
4A60h max  Bxh@4, Axh@3 || max Bxl@4, Axl@3 || mov Bxl@not4, MemR04@1 || vtrshr || R04@1stepII2@0
4A64h max  Bxh@4, Axh@3 || max Bxl@4, Axl@3 || mov Bxh@not4, MemR04@1 || vtrshr || R04@1stepII2@0
8060h maxd NoReverse, Ax@8, MemR0, ge, Implied mixp, Implied r0 || R0stepZIDS@3   ;when (r0) >= aX
8260h maxd NoReverse, Ax@8, MemR0, gt, Implied mixp, Implied r0 || R0stepZIDS@3   ;when (r0) > aX
8860h min  NoReverse, Ax@8, Implied Ax@not8, Bogus MemR0, le, Implied mixp, Implied r0 || R0stepZIDS@3   ;when aY <= aX
8A60h min  NoReverse, Ax@8, Implied Ax@not8, Bogus MemR0, lt, Implied mixp, Implied r0 || R0stepZIDS@3   ;when aY < aX
43C2h min  Axh@0, Axh@not0 || min Axl@0, Axl@not0 || vtrshr
D2B8h min  Axh@11, Bxh@10 || min Axl@11, Bxl@10 || mov Axh@not11, MemR01@2 || mov Axl@not11, MemR45@2 || vtrshr || R01@2stepII2@0, R45@2stepII2@1
4A00h min  Axh@3, Bxh@4 || min Axl@3, Bxl@4 || mov Axl@not3, MemR04@1 || vtrshr || R04@1stepII2@0
4A04h min  Axh@3, Bxh@4 || min Axl@3, Bxl@4 || mov Axh@not3, MemR04@1 || vtrshr || R04@1stepII2@0
45E0h min  Axh@4, Bxh@3 || min Axl@4, Bxl@3 || mov Axh@not4, MemR45@2 || mov Axl@not4, MemR01@2 || vtrshr || R01@2stepII2@0, R45@2stepII2@1
D4BAh min  Axh@8, Bxh@0 || min Axl@8, Bxl@0 || vtrshr
4A20h min  Bxh@4, Axh@3 || min Bxl@4, Axl@3 || mov Bxl@not4, MemR04@1 || vtrshr || R04@1stepII2@0
4A24h min  Bxh@4, Axh@3 || min Bxl@4, Axl@3 || mov Bxh@not4, MemR04@1 || vtrshr || R04@1stepII2@0
47A0h mind NoReverse, Ax@3, MemR0, le, Implied mixp, Implied r0 || R0stepZIDS@0
47A4h mind NoReverse, Ax@3, MemR0, lt, Implied mixp, Implied r0 || R0stepZIDS@0
0080h modr MemRn@0stepZIDS@3
00A0h modr MemRn@0stepZIDS@3, dmod  ;Disable modulo
D294h modr MemR0123@10stepII2D2S0@0 || modr MemR4567@10stepII2D2S0@5
0D80h modr MemR0123@5stepII2D2S0@1  || modr MemR4567@5stepII2D2S0@3, dmod
0D81h modr MemR0123@5stepII2D2S0@1, dmod || modr MemR4567@5stepII2D2S0@3, dmod
8464h modr MemR0123@8stepII2D2S0@0, dmod || modr MemR4567@8stepII2D2S0@3
5DA0h modr MemRn@0stepD2
5DA8h modr MemRn@0stepD2, dmod
4990h modr MemRn@0stepI2
4998h modr MemRn@0stepI2, dmod
D290h mov  Ab@10, Ab@5
D298h mov  Abl@10, dvm
D2D8h mov  Abl@10, x0
3000h mov  Ablh@9, MemImm8@0
D4BCh mov  Axl@8, MemImm16@16
D49Ch mov  Axl@8, MemR7Imm16@16
DC80h mov  Axl@8, MemR7Imm7s@0
D4B8h mov  MemImm16@16, Ax@8
6100h mov  MemImm8@0, Ab@11
6200h mov  MemImm8@0, Ablh@10
6500h mov  MemImm8@0, Axh@12, eu   ;aka Axheu
6000h mov  MemImm8@0, R0123457y0@10
6D00h mov  MemImm8@0, sv
D491h mov  dvm, Ab@5
D492h mov  icr, Ab@5
5E20h mov  Imm16@16, Bx@8
5E00h mov  Imm16@16, Register@0
4F80h mov  Imm5u@0, icr    ;uh, but icr is 8bit wide (only 4bit are R/W)?
2500h mov  Imm8s@0, Axh@12         ;signed!
2900h mov  Imm8s@0, ext0
2D00h mov  Imm8s@0, ext1
3900h mov  Imm8s@0, ext2
3D00h mov  Imm8s@0, ext3
2300h mov  Imm8s@0, R0123457y0@10  ;signed!
0500h mov  Imm8s@0, sv
2100h mov  Imm8u@0, Axl@12         ;unsigned!
D498h mov  MemR7Imm16@16, Ax@8
D880h mov  MemR7Imm7s@0, Ax@8
98C0h mov  MemRn@0, Bx@8 || Rn@0stepZIDS@3
1C00h mov  MemRn@0, Register@5 || Rn@0stepZIDS@3
47E0h mov  MemSp, Register@0
47C0h mov  mixp, Register@0
2000h mov  R0123457y0@9, MemImm8@0
4FC0h mov  Register@0, icr
5E80h mov  Register@0, mixp
1800h mov  Register@5, MemRn@0 || Rn@0stepZIDS@3
5EC0h mov  RegisterP0@0, Bx@5
5800h mov  RegisterP0@0, Register@5
D490h mov  repc, Ab@5
7D00h mov  sv, MemImm8@0
D493h mov  x0, Ab@5
D49Bh mov  a0h, stepi0
D59Bh mov  a0h, stepj0
4390h mov  a0h, MemR0425@2 || mov y0, MemR0425@2offsZIDZ@0 || R0425@2stepII2D2S@0
43D0h mov  a1h, MemR0425@2 || mov y0, MemR0425@2offsZIDZ@0 || R0425@2stepII2D2S@0
8FD4h mov  Ab@0, p0
43A0h mov  Abh@3, MemR01@2 || mov Abl@3, MemR45@2 || R01@2stepII2@0, R45@2stepII2@1
43E0h mov  Abh@3, MemR45@2 || mov Abl@3, MemR01@2 || R01@2stepII2@0, R45@2stepII2@1
9D40h mov  Abh@4, MemR04@1 || mov Abh@2, MemR04@1offsZI@0 || R04@1stepII2@0
9164h mov  Abl@0, prpage
9064h mov  Abl@0, repc
D394h mov  Abl@0, x1
D384h mov  Abl@0, y1
9540h mov  Abl@3, ArArp@0
9C60h mov  Abl@3, SttMod@0
9560h mov  ArArp@0, Abl@3
D488h mov  ArArp@0, MemR04@8 || R04@8stepII2@5
5F50h mov  ArArpSttMod@0, MemR7Imm16@16
886Bh mov  Ax@8, pc
8C60h mov  Axh@4, MemR4567@8 || mov MemR0123@8, Axh@4 || R0123@8stepII2D2S@0, R4567@8stepII2D2S@2
4800h mov  Axh@6, MemR0123@4 || movr MemR4567@4, Axh@6 || R0123@4stepII2D2S@0, R4567@4stepII2D2S@2
4900h mov  Axh@6, MemR0123@4 || mov  MemR4567@4, Axh@6 || R0123@4stepII2D2S@0, R4567@4stepII2D2S@2
7F80h mov  Axh@6, MemR4567@4 || movr MemR0123@4, Axh@6 || R0123@4stepII2D2S@0, R4567@4stepII2D2S@2
8863h mov  Bx@8, pc
0008h mov  Imm16@16, ArArp@0
0023h mov  Imm16@16, r6
0001h mov  Imm16@16, repc
8971h mov  Imm16@16, stepi0
8979h mov  Imm16@16, stepj0
0030h mov  Imm16@16, SttMod@0
5DD0h mov  Imm4u@0, prpage
80C4h mov  MemR01@9, Abh@10 || mov MemR45@9, Abl@10 || R01@9stepII2@0, R45@9stepII2@8
D292h mov  MemR0425@10_MemR0425@10offsZIDZ@5, Px@0 || R0425@10stepII2D2S@5
D7D4h mov  MemR04@1, repc || R04@1stepII2@0
5F4Ch mov  MemR04@1, sv || sub3 MemR04@1, p0, p1, b0 || R04@1stepII2@0
D4B4h mov  MemR04@1, sv || sub3rnd MemR04@1, p0, p1, b1 || R04@1stepII2@0
DE9Ch mov  MemR04@1, sv || sub3rnd MemR04@1, p0, p1, b0 || R04@1stepII2@0
4B40h mov  MemR04@3, sv || addsub    MemR04@3, p1, p0, Bx@0 || R04@3stepII2@2
4B42h mov  MemR04@3, sv || addsubrnd MemR04@3, p1, p0, Bx@0 || R04@3stepII2@2
8062h mov  MemR04@4, ArArp@8  || R04@4stepII2@3
8063h mov  MemR04@4, SttMod@8 || R04@4stepII2@3
9960h mov  MemR04@4, sv || addsub    MemR04@4, p1, p0, Bx@2 || R04@4stepD2S@3  ;<-- ordered p1, p0 here !
99E0h mov  MemR04@4, sv || addsubrnd MemR04@4, p1, p0, Bx@2 || R04@4stepD2S@3  ;<-- ordered p1, p0 here !
9860h mov  MemR04@4, sv || sub3      MemR04@4, p0, p1, Bx@2 || R04@4stepD2S@3
98E0h mov  MemR04@4, sv || sub3rnd   MemR04@4, p0, p1, Bx@2 || R04@4stepD2S@3
8873h mov  MemR04@8, sv || sub3 MemR04@8, p0, p1, b1 || R04@8stepII2@3
D4C0h mov  MemR45@5, Abh@2 || mov MemR01@5, Abl@2 || R01@5stepII2@0, R45@5stepII2@1
4D90h mov  MemR7Imm16@16, ArArpSttMod@0
D2DCh mov  MemR7Imm16@16, repc, Unused2@0, Unused1@10
1B20h mov  MemRn@0, r6 || Rn@0stepZIDS@3 ;override 1800h (mov a1,MemRn@0)
D29Ch mov  MemSp, r6, Unused2@0, Unused1@10
8A73h mov  mixp, Bx@3
4381h mov  mixp, r6
4382h mov  p0h, Bx@0
D3C2h mov  p0h, r6
4B60h mov  p0h, Register@0     ;<-- here "p0h" as source
8FD8h mov  p1, Ab@0
88D0h mov  Px@1, MemR0425@8_MemR0425@8offsZIDZ@2   || R0425@8stepII2D2S@2
88D1h mov  Px@1, MemR0425@8_MemR0425@8offsZIDZ@2,s || R0425@8stepII2D2S@2
D481h mov  r6, Bx@8
1B00h mov  r6, MemRn@0 || Rn@0stepZIDS@3 ;override 1800h (mov a0,MemRn@0)
43C1h mov  r6, mixp
5F00h mov  r6, Register@0
5F60h mov  Register@0, r6
D2D9h mov  repc, Abl@10
D7D0h mov  repc, MemR04@1 || R04@1stepII2@0
D3C8h mov  repc, MemR7Imm16@16, Unused3@0
D482h mov  stepi0, a0h
D582h mov  stepj0, a0h
D2F8h mov  SttMod@0, Abl@10
49C1h mov  x1, Ab@4
D299h mov  y1, Ab@10
5EB0h mov  prpage, Abl@0
49A0h mov  SttMod@0, MemR04@4 || R04@4stepII2@3
4DC0h mova Ab@4, MemR0425@2_MemR0425@2offsZIDZ@0 || R0425@2stepII2D2S@0
4BC0h mova MemR0425@2_MemR0425@2offsZIDZ@0, Ab@4 || R0425@2stepII2D2S@0
5F80h movd MemR0123@0,ProgMemR45@2 || R0123@0stepZIDS@3, R45@2stepZIDS@5
0040h movp ProgMemAxl@5, Register@0
0D40h movp ProgMemAx@5, Register@0
0600h movp ProgMemRn@0, MemR0123@5 || R0123@5stepZIDS@7, Rn@0stepZIDS@3
D499h movpdw ProgMemAx@8_ProgMemAx@8offsI, pc
8864h movr MemR0425@3, Abh@8 || R0425@3stepII2D2S@0   ;op*10000h+8000h
9CE0h movr MemRn@0, Ax@8 || Rn@0stepZIDS@3
9CC0h movr RegisterP0@0, Ax@8
5DF4h movr Bx@1, Ax@0
8961h movr r6, Ax@3
6300h movs Implied sv, MemImm8@0, Ab@11
0180h movs Implied sv, MemRn@0, Ab@5 || Rn@0stepZIDS@3
0100h movs Implied sv, RegisterP0@0, Ab@5
5F42h movs Implied sv, r6, Ax@0
4080h movsi Implied Imm5s@0, R0123457y0@9, Ab@5, Bogus Imm5s@0
D000h mpy  MemR45@2, MemR0123@0 || R0123@0stepZIDS@3, R45@2stepZIDS@5
8000h mpy  MemRn@0, Imm16@16    || Rn@0stepZIDS@3
8020h mpy  y0, MemRn@0          || Rn@0stepZIDS@3
8040h mpy  y0, Register@0
E000h mpy  y0, MemImm8@0
5EA0h mpy  y0, r6
CB00h mpy  MemR45@5, MemR01@5 || mpysu MemR45@5offsZI@4, MemR01@5offsZI@3 || sub3   p0, p1, Ab@6 || R01@5stepII2@3, R45@5stepII2@4
CB01h mpy  MemR45@5, MemR01@5 || mpyus MemR45@5offsZI@4, MemR01@5offsZI@3 || sub3   p0, p1, Ab@6 || R01@5stepII2@3, R45@5stepII2@4
CB02h mpy  MemR45@5, MemR01@5 || mpysu MemR45@5offsZI@4, MemR01@5offsZI@3 || sub3a  p0, p1, Ab@6 || R01@5stepII2@3, R45@5stepII2@4
CB03h mpy  MemR45@5, MemR01@5 || mpyus MemR45@5offsZI@4, MemR01@5offsZI@3 || sub3a  p0, p1, Ab@6 || R01@5stepII2@3, R45@5stepII2@4
CB04h mpy  MemR45@5, MemR01@5 || mpysu MemR45@5offsZI@4, MemR01@5offsZI@3 || add3   p0, p1, Ab@6 || R01@5stepII2@3, R45@5stepII2@4
CB05h mpy  MemR45@5, MemR01@5 || mpyus MemR45@5offsZI@4, MemR01@5offsZI@3 || add3   p0, p1, Ab@6 || R01@5stepII2@3, R45@5stepII2@4
CB06h mpy  MemR45@5, MemR01@5 || mpysu MemR45@5offsZI@4, MemR01@5offsZI@3 || add3a  p0, p1, Ab@6 || R01@5stepII2@3, R45@5stepII2@4
CB07h mpy  MemR45@5, MemR01@5 || mpyus MemR45@5offsZI@4, MemR01@5offsZI@3 || add3a  p0, p1, Ab@6 || R01@5stepII2@3, R45@5stepII2@4
D5E0h mpy  MemR04@1, x1 || mpy y1, x0 || sub3 p0, p1, Ax@3 || R04@1stepII2@0
D5E4h mpy  MemR04@1, x1 || mpy y1, x0 || add3 p0, p1, Ax@3 || R04@1stepII2@0
C800h mpy  MemR4567@4, MemR0123@4 || mpy MemR4567@4offsZIDZ@2, MemR0123@4offsZIDZ@0 || add3 p0, p1, Ab@6 || R0123@4stepII2D2S@0, R4567@4stepII2D2S@2
C900h mpy  MemR4567@4, MemR0123@4 || mpy MemR4567@4offsZIDZ@2, MemR0123@4offsZIDZ@0 || sub3 p0, p1, Ab@6 || R0123@4stepII2D2S@0, R4567@4stepII2D2S@2
80C2h mpy  MemR45@0, MemR01@0 || mpy MemR45@0offsZI@9, MemR01@0offsZI@8 || add3a p0, p1, Ab@10 || R01@0stepII2@8, R45@0stepII2@9
49C8h mpy  MemR45@2, MemR01@2 || mpy MemR45@2offsZI@1, MemR01@2offsZI@0 || sub3a p0, p1, Ab@4 || R01@2stepII2@0, R45@2stepII2@1
80C8h mpy  MemR45@2, MemR01@2 || mpy MemR45@2offsZI@1, MemR01@2offsZI@0 || addsub  p0, p1, Ab@10 || R01@2stepII2@0, R45@2stepII2@1
81C8h mpy  MemR45@2, MemR01@2 || mpy MemR45@2offsZI@1, MemR01@2offsZI@0 || addsuba p0, p1, Ab@10 || R01@2stepII2@0, R45@2stepII2@1
82C8h mpy  MemR45@2, MemR01@2 || mpy MemR45@2offsZI@1, MemR01@2offsZI@0 || add     p0, p1, Ab@10 || R01@2stepII2@0, R45@2stepII2@1
83C8h mpy  MemR45@2, MemR01@2 || mpy MemR45@2offsZI@1, MemR01@2offsZI@0 || adda    p0, p1, Ab@10 || R01@2stepII2@0, R45@2stepII2@1
00C0h mpy  MemR45@3, MemR01@3 || mpy MemR45@3offsZI@2, MemR01@3offsZI@1 || sub  p0, p1, Ab@4 || R01@3stepII2@1, R45@3stepII2@2
00C1h mpy  MemR45@3, MemR01@3 || mpy MemR45@3offsZI@2, MemR01@3offsZI@1 || suba p0, p1, Ab@4 || R01@3stepII2@1, R45@3stepII2@2
0D20h mpy  MemR45@3, MemR01@3 || mpyus MemR45@3offsZI@2, MemR01@3offsZI@1 || add3a p0, p1, Ax@0, dmodi || R01@3stepII2@1, R45@3stepII2@2
0D30h mpy  MemR45@3, MemR01@3 || mpyus MemR45@3offsZI@2, MemR01@3offsZI@1 || add3a p0, p1, Ax@0, dmodj || R01@3stepII2@1, R45@3stepII2@2
4B50h mpy  MemR45@3, MemR01@3 || mpyus MemR45@3offsZI@2, MemR01@3offsZI@1 || add3a p0, p1, Ax@0, dmodij || R01@3stepII2@1, R45@3stepII2@2
D7A0h mpy  MemR45@3, MemR01@3 || mpy MemR45@3offsZI@2, MemR01@3offsZI@1 || add3    sv, p0, p1, Ax@4 || R01@3stepII2@1, R45@3stepII2@2
D7A1h mpy  MemR45@3, MemR01@3 || mpy MemR45@3offsZI@2, MemR01@3offsZI@1 || add3rnd sv, p0, p1, Ax@4 || R01@3stepII2@1, R45@3stepII2@2
9861h mpy  MemR45@4, MemR01@4 || mpy MemR45@4offsZI@3, MemR01@4offsZI@2 || add3  p0, p1, Ax@8, dmodj  || R01@4stepII2@2, R45@4stepII2@3
9862h mpy  MemR45@4, MemR01@4 || mpy MemR45@4offsZI@3, MemR01@4offsZI@2 || add3  p0, p1, Ax@8, dmodi  || R01@4stepII2@2, R45@4stepII2@3
9863h mpy  MemR45@4, MemR01@4 || mpy MemR45@4offsZI@3, MemR01@4offsZI@2 || add3  p0, p1, Ax@8, dmodij || R01@4stepII2@2, R45@4stepII2@3
98E1h mpy  MemR45@4, MemR01@4 || mpy MemR45@4offsZI@3, MemR01@4offsZI@2 || add3a p0, p1, Ax@8, dmodj  || R01@4stepII2@2, R45@4stepII2@3
98E2h mpy  MemR45@4, MemR01@4 || mpy MemR45@4offsZI@3, MemR01@4offsZI@2 || add3a p0, p1, Ax@8, dmodi  || R01@4stepII2@2, R45@4stepII2@3
98E3h mpy  MemR45@4, MemR01@4 || mpy MemR45@4offsZI@3, MemR01@4offsZI@2 || add3a p0, p1, Ax@8, dmodij || R01@4stepII2@2, R45@4stepII2@3
4DA0h mpy  y0, MemR04@3 || mpyus y1, MemR04@3offsZI@2 || sub3  p0, p1, Ax@4 || R04@3stepII2@2
4DA1h mpy  y0, MemR04@3 || mpyus y1, MemR04@3offsZI@2 || sub3a p0, p1, Ax@4 || R04@3stepII2@2
4DA2h mpy  y0, MemR04@3 || mpyus y1, MemR04@3offsZI@2 || add3  p0, p1, Ax@4 || R04@3stepII2@2
4DA3h mpy  y0, MemR04@3 || mpyus y1, MemR04@3offsZI@2 || add3a p0, p1, Ax@4 || R04@3stepII2@2
94E0h mpy  y0, MemR04@4 || mpy   y1, MemR04@4offsZI@3 || sub3  p0, p1, Ax@8 || R04@4stepII2@3
94E2h mpy  y0, MemR04@4 || mpy   y1, MemR04@4offsZI@3 || sub3a p0, p1, Ax@8 || R04@4stepII2@3
94E4h mpy  y0, MemR04@4 || mpy   y1, MemR04@4offsZI@3 || add3  p0, p1, Ax@8 || R04@4stepII2@3
94E6h mpy  y0, MemR04@4 || mpy   y1, MemR04@4offsZI@3 || add3a p0, p1, Ax@8 || R04@4stepII2@3
94E1h mpy  y0, MemR04@4 || mpysu y1, MemR04@4offsZI@3 || sub3  p0, p1, Ax@8 || R04@4stepII2@3
94E3h mpy  y0, MemR04@4 || mpysu y1, MemR04@4offsZI@3 || sub3a p0, p1, Ax@8 || R04@4stepII2@3
94E5h mpy  y0, MemR04@4 || mpysu y1, MemR04@4offsZI@3 || add3  p0, p1, Ax@8 || R04@4stepII2@3
94E7h mpy  y0, MemR04@4 || mpysu y1, MemR04@4offsZI@3 || add3a p0, p1, Ax@8 || R04@4stepII2@3
8862h mpy  y0, x1 || mpy   MemR04@4, x0 || sub3  p0, p1, Ax@8 || R04@4stepII2@3
8A62h mpy  y0, x1 || mpy   MemR04@4, x0 || add3  p0, p1, Ax@8 || R04@4stepII2@3
4D88h mpy  y0, x1 || mpy   y1, x0 || sub p0, p1, Ax@1
5E24h mpy  y0, x1 || mpy   y1, x0 || add p0, p1, Ab@0
8061h mpy  y0, x1 || mpy   y1, x0 || add3  p0, p1, Ab@8
8071h mpy  y0, x1 || mpy   y1, x0 || add3a p0, p1, Ab@8
8461h mpy  y0, x1 || mpy   y1, x0 || sub3  p0, p1, Ab@8
8471h mpy  y0, x1 || mpy   y1, x0 || sub3a p0, p1, Ab@8
D484h mpy  y0, x1 || mpy   y1, x0 || add3aa p0, p1, Ab@0
D49Dh mpy  y0, x1 || mpy   y1, x0 || sub p0, p1, Bx@5
D4A0h mpy  y0, x1 || mpy   y1, x0 || addsub p0, p1, Ab@0
4FA0h mpy  y0, x1 || mpy y1, x0 || add3 p0, p1, Ab@3 || mov Axh@6, MemR04@1 || mov Bxh@2, MemR04@1offsZI@0 || R04@1stepII2@0
5818h mpy  y0, x1 || mpy y1, x0 || addsub    sv, p0, p1, Ax@0 || mov Axh@0, MemR0425@7 || mov Axh@not0, MemR0425@7offsZI@6 || R0425@7stepII2@6  ;override 5800h+18h (mov a0, Register)
5838h mpy  y0, x1 || mpy y1, x0 || addsubrnd sv, p0, p1, Ax@0 || mov Axh@0, MemR0425@7 || mov Axh@not0, MemR0425@7offsZI@6 || R0425@7stepII2@6  ;override 5800h+38h (mov a1, Register)
80D0h mpy  y0, x1 || mpy y1, x0 || addsub    sv, p0, p1, Ax@10 || mov Axh@9, MemR04@3 || mov Bxh@8, MemR04@3offsZI@2 || R04@3stepII2@2
80D1h mpy  y0, x1 || mpy y1, x0 || addsubrnd sv, p0, p1, Ax@10 || mov Axh@9, MemR04@3 || mov Bxh@8, MemR04@3offsZI@2 || R04@3stepII2@2
80D2h mpy  y0, x1 || mpy y1, x0 || add3      sv, p0, p1, Ax@10 || mov Axh@9, MemR04@3 || mov Bxh@8, MemR04@3offsZI@2 || R04@3stepII2@2
80D3h mpy  y0, x1 || mpy y1, x0 || add3rnd   sv, p0, p1, Ax@10 || mov Axh@9, MemR04@3 || mov Bxh@8, MemR04@3offsZI@2 || R04@3stepII2@2
D3A0h mpy  y0, x1 || mpy y1, x0 || addsub p0, p1, Ab@3 || mov Axh@6, MemR04@1 || mov Bxh@2, MemR04@1offsZI@0 || R04@1stepII2@0
4D89h mpy  y0, x1 || mpyus y1, x0 || sub p0, p1, Ax@1
5F24h mpy  y0, x1 || mpyus y1, x0 || add p0, p1, Ab@0
8069h mpy  y0, x1 || mpyus y1, x0 || add3  p0, p1, Ab@8
8079h mpy  y0, x1 || mpyus y1, x0 || add3a p0, p1, Ab@8
8469h mpy  y0, x1 || mpyus y1, x0 || sub3  p0, p1, Ab@8
8479h mpy  y0, x1 || mpyus y1, x0 || sub3a p0, p1, Ab@8
D584h mpy  y0, x1 || mpyus y1, x0 || add3aa p0, p1, Ab@0
D59Dh mpy  y0, x1 || mpyus y1, x0 || sub p0, p1, Bx@5
D5A0h mpy  y0, x1 || mpyus y1, x0 || addsub p0, p1, Ab@0
0800h mpyi NoReverse, Implied p0, y0, Imm8s@0   ;multiply  ;aka "mpys"
D100h mpysu MemR45@2, MemR0123@0 || R0123@0stepZIDS@3, R45@2stepZIDS@5
8100h mpysu MemRn@0, Imm16@16    || Rn@0stepZIDS@3
8120h mpysu y0, MemRn@0          || Rn@0stepZIDS@3
8140h mpysu y0, Register@0
CA00h mpysu MemR45@5, MemR01@5 || mpysu MemR45@5offsZI@4, MemR01@5offsZI@3 || sub3a  p0, p1, Ab@6 || R01@5stepII2@3, R45@5stepII2@4
CA01h mpysu MemR45@5, MemR01@5 || mpyus MemR45@5offsZI@4, MemR01@5offsZI@3 || sub3a  p0, p1, Ab@6 || R01@5stepII2@3, R45@5stepII2@4
CA02h mpysu MemR45@5, MemR01@5 || mpysu MemR45@5offsZI@4, MemR01@5offsZI@3 || sub3aa p0, p1, Ab@6 || R01@5stepII2@3, R45@5stepII2@4
CA03h mpysu MemR45@5, MemR01@5 || mpyus MemR45@5offsZI@4, MemR01@5offsZI@3 || sub3aa p0, p1, Ab@6 || R01@5stepII2@3, R45@5stepII2@4
CA04h mpysu MemR45@5, MemR01@5 || mpysu MemR45@5offsZI@4, MemR01@5offsZI@3 || add3a  p0, p1, Ab@6 || R01@5stepII2@3, R45@5stepII2@4
CA05h mpysu MemR45@5, MemR01@5 || mpyus MemR45@5offsZI@4, MemR01@5offsZI@3 || add3a  p0, p1, Ab@6 || R01@5stepII2@3, R45@5stepII2@4
CA06h mpysu MemR45@5, MemR01@5 || mpysu MemR45@5offsZI@4, MemR01@5offsZI@3 || add3aa p0, p1, Ab@6 || R01@5stepII2@3, R45@5stepII2@4
CA07h mpysu MemR45@5, MemR01@5 || mpyus MemR45@5offsZI@4, MemR01@5offsZI@3 || add3aa p0, p1, Ab@6 || R01@5stepII2@3, R45@5stepII2@4
5EA2h mpysu y0, r6
D080h msu  MemR45@2,MemR0123@0,Ax@8 || R0123@0stepZIDS@3, R45@2stepZIDS@5
90C0h msu  MemRn@0, Imm16@16,  Ax@8 || Rn@0stepZIDS@3 ;multiply, subtract
9080h msu  y0, MemRn@0, Ax@8 || Rn@0stepZIDS@3
90A0h msu  y0, Register@0, Ax@8
B000h msu  y0,MemImm8@0, Ax@8
9462h msu  y0, r6, Ax@0
8264h msusu y0, MemR0425@3, Ax@8 || R0425@3stepII2D2S@0
6790h neg  Ax@12, Cond@0 ;aX=0-aX
0000h nop
94C0h norm Ax@8, Bogus MemRn@0 || Rn@0stepZIDS@3  ;if N=0 (aX=aX*2,rN+/-)
6780h not  Ax@12, Cond@0 ;aX=not aX
D4F8h or   MemImm16@16, Ax@8
A000h or   MemImm8@0, Ax@8
80C0h or   Imm16@16, Ax@8
C000h or   Imm8u@0, Ax@8
D4D8h or   MemR7Imm16@16, Ax@8
4000h or   MemR7Imm7s@0, Ax@8
8080h or   MemRn@0, Ax@8 || Rn@0stepZIDS@3
80A0h or   RegisterP0@0, Ax@8
D291h or   Ab@10, Ax@6, Ax@5
D4A4h or   Ax@8, Bx@1, Ax@0
D3C4h or   b0, Bx@1, Ax@0
D7C4h or   b1, Bx@1, Ax@0
D388h or   r6, Ax@4
67B0h pacr Implied Const8000h, Implied p0, Ax@12, Cond@0 ;aX=shfP+8000h
D7C2h pacr1 Implied Const8000h, Implied p1, Ax@0
5E60h pop  Register@0
47B4h pop  Abe@0
80C7h pop  ArArpSttMod@8
0006h pop  Bx@5, Unused1@0
D7F4h pop  prpage, Unused2@0
D496h pop  Px@0
0024h pop  r6, Unused1@0
D7F0h pop  repc, Unused2@0
D494h pop  x0
D495h pop  x1
0004h pop  y1, Unused1@0
47B0h popa Ab@0
5F40h push Imm16@16
5E40h push Register@0
D7C8h push Abe@1, Unused1@0
D3D0h push ArArpSttMod@0
D7FCh push prpage, Unused2@0
D78Ch push Px@1, Unused1@0
D4D7h push r6, Unused1@5
D7F8h push repc, Unused2@0
D4D4h push x0, Unused1@5
D4D5h push x1, Unused1@5
D4D6h push y1, Unused1@5
4384h pusha Ax@6, Unused2@0
D788h pusha Bx@1, Unused1@0
0C00h rep  Imm8u@0    ;repeat next opcode N+1 times
0D00h rep  Register@0 ;repeat next opcode N+1 times
0002h rep  r6, Unused1@0
4580h ret  Cond@0      ;=pop pc
D780h retd    ;delayed return (after 2 clks)
45C0h reti Cond@0          ;Don't context switch
45D0h reti Cond@0, context ;Do context switch
D7C0h retid   ;delayed, from interrupt
D3C3h retid context
0900h rets Imm8u@0          ;ret+dealloc sp (for INCOMING pushed params)
67A0h rnd  Implied Const8000h, Ax@12, Cond@0 ;aX=aX+8000h
6750h rol  Implied Const1,     Ax@12, Cond@0 ;aX=aX rcl 1 (37bit rotate)
6F50h rol  Implied Const1,     Bx@12, Cond@0 ;bX=bX rcl 1 (37bit rotate)
6740h ror  Implied Const1,     Ax@12, Cond@0 ;aX=aX rcr 1 (37bit rotate)
6F40h ror  Implied Const1,     Bx@12, Cond@0 ;bX=bX rcr 1 (37bit rotate)
E300h rst  Imm16@16, MemImm8@0
82E0h rst  Imm16@16, MemRn@0 || Rn@0stepZIDS@3
83E0h rst  Imm16@16, Register@0
47B9h rst  Imm16@16, r6
4388h rst  Imm16@16, SttMod@0
E100h set  Imm16@16, MemImm8@0
80E0h set  Imm16@16, MemRn@0 || Rn@0stepZIDS@3
81E0h set  Imm16@16, Register@0
47B8h set  Imm16@16, r6
43C8h set  Imm16@16, SttMod@0
D280h shfc Implied sv, Ab@10, Ab@5, Cond@0
9240h shfi Implied Imm6s@0, Ab@10, Ab@7, Bogus Imm6s@0
6720h shl  Implied Const1,     Ax@12, Cond@0 ;aX=aX*2
6F20h shl  Implied Const1,     Bx@12, Cond@0 ;bX=bX*2
6730h shl4 Implied Const4,     Ax@12, Cond@0 ;aX=aX*10h
6F30h shl4 Implied Const4,     Bx@12, Cond@0 ;bX=bX*10h
6700h shr  Implied Const1,     Ax@12, Cond@0 ;aX=aX/2
6F00h shr  Implied Const1,     Bx@12, Cond@0 ;bX=bX/2
6710h shr4 Implied Const4,     Ax@12, Cond@0 ;aX=aX/10h
6F10h shr4 Implied Const4,     Bx@12, Cond@0 ;bX=bX/10h
BA00h sqr  MemImm8@0
9A80h sqr  MemRn@0 || Rn@0stepZIDS@3
9AA0h sqr  Register@0
D790h sqr  Abh@2 || sqr Abl@2 || add3 p0, p1, Ab@0
49C4h sqr  Abh@4 || mpysu Abh@4, Abl@4 || add3a p0, p1, Ab@0
4B00h sqr  MemR0425@4 || sqr MemR0425@4offsZIDZ@2 || add3 p0, p1, Ab@0 || R0425@4stepII2D2S@2
5F41h sqr  r6
BC00h sqra MemImm8@0, Ax@8
9C80h sqra MemRn@0, Ax@8 || Rn@0stepZIDS@3
9CA0h sqra Register@0, Ax@8
9062h sqra r6, Ax@8, Unused1@0
D4FFh sub  MemImm16@16, Ax@8
AE00h sub  MemImm8@0, Ax@8
8EC0h sub  Imm16@16, Ax@8
CE00h sub  Imm8u@0, Ax@8
D4DFh sub  MemR7Imm16@16, Ax@8
4E00h sub  MemR7Imm7s@0, Ax@8
8E80h sub  MemRn@0, Ax@8 || Rn@0stepZIDS@3
8EA0h sub  RegisterP0@0, Ax@8
8A61h sub  Ab@3, Bx@8
8861h sub  Bx@4, Ax@3
8064h sub  MemR01@8, sv, Abh@3 || add MemR01@8offsZI@0, sv, Abl@3 || mov MemR45@8, sv || R01@8stepII2@0, R45@8stepII2@1
5DE0h sub  MemR04@1, sv, Abh@2 || add MemR04@1offsZI@0, sv, Abl@2 || R04@1stepII2@0
6FC0h sub  MemR45@2, MemR01@2, Abh@3 || add MemR45@2offsZI@1, MemR01@2offsZI@0, Abl@3 || R01@2stepII2@0, R45@2stepII2@1
6FE0h sub  MemR45@2, MemR01@2, Abh@3 || sub MemR45@2offsZI@1, MemR01@2offsZI@0, Abl@3 || R01@2stepII2@0, R45@2stepII2@1
5D80h sub  MemR45@2, sv, Abh@3 || add MemR45@2offsZI@1, sv, Abl@3 || mov MemR01@2, sv || R01@2stepII2@0, R45@2stepII2@1
5DC2h sub  p0, p1, Ab@2
D4B9h sub  p1, Ax@8
8FD0h sub  Px@1, Bx@0
D38Fh sub  r6, Ax@4
80C6h sub3 p0, p1, Ab@10
82C6h sub3a p0, p1, Ab@10
83C6h sub3aa p0, p1, Ab@10
5DC3h suba p0, p1, Ab@2
B600h subh MemImm8@0, Ax@8
9680h subh MemRn@0, Ax@8 || Rn@0stepZIDS@3
96A0h subh Register@0, Ax@8
5E23h subh r6, Ax@8
B800h subl MemImm8@0, Ax@8
9880h subl MemRn@0, Ax@8 || Rn@0stepZIDS@3
98A0h subl Register@0, Ax@8
5E22h subl r6, Ax@8
EF00h subv Imm16@16, MemImm8@0
8EE0h subv Imm16@16, MemRn@0 || Rn@0stepZIDS@3
8FE0h subv Imm16@16, Register@0
47BFh subv Imm16@16, r6
4980h swap SwapTypes4@0
0020h trap                  ;software interrupt
A800h tst0 Axl@8, MemImm8@0
8880h tst0 Axl@8, MemRn@0 || Rn@0stepZIDS@3
88A0h tst0 Axl@8, Register@0
E900h tst0 Imm16@16, MemImm8@0
88E0h tst0 Imm16@16, MemRn@0 || Rn@0stepZIDS@3
89E0h tst0 Imm16@16, Register@0
D38Ch tst0 Axl@4, r6
47BCh tst0 Imm16@16, r6
9470h tst0 Imm16@16, SttMod@0
AA00h tst1 Axl@8, MemImm8@0 Implied Not
8A80h tst1 Axl@8, MemRn@0 Implied Not || Rn@0stepZIDS@3
8AA0h tst1 Axl@8, Register@0 Implied Not
EB00h tst1 Imm16@16, MemImm8@0 Implied Not
8AE0h tst1 Imm16@16, MemRn@0 Implied Not || Rn@0stepZIDS@3
8BE0h tst1 Imm16@16, Register@0 Implied Not
D38Dh tst1 Axl@4, r6 Implied Not
47BDh tst1 Imm16@16, r6 Implied Not
9478h tst1 Imm16@16, SttMod@0 Implied Not
80C1h tst4b a0l, MemR0425@10 || R0425@10stepII2D2S@8
4780h tst4b a0l, MemR0425@2, Ax@4 || R0425@2stepII2D2S@0
F000h tstb NoReverse, Implied Not MemImm8@0, Imm4bitno@8
9020h tstb NoReverse, Implied Not MemRn@0, Imm4bitno@8 || Rn@0stepZIDS@3
9000h tstb NoReverse, Implied Not Register@0, Imm4bitno@8
9018h tstb NoReverse, Implied Not r6, Imm4bitno@8  ;override tstb a0,Imm4
0028h tstb NoReverse, Implied Not SttMod@0, Imm4bitno@16, Unused12@20
5F45h vtrclr vtr0
5F47h vtrclr vtr0, vtr1
5F46h vtrclr vtr1
D383h vtrmov Axl@4
D29Ah vtrmov vtr0, Axl@0
D69Ah vtrmov vtr1, Axl@0
D781h vtrshr
D4FAh xor  MemImm16@16, Ax@8
A400h xor  MemImm8@0, Ax@8
84C0h xor  Imm16@16, Ax@8
C400h xor  Imm8u@0, Ax@8
D4DAh xor  MemR7Imm16@16, Ax@8
4400h xor  MemR7Imm7s@0, Ax@8
8480h xor  MemRn@0, Ax@8 || Rn@0stepZIDS@3
84A0h xor  RegisterP0@0, Ax@8
D38Ah xor  r6, Ax@4
8800h undefined Unused5@0, Unused1@8 ;(mpy/mpys without A in bit11)
8820h undefined Unused5@0, Unused1@8 ;(mpy/mpys without A in bit11)
8840h undefined Unused5@0, Unused1@8 ;(mpy/mpys without A in bit11)
D800h undefined Unused7@0, Unused1@8 ;(mpy/mpys without A in bit11)
9B80h undefined Unused6@0  ;(sqr without A in bit8)
BB00h undefined Unused8@0  ;(sqr without A in bit8)
E800h undefined Unused8@0  ;(mpy without A in bit11)
5EA1h undefined Unused1@1  ;(mpy/mpys without A in bit11)
5DFCh undefined
8CDEh undefined
D3C1h undefined
5EB4h undefined Unused2@0
)"
