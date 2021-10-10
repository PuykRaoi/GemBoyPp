#include "lr35902.h"
#include "systemBus.h"

#include <iostream>

void LR35902::Initialize()
{
    a  = 0;
    b  = 0;
    c  = 0;
    d  = 0;
    e  = 0;
    h  = 0;
    l  = 0;
    sp = 0;
    pc = 0;
    cc = {0,0,0,0,0};
    int_enable = 0;

    instructions_executed = 0;
}

void LR35902::PrintState()
{
    std::cout << "********* CPU STATE *********" << std::endl;
    std::cout << "a: " << std::hex << (int)a << std::endl;
    std::cout << "b: " << std::hex << (int)b << std::endl;
    std::cout << "c: " << std::hex << (int)c << std::endl;
    std::cout << "d: " << std::hex << (int)d << std::endl;
    std::cout << "e: " << std::hex << (int)e << std::endl;
    std::cout << "h: " << std::hex << (int)h << std::endl;
    std::cout << "l: " << std::hex << (int)l << std::endl;
    std::cout << "pc: " << std::hex << (int)pc << std::endl;
    std::cout << "sp: " << std::hex << (int)sp << std::endl;
    std::cout << "n: " << std::hex << (int)cc.n << std::endl;
    std::cout << "h: " << std::hex << (int)cc.h << std::endl;
    std::cout << "z: " << std::hex << (int)cc.z << std::endl;
    std::cout << "c: " << std::hex << (int)cc.c << std::endl;
}

void LR35902::UnimplementedInstruction(uint8_t opcode)
{
    std::cout << "Found unimplemented instruction: "
        << std::hex << (int)opcode << std::endl;
    halted = true;
}

/* void LR35902::EmulateCycles(uint32_t num_cycles) */
/* { */
/*     cycles = 0; */
/*     while(cycles < num_cycles) { */
/*         RegularInstruction(); */
/*     } */
/* } */

void LR35902::ExecuteInstruction()
{
    uint8_t opcode = Read(pc);
    uint8_t arg1 =   Read(pc+1);
    uint8_t arg2 =   Read(pc+2);
    Disassemble(opcode, arg1, arg2);
    NonPrefixedInstruction(opcode);
}

/* void LR35902::Interrupt(uint8_t opcode) */
/* { */
/*     // If interrupts are enabled, service the request */
/*     if (int_enable) { */
/*         int_enable = false; */
/*         ExecuteInstruction(opcode); */
/*     } */
/* } */

void LR35902::NonPrefixedInstruction(uint8_t opcode)
{
#define BYTE1 Read(pc+1)
#define BYTE2 Read(pc+2)
    // Decode and execute instruction
    switch(opcode)
    {
        case 0x00:      NOP ();                                   break;
/*         case 0x01:      LXI (b, c, BYTE2, BYTE1);                 break; */
/*         case 0x02:   STAX_B ();                                   break; */
/*         case 0x03:      INX (b, c);                               break; */
/*         case 0x04:    INR_r (b);                                  break; */
/*         case 0x05:    DCR_r (b);                                  break; */
/*         case 0x06:      MVI (b, BYTE1);                           break; */
/*         case 0x07:      RLC ();                                   break; */
/*         /1*   0x08: - *1/ */
/*         case 0x09:      DAD (b, c);                               break; */
/*         case 0x0a:     LDAX (b, c);                               break; */
/*         case 0x0b:    DCX_B ();                                   break; */
/*         case 0x0c:    INR_r (c);                                  break; */
/*         case 0x0d:    DCR_r (c);                                  break; */
        case 0x0e:      MVI (c, BYTE1);                           break;
/*         case 0x0f:      RRC ();                                   break; */
/*         /1*   0x10: - *1/ */
        case 0x11:      LXI (d, e, BYTE2, BYTE1);                 break;
/*         case 0x12:   STAX_D ();                                   break; */
/*         case 0x13:      INX (d, e);                               break; */
/*         case 0x14:    INR_r (d);                                  break; */
/*         case 0x15:    DCR_r (d);                                  break; */
/*         case 0x16:      MVI (d, BYTE1);                           break; */
/*         case 0x17:      RAL ();                                   break; */
/*         /1*   0x18: - *1/ */
/*         case 0x19:      DAD (d, e);                               break; */
/*         case 0x1a:     LDAX (d, e);                               break; */
/*         case 0x1b:    DCX_D ();                                   break; */
/*         case 0x1c:    INR_r (e);                                  break; */
/*         case 0x1d:    DCR_r (e);                                  break; */
/*         case 0x1e:      MVI (e, BYTE1);                           break; */
/*         case 0x1f:      RAR ();                                   break; */
/*         /1*   0x20: - *1/ */
        case 0x21:      LXI (h, l, BYTE2, BYTE1);                 break;
/*         case 0x22:     SHLD (BYTE2, BYTE1);                       break; */
/*         case 0x23:      INX (h, l);                               break; */
/*         case 0x24:    INR_r (h);                                  break; */
/*         case 0x25:    DCR_r (h);                                  break; */
/*         case 0x26:      MVI (h, BYTE1);                           break; */
/*         case 0x27: pc+=1; break; //TODO SKIP! */
/*         /1*   0x28: - *1/ */
/*         case 0x29:      DAD (h, l);                               break; */
        case 0x2a:     LDAHLI ();                       break;
/*         case 0x2b:    DCX_H ();                                   break; */
/*         case 0x2c:    INR_r (l);                                  break; */
/*         case 0x2d:    DCR_r (l);                                  break; */
/*         case 0x2e:      MVI (l, BYTE1);                           break; */
/*         case 0x2f:      CMA ();                                   break; */
/*         /1*   0x30: - *1/ */
/*         case 0x31:   LXI_SP (BYTE2, BYTE1);                       break; */
/*         case 0x32:      STA (BYTE2, BYTE1);                       break; */
/*         case 0x33:   INX_SP ();                                   break; */
/*         case 0x34:    INR_M ();                                   break; */
/*         case 0x35:    DCR_M ();                                   break; */
/*         case 0x36:    MVI_M (BYTE1);                              break; */
/*         case 0x37:      STC ();                                   break; */
/*         /1*   0x38: - *1/ */
/*         case 0x39:   DAD_SP ();                                   break; */
/*         case 0x3a:      LDA (BYTE2, BYTE1);                       break; */
/*         case 0x3b:      DCX_SP ();                                break; */
/*         case 0x3c:    INR_r (a);                                  break; */
/*         case 0x3d:    DCR_r (a);                                  break; */
/*         case 0x3e:      MVI (a, BYTE1);                           break; */
/*         case 0x3f:      CMC ();                                   break; */
/*         case 0x40:  MOV_r_r (b, b);                               break; */
/*         case 0x41:  MOV_r_r (b, c);                               break; */
/*         case 0x42:  MOV_r_r (b, d);                               break; */
/*         case 0x43:  MOV_r_r (b, e);                               break; */
/*         case 0x44:  MOV_r_r (b, h);                               break; */
/*         case 0x45:  MOV_r_r (b, l);                               break; */
/*         case 0x46:  MOV_r_m (b);                                  break; */
        case 0x47:  MOV_r_r (b, a);                               break;
/*         case 0x48:  MOV_r_r (c, b);                               break; */
/*         case 0x49:  MOV_r_r (c, c);                               break; */
/*         case 0x4a:  MOV_r_r (c, d);                               break; */
/*         case 0x4b:  MOV_r_r (c, e);                               break; */
/*         case 0x4c:  MOV_r_r (c, h);                               break; */
/*         case 0x4d:  MOV_r_r (c, l);                               break; */
/*         case 0x4e:  MOV_r_m (c);                                  break; */
/*         case 0x4f:  MOV_r_r (c, a);                               break; */
/*         case 0x50:  MOV_r_r (d, b);                               break; */
/*         case 0x51:  MOV_r_r (d, c);                               break; */
/*         case 0x52:  MOV_r_r (d, d);                               break; */
/*         case 0x53:  MOV_r_r (d, e);                               break; */
/*         case 0x54:  MOV_r_r (d, h);                               break; */
/*         case 0x55:  MOV_r_r (d, l);                               break; */
/*         case 0x56:  MOV_r_m (d);                                  break; */
/*         case 0x57:  MOV_r_r (d, a);                               break; */
/*         case 0x58:  MOV_r_r (e, b);                               break; */
/*         case 0x59:  MOV_r_r (e, c);                               break; */
/*         case 0x5a:  MOV_r_r (e, d);                               break; */
/*         case 0x5b:  MOV_r_r (e, e);                               break; */
/*         case 0x5c:  MOV_r_r (e, h);                               break; */
/*         case 0x5d:  MOV_r_r (e, l);                               break; */
/*         case 0x5e:  MOV_r_m (e);                                  break; */
/*         case 0x5f:  MOV_r_r (e, a);                               break; */
/*         case 0x60:  MOV_r_r (h, b);                               break; */
/*         case 0x61:  MOV_r_r (h, c);                               break; */
/*         case 0x62:  MOV_r_r (h, d);                               break; */
/*         case 0x63:  MOV_r_r (h, e);                               break; */
/*         case 0x64:  MOV_r_r (h, h);                               break; */
/*         case 0x65:  MOV_r_r (h, l);                               break; */
/*         case 0x66:  MOV_r_m (h);                                  break; */
/*         case 0x67:  MOV_r_r (h, a);                               break; */
/*         case 0x68:  MOV_r_r (l, b);                               break; */
/*         case 0x69:  MOV_r_r (l, c);                               break; */
/*         case 0x6a:  MOV_r_r (l, d);                               break; */
/*         case 0x6b:  MOV_r_r (l, e);                               break; */
/*         case 0x6c:  MOV_r_r (l, h);                               break; */
/*         case 0x6d:  MOV_r_r (l, l);                               break; */
/*         case 0x6e:  MOV_r_m (l);                                  break; */
/*         case 0x6f:  MOV_r_r (l, a);                               break; */
/*         case 0x70:  MOV_m_r (b);                                  break; */
/*         case 0x71:  MOV_m_r (c);                                  break; */
/*         case 0x72:  MOV_m_r (d);                                  break; */
/*         case 0x73:  MOV_m_r (e);                                  break; */
/*         case 0x74:  MOV_m_r (h);                                  break; */
/*         case 0x75:  MOV_m_r (l);                                  break; */
/*         /1* case 0x76:  HLT ();                                  break; *1/ */
/*         case 0x77:  MOV_m_r (a);                                  break; */
/*         case 0x78:  MOV_r_r (a, b);                               break; */
/*         case 0x79:  MOV_r_r (a, c);                               break; */
/*         case 0x7a:  MOV_r_r (a, d);                               break; */
/*         case 0x7b:  MOV_r_r (a, e);                               break; */
/*         case 0x7c:  MOV_r_r (a, h);                               break; */
/*         case 0x7d:  MOV_r_r (a, l);                               break; */
/*         case 0x7e:  MOV_r_m (a);                                  break; */
/*         case 0x7f:  MOV_r_r (a, a);                               break; */
/*         case 0x80:    ADD_r (b);                                  break; */
/*         case 0x81:    ADD_r (c);                                  break; */
/*         case 0x82:    ADD_r (d);                                  break; */
/*         case 0x83:    ADD_r (e);                                  break; */
/*         case 0x84:    ADD_r (h);                                  break; */
/*         case 0x85:    ADD_r (l);                                  break; */
/*         case 0x86:    ADD_M ();                                   break; */
/*         case 0x87:    ADD_r (a);                                  break; */
/*         case 0x88:    ADC_r (b);                                  break; */
/*         case 0x89:    ADC_r (c);                                  break; */
/*         case 0x8a:    ADC_r (d);                                  break; */
/*         case 0x8b:    ADC_r (e);                                  break; */
/*         case 0x8c:    ADC_r (h);                                  break; */
/*         case 0x8d:    ADC_r (l);                                  break; */
/*         case 0x8e:    ADC_M ();                                   break; */
/*         case 0x8f:    ADC_r (a);                                  break; */
/*         case 0x90:    SUB_r (b);                                  break; */
/*         case 0x91:    SUB_r (c);                                  break; */
/*         case 0x92:    SUB_r (d);                                  break; */
/*         case 0x93:    SUB_r (e);                                  break; */
/*         case 0x94:    SUB_r (h);                                  break; */
/*         case 0x95:    SUB_r (l);                                  break; */
/*         case 0x96:    SUB_M ();                                   break; */
/*         case 0x97:    SUB_r (a);                                  break; */
/*         case 0x98:    SBB_r (b);                                  break; */
/*         case 0x99:    SBB_r (c);                                  break; */
/*         case 0x9a:    SBB_r (d);                                  break; */
/*         case 0x9b:    SBB_r (e);                                  break; */
/*         case 0x9c:    SBB_r (h);                                  break; */
/*         case 0x9d:    SBB_r (l);                                  break; */
/*         case 0x9e:    SBB_M ();                                   break; */
/*         case 0x9f:    SBB_r (a);                                  break; */
/*         case 0xa0:    ANA_r (b);                                  break; */
/*         case 0xa1:    ANA_r (c);                                  break; */
/*         case 0xa2:    ANA_r (d);                                  break; */
/*         case 0xa3:    ANA_r (e);                                  break; */
/*         case 0xa4:    ANA_r (h);                                  break; */
/*         case 0xa5:    ANA_r (l);                                  break; */
/*         case 0xa6:    ANA_M ();                                   break; */
/*         case 0xa7:    ANA_r (a);                                  break; */
/*         case 0xa8:    XRA_r (b);                                  break; */
/*         case 0xa9:    XRA_r (c);                                  break; */
/*         case 0xaa:    XRA_r (d);                                  break; */
/*         case 0xab:    XRA_r (e);                                  break; */
/*         case 0xac:    XRA_r (h);                                  break; */
/*         case 0xad:    XRA_r (l);                                  break; */
/*         case 0xae:    XRA_M ();                                   break; */
/*         case 0xaf:    XRA_r (a);                                  break; */
/*         case 0xb0:    ORA_r (b);                                  break; */
/*         case 0xb1:    ORA_r (c);                                  break; */
/*         case 0xb2:    ORA_r (d);                                  break; */
/*         case 0xb3:    ORA_r (e);                                  break; */
/*         case 0xb4:    ORA_r (h);                                  break; */
/*         case 0xb5:    ORA_r (l);                                  break; */
/*         case 0xb6:    ORA_M ();                                   break; */
/*         case 0xb7:    ORA_r (a);                                  break; */
/*         case 0xb8:    CMP_r (b);                                  break; */
/*         case 0xb9:    CMP_r (c);                                  break; */
/*         case 0xba:    CMP_r (d);                                  break; */
/*         case 0xbb:    CMP_r (e);                                  break; */
/*         case 0xbc:    CMP_r (h);                                  break; */
/*         case 0xbd:    CMP_r (l);                                  break; */
/*         case 0xbe:    CMP_M ();                                   break; */
/*         case 0xbf:    CMP_r (a);                                  break; */
/*         case 0xc0:   R_cond (!cc.z);                              break; */
/*         case 0xc1:   POP_rp (b, c);                               break; */
/*         case 0xc2:   J_Cond (BYTE2, BYTE1, !cc.z);                break; */
        case 0xc3:   J_Cond (BYTE2, BYTE1, true);                 break;
/*         case 0xc4:   C_Cond (BYTE2, BYTE1, (!cc.z));              break; */
/*         case 0xc5:  PUSH_rp (b, c);                               break; */
/*         case 0xc6:      ADI (BYTE1);                              break; */
/*         case 0xc7:      RST (0x0);                                break; */
/*         case 0xc8:   R_cond (cc.z);                               break; */
/*         case 0xc9:      RET ();                                   break; */
/*         case 0xca:   J_Cond (BYTE2, BYTE1, cc.z);                 break; */
/*         /1*   0xcb: - *1/ */
/*         case 0xcc:   C_Cond (BYTE2, BYTE1, cc.z);                 break; */
/*         case 0xcd:     CALL (BYTE2, BYTE1);                       break; */
/*         case 0xce:      ACI (BYTE1);                              break; */
/*         case 0xcf:      RST (0x1);                                break; */
/*         case 0xd0:   R_cond (!cc.cy);                             break; */
/*         case 0xd1:   POP_rp (d, e);                               break; */
/*         case 0xd2:   J_Cond (BYTE2, BYTE1, !cc.cy);               break; */
/*         case 0xd3:      OUT (BYTE1);                              break; */
/*         case 0xd4:   C_Cond (BYTE2, BYTE1, !cc.cy);               break; */
/*         case 0xd5:  PUSH_rp (d, e);                               break; */
/*         case 0xd6:      SUI (BYTE1);                              break; */
/*         case 0xd7:      RST (0x2);                                break; */
/*         case 0xd8:   R_cond (cc.cy);                              break; */
/*         /1*   0xd9: - *1/ */
/*         case 0xda:   J_Cond (BYTE2, BYTE1, cc.cy);                break; */
/*         case 0xdb:       IN (BYTE1);                              break; */
/*         case 0xdc:   C_Cond (BYTE2, BYTE1, cc.cy);                break; */
/*         /1*   0xdd: - *1/ */
/*         case 0xde:      SBI (BYTE1);                              break; */
/*         case 0xdf:      RST (0x3);                                break; */
/*         case 0xe0:   R_cond (!cc.p);                               break; */
/*         case 0xe1:   POP_rp (h, l);                               break; */
/*         case 0xe2:   J_Cond (BYTE2, BYTE1, !cc.p);                break; */
/*         case 0xe3:     XTHL ();                                   break; */
/*         case 0xe4:   C_Cond (BYTE2, BYTE1, !cc.p);                break; */
/*         case 0xe5:  PUSH_rp (h, l);                               break; */
/*         case 0xe6:      ANI (BYTE1);                              break; */
/*         case 0xe7:      RST (0x4);                                break; */
/*         case 0xe8:   R_cond (cc.p);                               break; */
/*         case 0xe9:     PCHL ();                                   break; */
/*         case 0xea:   J_Cond (BYTE2, BYTE1, cc.p);                 break; */
/*         case 0xeb:     XCHG ();                                   break; */
/*         case 0xec:   C_Cond (BYTE2, BYTE1, cc.p);                 break; */
/*         /1*   0xed: - *1/ */
/*         case 0xee:      XRI (BYTE1);                              break; */
/*         case 0xef:      RST (0x5);                                break; */
/*         case 0xf0:   R_cond (!cc.s);                              break; */
/*         case 0xf1:  POP_PSW ();                                   break; */
/*         case 0xf2:   J_Cond (BYTE2, BYTE1, !cc.s);                break; */
/*         case 0xf3:       DI ();                                   break; */
/*         case 0xf4:   C_Cond (BYTE2, BYTE1, !cc.s);                break; */
/*         case 0xf5: PUSH_PSW ();                                   break; */
/*         case 0xf6:      ORI (BYTE1);                              break; */
/*         case 0xf7:      RST (0x6);                                break; */
/*         case 0xf8:   R_cond (cc.s);                               break; */
/*         case 0xf9:     SPHL ();                                   break; */
/*         case 0xfa:   J_Cond (BYTE2, BYTE1, cc.s);                 break; */
/*         case 0xfb:       EI ();                                   break; */
/*         case 0xfc:   C_Cond (BYTE2, BYTE1, cc.s);                 break; */
/*         /1*   0xfd: - *1/ */
/*         case 0xfe:      CPI (BYTE1);                              break; */
/*         case 0xff:      RST (0x7);                                break; */
        default  : UnimplementedInstruction(opcode);              break;
    }

    instructions_executed++;
}

bool LR35902::Running()
{
    return !halted;
}

uint8_t LR35902::Read(uint16_t address)
{
    return bus->Read(address);
}

void LR35902::Write(uint16_t address, uint8_t data)
{
    bus->Write(address, data);
}

void LR35902::Connect(SystemBus* l_bus)
{
    bus = l_bus;
}

/* void LR35902::logical_flags(uint8_t result) */
/* { */
/*     // Sets the flags according to the result after a logical operation */
/*     cc.z  = (result == 0); */
/*     cc.s  = ((result & 0x80) != 0); */
/*     cc.p  = Parity(result); */
/*     cc.cy = 0; // Reset according to programmer's manual. */
/* } */

/* void LR35902::addition_flags(uint8_t i_a, uint8_t i_b, uint8_t cy) */
/* { */
/*     uint16_t sum = (uint16_t)i_a + (uint16_t)i_b + cy; */
/* 	cc.z = ((uint8_t)(i_a + i_b + cy) == 0); */
/* 	cc.s = ((sum & 0x80) == 0x80); */
/* 	cc.p = (Parity(sum & 0xff)); */
/* 	uint16_t carry = sum ^ i_a ^ i_b; */
/* 	/1* cc.cy = (carry & (1 << 8)); *1/ */
/* 	cc.cy = sum > 0xff; */
/*     /1* cc.ac = (carry & (1 << 4)); *1/ */
/* } */

/* void LR35902::subtraction_flags(uint8_t i_a, uint8_t i_b, uint8_t i_cy) */
/* { */
/*     uint16_t dif = (uint16_t)i_a - (uint16_t)i_b - i_cy; */
/* 	cc.z = (dif == 0); */
/* 	cc.s = ((dif & 0x80) == 0x80); */
/* 	cc.p = (Parity((uint8_t)(i_a - i_b - i_cy))); */
/* 	cc.cy = (i_a < (i_b + i_cy)) ? 1 : 0; */
/* 	cc.ac = ~(i_a ^ i_b ^ dif) & 0x10; */
/* } */

void LR35902::Disassemble(uint8_t opcode, uint8_t arg1, uint8_t arg2)
{
    NonPrefixDisassemble(opcode, arg1, arg2);
}

void LR35902::NonPrefixDisassemble(uint8_t opcode, uint8_t arg1, uint8_t arg2)
{
	printf("\n%04x ", pc);
	switch (opcode)
	{
		case 0x00: printf("NOP"); break;
	/* 	case 0x01: printf("LXI    B,#$%02x%02x", code[2], code[1]); opbytes=3; break; */
	/* 	case 0x02: printf("STAX   B"); break; */
	/* 	case 0x03: printf("INX    B"); break; */
	/* 	case 0x04: printf("INR    B"); break; */
	/* 	case 0x05: printf("DCR    B"); break; */
	/* 	case 0x06: printf("MVI    B,#$%02x", code[1]); opbytes=2; break; */
	/* 	case 0x07: printf("RLC"); break; */
	/* 	case 0x08: printf("NOP"); break; */
	/* 	case 0x09: printf("DAD    B"); break; */
	/* 	case 0x0a: printf("LDAX   B"); break; */
	/* 	case 0x0b: printf("DCX    B"); break; */
	/* 	case 0x0c: printf("INR    C"); break; */
	/* 	case 0x0d: printf("DCR    C"); break; */
		case 0x0e: printf("MVI    C,#$%02x", arg1); break;
	/* 	case 0x0f: printf("RRC"); break; */

	/* 	case 0x10: printf("NOP"); break; */
		case 0x11: printf("LXI    D,#$%02x%02x", arg2, arg1); break;
	/* 	case 0x12: printf("STAX   D"); break; */
	/* 	case 0x13: printf("INX    D"); break; */
	/* 	case 0x14: printf("INR    D"); break; */
	/* 	case 0x15: printf("DCR    D"); break; */
	/* 	case 0x16: printf("MVI    D,#$%02x", code[1]); opbytes=2; break; */
	/* 	case 0x17: printf("RAL"); break; */
	/* 	case 0x18: printf("NOP"); break; */
	/* 	case 0x19: printf("DAD    D"); break; */
	/* 	case 0x1a: printf("LDAX   D"); break; */
	/* 	case 0x1b: printf("DCX    D"); break; */
	/* 	case 0x1c: printf("INR    E"); break; */
	/* 	case 0x1d: printf("DCR    E"); break; */
	/* 	case 0x1e: printf("MVI    E,#$%02x", code[1]); opbytes = 2; break; */
	/* 	case 0x1f: printf("RAR"); break; */

	/* 	case 0x20: printf("NOP"); break; */
		case 0x21: printf("LXI    H,#$%02x%02x", arg2, arg1); break;
	/* 	case 0x22: printf("SHLD   $%02x%02x", code[2], code[1]); opbytes=3; break; */
	/* 	case 0x23: printf("INX    H"); break; */
	/* 	case 0x24: printf("INR    H"); break; */
	/* 	case 0x25: printf("DCR    H"); break; */
	/* 	case 0x26: printf("MVI    H,#$%02x", code[1]); opbytes=2; break; */
	/* 	case 0x27: printf("DAA"); break; */
	/* 	case 0x28: printf("NOP"); break; */
	/* 	case 0x29: printf("DAD    H"); break; */
		case 0x2a: printf("LD A (HL+)"); break;
	/* 	case 0x2b: printf("DCX    H"); break; */
	/* 	case 0x2c: printf("INR    L"); break; */
	/* 	case 0x2d: printf("DCR    L"); break; */
	/* 	case 0x2e: printf("MVI    L,#$%02x", code[1]); opbytes = 2; break; */
	/* 	case 0x2f: printf("CMA"); break; */

	/* 	case 0x30: printf("NOP"); break; */
	/* 	case 0x31: printf("LXI    SP,#$%02x%02x", code[2], code[1]); opbytes=3; break; */
	/* 	case 0x32: printf("STA    $%02x%02x", code[2], code[1]); opbytes=3; break; */
	/* 	case 0x33: printf("INX    SP"); break; */
	/* 	case 0x34: printf("INR    M"); break; */
	/* 	case 0x35: printf("DCR    M"); break; */
	/* 	case 0x36: printf("MVI    M,#$%02x", code[1]); opbytes=2; break; */
	/* 	case 0x37: printf("STC"); break; */
	/* 	case 0x38: printf("NOP"); break; */
	/* 	case 0x39: printf("DAD    SP"); break; */
	/* 	case 0x3a: printf("LDA    $%02x%02x", code[2], code[1]); opbytes=3; break; */
	/* 	case 0x3b: printf("DCX    SP"); break; */
	/* 	case 0x3c: printf("INR    A"); break; */
	/* 	case 0x3d: printf("DCR    A"); break; */
	/* 	case 0x3e: printf("MVI    A,#$%02x", code[1]); opbytes = 2; break; */
	/* 	case 0x3f: printf("CMC"); break; */

	/* 	case 0x40: printf("MOV    B,B"); break; */
	/* 	case 0x41: printf("MOV    B,C"); break; */
	/* 	case 0x42: printf("MOV    B,D"); break; */
	/* 	case 0x43: printf("MOV    B,E"); break; */
	/* 	case 0x44: printf("MOV    B,H"); break; */
	/* 	case 0x45: printf("MOV    B,L"); break; */
	/* 	case 0x46: printf("MOV    B,M"); break; */
		case 0x47: printf("MOV    B,A"); break;
	/* 	case 0x48: printf("MOV    C,B"); break; */
	/* 	case 0x49: printf("MOV    C,C"); break; */
	/* 	case 0x4a: printf("MOV    C,D"); break; */
	/* 	case 0x4b: printf("MOV    C,E"); break; */
	/* 	case 0x4c: printf("MOV    C,H"); break; */
	/* 	case 0x4d: printf("MOV    C,L"); break; */
	/* 	case 0x4e: printf("MOV    C,M"); break; */
	/* 	case 0x4f: printf("MOV    C,A"); break; */

	/* 	case 0x50: printf("MOV    D,B"); break; */
	/* 	case 0x51: printf("MOV    D,C"); break; */
	/* 	case 0x52: printf("MOV    D,D"); break; */
	/* 	case 0x53: printf("MOV    D.E"); break; */
	/* 	case 0x54: printf("MOV    D,H"); break; */
	/* 	case 0x55: printf("MOV    D,L"); break; */
	/* 	case 0x56: printf("MOV    D,M"); break; */
	/* 	case 0x57: printf("MOV    D,A"); break; */
	/* 	case 0x58: printf("MOV    E,B"); break; */
	/* 	case 0x59: printf("MOV    E,C"); break; */
	/* 	case 0x5a: printf("MOV    E,D"); break; */
	/* 	case 0x5b: printf("MOV    E,E"); break; */
	/* 	case 0x5c: printf("MOV    E,H"); break; */
	/* 	case 0x5d: printf("MOV    E,L"); break; */
	/* 	case 0x5e: printf("MOV    E,M"); break; */
	/* 	case 0x5f: printf("MOV    E,A"); break; */

	/* 	case 0x60: printf("MOV    H,B"); break; */
	/* 	case 0x61: printf("MOV    H,C"); break; */
	/* 	case 0x62: printf("MOV    H,D"); break; */
	/* 	case 0x63: printf("MOV    H.E"); break; */
	/* 	case 0x64: printf("MOV    H,H"); break; */
	/* 	case 0x65: printf("MOV    H,L"); break; */
	/* 	case 0x66: printf("MOV    H,M"); break; */
	/* 	case 0x67: printf("MOV    H,A"); break; */
	/* 	case 0x68: printf("MOV    L,B"); break; */
	/* 	case 0x69: printf("MOV    L,C"); break; */
	/* 	case 0x6a: printf("MOV    L,D"); break; */
	/* 	case 0x6b: printf("MOV    L,E"); break; */
	/* 	case 0x6c: printf("MOV    L,H"); break; */
	/* 	case 0x6d: printf("MOV    L,L"); break; */
	/* 	case 0x6e: printf("MOV    L,M"); break; */
	/* 	case 0x6f: printf("MOV    L,A"); break; */

	/* 	case 0x70: printf("MOV    M,B"); break; */
	/* 	case 0x71: printf("MOV    M,C"); break; */
	/* 	case 0x72: printf("MOV    M,D"); break; */
	/* 	case 0x73: printf("MOV    M.E"); break; */
	/* 	case 0x74: printf("MOV    M,H"); break; */
	/* 	case 0x75: printf("MOV    M,L"); break; */
	/* 	case 0x76: printf("HLT");        break; */
	/* 	case 0x77: printf("MOV    M,A"); break; */
	/* 	case 0x78: printf("MOV    A,B"); break; */
	/* 	case 0x79: printf("MOV    A,C"); break; */
	/* 	case 0x7a: printf("MOV    A,D"); break; */
	/* 	case 0x7b: printf("MOV    A,E"); break; */
	/* 	case 0x7c: printf("MOV    A,H"); break; */
	/* 	case 0x7d: printf("MOV    A,L"); break; */
	/* 	case 0x7e: printf("MOV    A,M"); break; */
	/* 	case 0x7f: printf("MOV    A,A"); break; */

	/* 	case 0x80: printf("ADD    B"); break; */
	/* 	case 0x81: printf("ADD    C"); break; */
	/* 	case 0x82: printf("ADD    D"); break; */
	/* 	case 0x83: printf("ADD    E"); break; */
	/* 	case 0x84: printf("ADD    H"); break; */
	/* 	case 0x85: printf("ADD    L"); break; */
	/* 	case 0x86: printf("ADD    M"); break; */
	/* 	case 0x87: printf("ADD    A"); break; */
	/* 	case 0x88: printf("ADC    B"); break; */
	/* 	case 0x89: printf("ADC    C"); break; */
	/* 	case 0x8a: printf("ADC    D"); break; */
	/* 	case 0x8b: printf("ADC    E"); break; */
	/* 	case 0x8c: printf("ADC    H"); break; */
	/* 	case 0x8d: printf("ADC    L"); break; */
	/* 	case 0x8e: printf("ADC    M"); break; */
	/* 	case 0x8f: printf("ADC    A"); break; */

	/* 	case 0x90: printf("SUB    B"); break; */
	/* 	case 0x91: printf("SUB    C"); break; */
	/* 	case 0x92: printf("SUB    D"); break; */
	/* 	case 0x93: printf("SUB    E"); break; */
	/* 	case 0x94: printf("SUB    H"); break; */
	/* 	case 0x95: printf("SUB    L"); break; */
	/* 	case 0x96: printf("SUB    M"); break; */
	/* 	case 0x97: printf("SUB    A"); break; */
	/* 	case 0x98: printf("SBB    B"); break; */
	/* 	case 0x99: printf("SBB    C"); break; */
	/* 	case 0x9a: printf("SBB    D"); break; */
	/* 	case 0x9b: printf("SBB    E"); break; */
	/* 	case 0x9c: printf("SBB    H"); break; */
	/* 	case 0x9d: printf("SBB    L"); break; */
	/* 	case 0x9e: printf("SBB    M"); break; */
	/* 	case 0x9f: printf("SBB    A"); break; */

	/* 	case 0xa0: printf("ANA    B"); break; */
	/* 	case 0xa1: printf("ANA    C"); break; */
	/* 	case 0xa2: printf("ANA    D"); break; */
	/* 	case 0xa3: printf("ANA    E"); break; */
	/* 	case 0xa4: printf("ANA    H"); break; */
	/* 	case 0xa5: printf("ANA    L"); break; */
	/* 	case 0xa6: printf("ANA    M"); break; */
	/* 	case 0xa7: printf("ANA    A"); break; */
	/* 	case 0xa8: printf("XRA    B"); break; */
	/* 	case 0xa9: printf("XRA    C"); break; */
	/* 	case 0xaa: printf("XRA    D"); break; */
	/* 	case 0xab: printf("XRA    E"); break; */
	/* 	case 0xac: printf("XRA    H"); break; */
	/* 	case 0xad: printf("XRA    L"); break; */
	/* 	case 0xae: printf("XRA    M"); break; */
	/* 	case 0xaf: printf("XRA    A"); break; */

	/* 	case 0xb0: printf("ORA    B"); break; */
	/* 	case 0xb1: printf("ORA    C"); break; */
	/* 	case 0xb2: printf("ORA    D"); break; */
	/* 	case 0xb3: printf("ORA    E"); break; */
	/* 	case 0xb4: printf("ORA    H"); break; */
	/* 	case 0xb5: printf("ORA    L"); break; */
	/* 	case 0xb6: printf("ORA    M"); break; */
	/* 	case 0xb7: printf("ORA    A"); break; */
	/* 	case 0xb8: printf("CMP    B"); break; */
	/* 	case 0xb9: printf("CMP    C"); break; */
	/* 	case 0xba: printf("CMP    D"); break; */
	/* 	case 0xbb: printf("CMP    E"); break; */
	/* 	case 0xbc: printf("CMP    H"); break; */
	/* 	case 0xbd: printf("CMP    L"); break; */
	/* 	case 0xbe: printf("CMP    M"); break; */
	/* 	case 0xbf: printf("CMP    A"); break; */

	/* 	case 0xc0: printf("RNZ"); break; */
	/* 	case 0xc1: printf("POP    B"); break; */
	/* 	case 0xc2: printf("JNZ    $%02x%02x",code[2],code[1]); opbytes = 3; break; */
		case 0xc3: printf("JMP    $%02x%02x",arg2,arg1); break;
	/* 	case 0xc4: printf("CNZ    $%02x%02x",code[2],code[1]); opbytes = 3; break; */
	/* 	case 0xc5: printf("PUSH   B"); break; */
	/* 	case 0xc6: printf("ADI    #$%02x",code[1]); opbytes = 2; break; */
	/* 	case 0xc7: printf("RST    0"); break; */
	/* 	case 0xc8: printf("RZ"); break; */
	/* 	case 0xc9: printf("RET"); break; */
	/* 	case 0xca: printf("JZ     $%02x%02x",code[2],code[1]); opbytes = 3; break; */
	/* 	case 0xcb: printf("JMP    $%02x%02x",code[2],code[1]); opbytes = 3; break; */
	/* 	case 0xcc: printf("CZ     $%02x%02x",code[2],code[1]); opbytes = 3; break; */
	/* 	case 0xcd: printf("CALL   $%02x%02x",code[2],code[1]); opbytes = 3; break; */
	/* 	case 0xce: printf("ACI    #$%02x",code[1]); opbytes = 2; break; */
	/* 	case 0xcf: printf("RST    1"); break; */

	/* 	case 0xd0: printf("RNC"); break; */
	/* 	case 0xd1: printf("POP    D"); break; */
	/* 	case 0xd2: printf("JNC    $%02x%02x",code[2],code[1]); opbytes = 3; break; */
	/* 	case 0xd3: printf("OUT    #$%02x",code[1]); opbytes = 2; break; */
	/* 	case 0xd4: printf("CNC    $%02x%02x",code[2],code[1]); opbytes = 3; break; */
	/* 	case 0xd5: printf("PUSH   D"); break; */
	/* 	case 0xd6: printf("SUI    #$%02x",code[1]); opbytes = 2; break; */
	/* 	case 0xd7: printf("RST    2"); break; */
	/* 	case 0xd8: printf("RC");  break; */
	/* 	case 0xd9: printf("RET"); break; */
	/* 	case 0xda: printf("JC     $%02x%02x",code[2],code[1]); opbytes = 3; break; */
	/* 	case 0xdb: printf("IN     #$%02x",code[1]); opbytes = 2; break; */
	/* 	case 0xdc: printf("CC     $%02x%02x",code[2],code[1]); opbytes = 3; break; */
	/* 	case 0xdd: printf("CALL   $%02x%02x",code[2],code[1]); opbytes = 3; break; */
	/* 	case 0xde: printf("SBI    #$%02x",code[1]); opbytes = 2; break; */
	/* 	case 0xdf: printf("RST    3"); break; */

	/* 	case 0xe0: printf("RPO"); break; */
	/* 	case 0xe1: printf("POP    H"); break; */
	/* 	case 0xe2: printf("JPO    $%02x%02x",code[2],code[1]); opbytes = 3; break; */
	/* 	case 0xe3: printf("XTHL");break; */
	/* 	case 0xe4: printf("CPO    $%02x%02x",code[2],code[1]); opbytes = 3; break; */
	/* 	case 0xe5: printf("PUSH   H"); break; */
	/* 	case 0xe6: printf("ANI    #$%02x",code[1]); opbytes = 2; break; */
	/* 	case 0xe7: printf("RST    4"); break; */
	/* 	case 0xe8: printf("RPE"); break; */
	/* 	case 0xe9: printf("PCHL");break; */
	/* 	case 0xea: printf("JPE    $%02x%02x",code[2],code[1]); opbytes = 3; break; */
	/* 	case 0xeb: printf("XCHG"); break; */
	/* 	case 0xec: printf("CPE     $%02x%02x",code[2],code[1]); opbytes = 3; break; */
	/* 	case 0xed: printf("CALL   $%02x%02x",code[2],code[1]); opbytes = 3; break; */
	/* 	case 0xee: printf("XRI    #$%02x",code[1]); opbytes = 2; break; */
	/* 	case 0xef: printf("RST    5"); break; */

	/* 	case 0xf0: printf("RP");  break; */
	/* 	case 0xf1: printf("POP    PSW"); break; */
	/* 	case 0xf2: printf("JP     $%02x%02x",code[2],code[1]); opbytes = 3; break; */
	/* 	case 0xf3: printf("DI");  break; */
	/* 	case 0xf4: printf("CP     $%02x%02x",code[2],code[1]); opbytes = 3; break; */
	/* 	case 0xf5: printf("PUSH   PSW"); break; */
	/* 	case 0xf6: printf("ORI    #$%02x",code[1]); opbytes = 2; break; */
	/* 	case 0xf7: printf("RST    6"); break; */
	/* 	case 0xf8: printf("RM");  break; */
	/* 	case 0xf9: printf("SPHL");break; */
	/* 	case 0xfa: printf("JM     $%02x%02x",code[2],code[1]); opbytes = 3; break; */
	/* 	case 0xfb: printf("EI");  break; */
	/* 	case 0xfc: printf("CM     $%02x%02x",code[2],code[1]); opbytes = 3; break; */
	/* 	case 0xfd: printf("CALL   $%02x%02x",code[2],code[1]); opbytes = 3; break; */
	/* 	case 0xfe: printf("CPI    #$%02x",code[1]); opbytes = 2; break; */
	/* 	case 0xff: printf("RST    7"); break; */
	}
    printf("\n");

}
