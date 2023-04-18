/* 8080 disassembler.
 * From: git clone https://github.com/snwlvl/Intel-8080-Disassembler.git
 * 2-18-2023
 * Tom Trebisky - I made a handful of modifications.
 */

#include <stdio.h>
#include <stdlib.h>

int disassemble (unsigned char *, int );

int
main(int argc, char **argv)
{
	if (argc < 2 ) {
	    printf ( "Usage disass file\n" );
	    exit ( 1 );
	}

	FILE *f = fopen(argv[1], "rb");
	if (f == NULL) {
		printf("Error: couldn't open file %s/n", argv[1]);
	        exit(1);
	}

	/* Get file size */
	fseek(f, 0L, SEEK_END);
	int fsize = ftell(f);
	fseek(f, 0L, SEEK_SET);

	unsigned char *buffer = malloc(fsize);
	fread(buffer, fsize, 1, f);
	fclose(f);

	int pc = 0;
	while (pc < fsize) {
		pc += disassemble ( buffer, pc );
	}

	free(buffer);

        return 0;
}

int
print_op1 ( unsigned char *op, int pc, char *mnem )
{
	printf ( "%04x %02x    \t%s\n", pc, op[0], mnem );
	return 1;
}

int
print_op2 ( unsigned char *op, int pc, char *mnem, unsigned char x )
{
	printf ( "%04x %02x%02x  \t%s0x%02x\n", pc, op[0], op[1], mnem, op[1] );
	return 2;
}

int
print_op3 ( unsigned char *op, int pc, char *mnem, unsigned char x, unsigned char y )
{
	printf ( "%04x %02x%02x%02x\t%s0x%02x%02x\n", pc, op[0], op[1], op[2], mnem, op[2], op[1] );
	return 3;
}

int
print_unk ( unsigned char *op, int pc )
{
	printf ( "%04x %02x    \tUnknown Instruction\n", pc, *op );
	return 1;
}

int
disassemble(unsigned char* buffer, int pc)
{
	unsigned char *opcode = &buffer[pc];
	// int opbytes = 1;
	int opbytes;

	// printf ( "%04x %02x    \t", pc, *opcode );

	switch (*opcode) {
		case 0x00:
		case 0x08:
		case 0x10:
		case 0x18:
		case 0x28:
		case 0x38:
		case 0xcb:
		case 0xd9:
		case 0xdd:
		case 0xed:
		case 0xfd:
			opbytes = print_op1 ( opcode, pc, "nop" );
			break;
		case 0x01:
			opbytes = print_op3 ( opcode, pc, "lxi\tB, ", opcode[2], opcode[1]);
			// opbytes = 3;
			break;
		case 0x02:
			opbytes = print_op1 ( opcode, pc, "stax\tB");
			break;
		case 0x03:
			opbytes = print_op1 ( opcode, pc, "inx\tB");
			break;
		case 0x04:
			opbytes = print_op1 ( opcode, pc, "inr\tB");
			break;
		case 0x05:
			opbytes = print_op1 ( opcode, pc, "dcr\tB");
			break;
		case 0x06:
			opbytes = print_op2 ( opcode, pc, "mvi\tB, ", opcode[1]);
			// opbytes = 2;
			break;
		case 0x07:
			opbytes = print_op1 ( opcode, pc, "rlc");
			break;
		case 0x09:
			opbytes = print_op1 ( opcode, pc, "dad\tB");
			break;
		case 0x0a:
			opbytes = print_op1 ( opcode, pc, "ldax\tB");
			break;
		case 0x0b:
			opbytes = print_op1 ( opcode, pc, "dcx\tB");
			break;
		case 0x0c:
			opbytes = print_op1 ( opcode, pc, "inr\tC");
			break;
		case 0x0d:
			opbytes = print_op1 ( opcode, pc, "dcr\tC");
			break;
		case 0x0e:
			opbytes = print_op2 ( opcode, pc, "mvi\tC, ", opcode[1]);
			// opbytes = 2;
			break;
		case 0x0f:
			opbytes = print_op1 ( opcode, pc, "rrc");
			break;
		case 0x11:
			opbytes = print_op3 ( opcode, pc, "lxi\tD, ", opcode[2], opcode[1]);
			// opbytes = 3;
			break;
		case 0x12:
			opbytes = print_op1 ( opcode, pc, "stax\tD");
			break;
		case 0x13:
			opbytes = print_op1 ( opcode, pc, "inx\tD");
			break;
		case 0x14:
			opbytes = print_op1 ( opcode, pc, "inr\tD");
			break;
		case 0x15:
			opbytes = print_op1 ( opcode, pc, "dcr\tD");
			break;
		case 0x16:
			opbytes = print_op1 ( opcode, pc, "dcr\tD");
			break;
		case 0x17:
			opbytes = print_op1 ( opcode, pc, "ral");
			break;
		case 0x19:
			opbytes = print_op1 ( opcode, pc, "dad\tD");
			break;
		case 0x1a:
			opbytes = print_op1 ( opcode, pc, "ldax\tD");
			break;
		case 0x1b:
			opbytes = print_op1 ( opcode, pc, "dcx\tD");
			break;
		case 0x1c:
			opbytes = print_op1 ( opcode, pc, "inr\tE");
			break;
		case 0x1d:
			opbytes = print_op1 ( opcode, pc, "dcr\tE");
			break;
		case 0x1e:
			opbytes = print_op2 ( opcode, pc, "mvi\tE, ", opcode[1]);
			// opbytes = 2;
			break;
		case 0x1f:
			opbytes = print_op1 ( opcode, pc, "rar");
			break;
		case 0x20:
			opbytes = print_op1 ( opcode, pc, "rim");
			break;
		case 0x21:
			opbytes = print_op3 ( opcode, pc, "lxi\tH, ", opcode[2], opcode[1]);
			// opbytes = 3;
			break;
		case 0x22:
			opbytes = print_op3 ( opcode, pc, "shld\t", opcode[2], opcode[1]);
			// opbytes = 3;
			break;
		case 0x23:
			opbytes = print_op1 ( opcode, pc, "inx\tH");
			break;
		case 0x24:
			opbytes = print_op1 ( opcode, pc, "inr\tH");
			break;
		case 0x25:
			opbytes = print_op1 ( opcode, pc, "dcr\tH");
			break;
		case 0x26:
			opbytes = print_op2 ( opcode, pc, "mvi\tH, ", opcode[1]);
			// opbytes = 2;
			break;
		case 0x27:
			opbytes = print_op1 ( opcode, pc, "daa");
			break;
		case 0x29:
			opbytes = print_op1 ( opcode, pc, "dad\tH");
			break;
		case 0x2a:
			opbytes = print_op3 ( opcode, pc, "lhld\t", opcode[2], opcode[1]);
			// opbytes = 3;
			break;
		case 0x2b:
			opbytes = print_op1 ( opcode, pc, "dcx\tH");
			break;
		case 0x2c:
			opbytes = print_op1 ( opcode, pc, "inr\tL");
			break;
		case 0x2d:
			opbytes = print_op1 ( opcode, pc, "dcr\tL");
			break;
		case 0x2e:
			opbytes = print_op2 ( opcode, pc, "mvi\tL, ", opcode[1]);
			// opbytes = 2;
			break;
		case 0x2f:
			opbytes = print_op1 ( opcode, pc, "cma");
			break;
		case 0x30:
			opbytes = print_op1 ( opcode, pc, "sim");
			break;
		case 0x31:
			opbytes = print_op3 ( opcode, pc, "lxi\tSP, ", opcode[2], opcode[1]);
			// opbytes = 3;
			break;
		case 0x32:
			opbytes = print_op3 ( opcode, pc, "sta\t", opcode[2], opcode[1]);
			// opbytes = 3;
			break;
		case 0x33:
			opbytes = print_op1 ( opcode, pc, "inx\tSP");
			break;
		case 0x34:
			opbytes = print_op1 ( opcode, pc, "inr\tM");
			break;
		case 0x35:
			opbytes = print_op1 ( opcode, pc, "dcr\tM");
			break;
		case 0x36:
			opbytes = print_op2 ( opcode, pc, "mvi\tM, ", opcode[1]);
			// opbytes = 2;
			break;
		case 0x37:
			opbytes = print_op1 ( opcode, pc, "stc");
			break;
		case 0x39:
			opbytes = print_op1 ( opcode, pc, "dad\tSP");
			break;
		case 0x3a:
			opbytes = print_op3 ( opcode, pc, "lda\t", opcode[2], opcode[1]);
			// opbytes = 3;
			break;
		case 0x3b:
			opbytes = print_op1 ( opcode, pc, "dcx\tSP");
			break;
		case 0x3c:
			opbytes = print_op1 ( opcode, pc, "inr\tA");
			break;
		case 0x3d:
			opbytes = print_op1 ( opcode, pc, "dcr\tA");
			break;
		case 0x3e:
			opbytes = print_op2 ( opcode, pc, "mvi\tA, ", opcode[1]);
			// opbytes = 2;
			break;
		case 0x3f:
			opbytes = print_op1 ( opcode, pc, "cmc");
			break;
		case 0x40:
			opbytes = print_op1 ( opcode, pc, "mov\tB, B");
			break;
		case 0x41:
			opbytes = print_op1 ( opcode, pc, "mov\tB, C");
			break;
		case 0x42:
			opbytes = print_op1 ( opcode, pc, "mov\tB, D");
			break;
		case 0x43:
			opbytes = print_op1 ( opcode, pc, "mov\tB, E");
			break;
		case 0x44:
			opbytes = print_op1 ( opcode, pc, "mov\tB, H");
			break;
		case 0x45:
			opbytes = print_op1 ( opcode, pc, "mov\tB, L");
			break;
		case 0x46:
			opbytes = print_op1 ( opcode, pc, "mov\tB, M");
			break;
		case 0x47:
			opbytes = print_op1 ( opcode, pc, "mov\tB, A");
			break;
		case 0x48:
			opbytes = print_op1 ( opcode, pc, "mov\tC, B");
			break;
		case 0x49:
			opbytes = print_op1 ( opcode, pc, "mov\tC, C");
			break;
		case 0x4a:
			opbytes = print_op1 ( opcode, pc, "mov\tC, D");
			break;
		case 0x4b:
			opbytes = print_op1 ( opcode, pc, "mov\tC, E");
			break;
		case 0x4c:
			opbytes = print_op1 ( opcode, pc, "mov\tC, H");
			break;
		case 0x4d:
			opbytes = print_op1 ( opcode, pc, "mov\tC, L");
			break;
		case 0x4e:
			opbytes = print_op1 ( opcode, pc, "mov\tC, M");
			break;
		case 0x4f:
			opbytes = print_op1 ( opcode, pc, "mov\tC, A");
			break;
		case 0x50:
			opbytes = print_op1 ( opcode, pc, "mov\tD, B");
			break;
		case 0x51:
			opbytes = print_op1 ( opcode, pc, "mov\tD, C");
			break;
		case 0x52:
			opbytes = print_op1 ( opcode, pc, "mov\tD, D");
			break;
		case 0x53:
			opbytes = print_op1 ( opcode, pc, "mov\tD, E");
			break;
		case 0x54:
			opbytes = print_op1 ( opcode, pc, "mov\tD, H");
			break;
		case 0x55:
			opbytes = print_op1 ( opcode, pc, "mov\tD, L");
			break;
		case 0x56:
			opbytes = print_op1 ( opcode, pc, "mov\tD, M");
			break;
		case 0x57:
			opbytes = print_op1 ( opcode, pc, "mov\tD, A");
			break;
		case 0x58:
			opbytes = print_op1 ( opcode, pc, "mov\tE, B");
			break;
		case 0x59:
			opbytes = print_op1 ( opcode, pc, "mov\tE, C");
			break;
		case 0x5a:
			opbytes = print_op1 ( opcode, pc, "mov\tE, D");
			break;
		case 0x5b:
			opbytes = print_op1 ( opcode, pc, "mov\tE, E");
			break;
		case 0x5c:
			opbytes = print_op1 ( opcode, pc, "mov\tE, H");
			break;
		case 0x5d:
			opbytes = print_op1 ( opcode, pc, "mov\tE, L");
			break;
		case 0x5e:
			opbytes = print_op1 ( opcode, pc, "mov\tE, M");
			break;
		case 0x5f:
			opbytes = print_op1 ( opcode, pc, "mov\tE, A");
			break;
		case 0x60:
			opbytes = print_op1 ( opcode, pc, "mov\tH, B");
			break;
		case 0x61:
			opbytes = print_op1 ( opcode, pc, "mov\tH, C");
			break;
		case 0x62:
			opbytes = print_op1 ( opcode, pc, "mov\tH, D");
			break;
		case 0x63:
			opbytes = print_op1 ( opcode, pc, "mov\tH, E");
			break;
		case 0x64:
			opbytes = print_op1 ( opcode, pc, "mov\tH, H");
			break;
		case 0x65:
			opbytes = print_op1 ( opcode, pc, "mov\tH, L");
			break;
		case 0x66:
			opbytes = print_op1 ( opcode, pc, "mov\tH, M");
			break;
		case 0x67:
			opbytes = print_op1 ( opcode, pc, "mov\tH, A");
			break;
		case 0x68:
			opbytes = print_op1 ( opcode, pc, "mov\tL, B");
			break;
		case 0x69:
			opbytes = print_op1 ( opcode, pc, "mov\tL, C");
			break;
		case 0x6a:
			opbytes = print_op1 ( opcode, pc, "mov\tL, D");
			break;
		case 0x6b:
			opbytes = print_op1 ( opcode, pc, "mov\tL, E");
			break;
		case 0x6c:
			opbytes = print_op1 ( opcode, pc, "mov\tL, H");
			break;
		case 0x6d:
			opbytes = print_op1 ( opcode, pc, "mov\tL, L");
			break;
		case 0x6e:
			opbytes = print_op1 ( opcode, pc, "mov\tL, M");
			break;
		case 0x6f:
			opbytes = print_op1 ( opcode, pc, "mov\tL, A");
			break;
		case 0x70:
			opbytes = print_op1 ( opcode, pc, "mov\tM, B");
			break;
		case 0x71:
			opbytes = print_op1 ( opcode, pc, "mov\tM, C");
			break;
		case 0x72:
			opbytes = print_op1 ( opcode, pc, "mov\tM, D");
			break;
		case 0x73:
			opbytes = print_op1 ( opcode, pc, "mov\tM, E");
			break;
		case 0x74:
			opbytes = print_op1 ( opcode, pc, "mov\tM, H");
			break;
		case 0x75:
			opbytes = print_op1 ( opcode, pc, "mov\tM, L");
			break;
		case 0x76:
			opbytes = print_op1 ( opcode, pc, "hlt");
			break;
		case 0x77:
			opbytes = print_op1 ( opcode, pc, "mov\tM, A");
			break;
		case 0x78:
			opbytes = print_op1 ( opcode, pc, "mov\tA, B");
			break;
		case 0x79:
			opbytes = print_op1 ( opcode, pc, "mov\tA, C");
			break;
		case 0x7a:
			opbytes = print_op1 ( opcode, pc, "mov\tA, D");
			break;
		case 0x7b:
			opbytes = print_op1 ( opcode, pc, "mov\tA, E");
			break;
		case 0x7c:
			opbytes = print_op1 ( opcode, pc, "mov\tA, H");
			break;
		case 0x7d:
			opbytes = print_op1 ( opcode, pc, "mov\tA, L");
			break;
		case 0x7e:
			opbytes = print_op1 ( opcode, pc, "mov\tA, M");
			break;
		case 0x7f:
			opbytes = print_op1 ( opcode, pc, "mov\tA, A");
			break;
		case 0x80:
			opbytes = print_op1 ( opcode, pc, "add\tB");
			break;
		case 0x81:
			opbytes = print_op1 ( opcode, pc, "add\tC");
			break;
		case 0x82:
			opbytes = print_op1 ( opcode, pc, "add\tD");
			break;
		case 0x83:
			opbytes = print_op1 ( opcode, pc, "add\tE");
			break;
		case 0x84:
			opbytes = print_op1 ( opcode, pc, "add\tH");
			break;
		case 0x85:
			opbytes = print_op1 ( opcode, pc, "add\tL");
			break;
		case 0x86:
			opbytes = print_op1 ( opcode, pc, "add\tM");
			break;
		case 0x87:
			opbytes = print_op1 ( opcode, pc, "add\tA");
			break;
		case 0x88:
			opbytes = print_op1 ( opcode, pc, "adc\tB");
			break;
		case 0x89:
			opbytes = print_op1 ( opcode, pc, "adc\tC");
			break;
		case 0x8a:
			opbytes = print_op1 ( opcode, pc, "adc\tE");
			break;
		case 0x8b:
			opbytes = print_op1 ( opcode, pc, "adc\tE");
			break;
		case 0x8c:
			opbytes = print_op1 ( opcode, pc, "adc\tH");
			break;
		case 0x8d:
			opbytes = print_op1 ( opcode, pc, "adc\tL");
			break;
		case 0x8e:
			opbytes = print_op1 ( opcode, pc, "adc\tM");
			break;
		case 0x8f:
			opbytes = print_op1 ( opcode, pc, "adc\tA");
			break;
		case 0x90:
			opbytes = print_op1 ( opcode, pc, "sub\tB");
			break;
		case 0x91:
			opbytes = print_op1 ( opcode, pc, "sub\tC");
			break;
		case 0x92:
			opbytes = print_op1 ( opcode, pc, "sub\tD");
			break;
		case 0x93:
			opbytes = print_op1 ( opcode, pc, "sub\tE");
			break;
		case 0x94:
			opbytes = print_op1 ( opcode, pc, "sub\tH");
			break;
		case 0x95:
			opbytes = print_op1 ( opcode, pc, "sub\tL");
			break;
		case 0x96:
			opbytes = print_op1 ( opcode, pc, "sub\tM");
			break;
		case 0x97:
			opbytes = print_op1 ( opcode, pc, "sub\tA");
			break;
		case 0x98:
			opbytes = print_op1 ( opcode, pc, "sbb\tB");
			break;
		case 0x99:
			opbytes = print_op1 ( opcode, pc, "sbb\tC");
			break;
		case 0x9a:
			opbytes = print_op1 ( opcode, pc, "sbb\tD");
			break;
		case 0x9b:
			opbytes = print_op1 ( opcode, pc, "sbb\tE");
			break;
		case 0x9c:
			opbytes = print_op1 ( opcode, pc, "sbb\tH");
			break;
		case 0x9d:
			opbytes = print_op1 ( opcode, pc, "sbb\tL");
			break;
		case 0x9e:
			opbytes = print_op1 ( opcode, pc, "sbb\tM");
			break;
		case 0x9f:
			opbytes = print_op1 ( opcode, pc, "sbb\tA");
			break;
		case 0xa0:
			opbytes = print_op1 ( opcode, pc, "ana\tB");
			break;
		case 0xa1:
			opbytes = print_op1 ( opcode, pc, "ana\tC");
			break;
		case 0xa2:
			opbytes = print_op1 ( opcode, pc, "ana\tD");
			break;
		case 0xa3:
			opbytes = print_op1 ( opcode, pc, "ana\tE");
			break;
		case 0xa4:
			opbytes = print_op1 ( opcode, pc, "ana\tH");
			break;
		case 0xa5:
			opbytes = print_op1 ( opcode, pc, "ana\tL");
			break;
		case 0xa6:
			opbytes = print_op1 ( opcode, pc, "ana\tM");
			break;
		case 0xa7:
			opbytes = print_op1 ( opcode, pc, "ana\tA");
			break;
		case 0xa8:
			opbytes = print_op1 ( opcode, pc, "xra\tB");
			break;
		case 0xa9:
			opbytes = print_op1 ( opcode, pc, "xra\tC");
			break;
		case 0xaa:
			opbytes = print_op1 ( opcode, pc, "xra\tD");
			break;
		case 0xab:
			opbytes = print_op1 ( opcode, pc, "xra\tE");
			break;
		case 0xac:
			opbytes = print_op1 ( opcode, pc, "xra\tH");
			break;
		case 0xad:
			opbytes = print_op1 ( opcode, pc, "xra\tL");
			break;
		case 0xae:
			opbytes = print_op1 ( opcode, pc, "xra\tM");
			break;
		case 0xaf:
			opbytes = print_op1 ( opcode, pc, "xra\tA");
			break;
		case 0xb0:
			opbytes = print_op1 ( opcode, pc, "ora\tB");
			break;
		case 0xb1:
			opbytes = print_op1 ( opcode, pc, "ora\tC");
			break;
		case 0xb2:
			opbytes = print_op1 ( opcode, pc, "ora\tD");
			break;
		case 0xb3:
			opbytes = print_op1 ( opcode, pc, "ora\tE");
			break;
		case 0xb4:
			opbytes = print_op1 ( opcode, pc, "ora\tH");
			break;
		case 0xb5:
			opbytes = print_op1 ( opcode, pc, "ora\tL");
			break;
		case 0xb6:
			opbytes = print_op1 ( opcode, pc, "ora\tM");
			break;
		case 0xb7:
			opbytes = print_op1 ( opcode, pc, "ora\tA");
			break;
		case 0xb8:
			opbytes = print_op1 ( opcode, pc, "cmp\tB");
			break;
		case 0xb9:
			opbytes = print_op1 ( opcode, pc, "cmp\tC");
			break;
		case 0xba:
			opbytes = print_op1 ( opcode, pc, "cmp\tD");
			break;
		case 0xbb:
			opbytes = print_op1 ( opcode, pc, "cmp\tE");
			break;
		case 0xbc:
			opbytes = print_op1 ( opcode, pc, "cmp\tH");
			break;
		case 0xbd:
			opbytes = print_op1 ( opcode, pc, "cmp\tL");
			break;
		case 0xbe:
			opbytes = print_op1 ( opcode, pc, "cmp\tM");
			break;
		case 0xbf:
			opbytes = print_op1 ( opcode, pc, "cmp\tA");
			break;
		case 0xc0:
			opbytes = print_op1 ( opcode, pc, "rnz");
			break;
		case 0xc1:
			opbytes = print_op1 ( opcode, pc, "pop\tB");
			break;
		case 0xc2:
			opbytes = print_op3 ( opcode, pc, "jnz\t", opcode[2], opcode[1]);
			// opbytes = 3;
			break;
		case 0xc3:
			opbytes = print_op3 ( opcode, pc, "jmp\t", opcode[2], opcode[1]);
			// opbytes = 3;
			break;
		case 0xc4:
			opbytes = print_op3 ( opcode, pc, "cnz\t", opcode[2], opcode[1]);
			// opbytes = 3;
			break;
		case 0xc5:
			opbytes = print_op1 ( opcode, pc, "push\tB");
			break;
		case 0xc6:
			opbytes = print_op2 ( opcode, pc, "adi\t", opcode[1]);
			// opbytes = 2;
			break;
		case 0xc7:
			opbytes = print_op1 ( opcode, pc, "rst\t0");
			break;
		case 0xc8:
			opbytes = print_op1 ( opcode, pc, "rz");
			break;
		case 0xc9:
			opbytes = print_op1 ( opcode, pc, "ret");
			printf ( "\n" );
			break;
		case 0xca:
			opbytes = print_op3 ( opcode, pc, "jz\t", opcode[2], opcode[1]);
			// opbytes = 3;
			break;
		case 0xcc:
			opbytes = print_op3 ( opcode, pc, "cz\t", opcode[2], opcode[1]);
			// opbytes = 3;
			break;
		case 0xcd:
			opbytes = print_op3 ( opcode, pc, "call\t", opcode[2], opcode[1]);
			// opbytes = 3;
			break;
		case 0xce:
			opbytes = print_op2 ( opcode, pc, "aci\t", opcode[1]);
			// opbytes = 2;
			break;
		case 0xcf:
			opbytes = print_op1 ( opcode, pc, "rst\t1");
			break;
		case 0xd0:
			opbytes = print_op1 ( opcode, pc, "rnc");
			break;
		case 0xd1:
			opbytes = print_op1 ( opcode, pc, "pop\tD");
			break;
		case 0xd2:
			opbytes = print_op3 ( opcode, pc, "jnc\t", opcode[2], opcode[1]);
			// opbytes = 3;
			break;
		case 0xd3:
			opbytes = print_op2 ( opcode, pc, "out\t", opcode[1]);
			// opbytes = 2;
			break;
		case 0xd4:
			opbytes = print_op3 ( opcode, pc, "cnc\t", opcode[2], opcode[1]);
			// opbytes = 3;
			break;
		case 0xd5:
			opbytes = print_op1 ( opcode, pc, "push\tD");
			break;
		case 0xd6:
			opbytes = print_op2 ( opcode, pc, "sui\t", opcode[1]);
			// opbytes = 2;
			break;
		case 0xd7:
			opbytes = print_op1 ( opcode, pc, "rst\t2");
			break;
		case 0xd8:
			opbytes = print_op1 ( opcode, pc, "rc");
			break;
		case 0xda:
			opbytes = print_op3 ( opcode, pc, "jc\t", opcode[2], opcode[1]);
			// opbytes = 3;
			break;
		case 0xdb:
			opbytes = print_op2 ( opcode, pc, "in\t", opcode[1]);
			// opbytes = 2;
			break;
		case 0xdc:
			opbytes = print_op3 ( opcode, pc, "cc\t", opcode[2], opcode[1]);
			// opbytes = 3;
			break;
		case 0xde:
			opbytes = print_op2 ( opcode, pc, "sbi\t", opcode[1]);
			// opbytes = 2;
			break;
		case 0xdf:
			opbytes = print_op1 ( opcode, pc, "rst\t3");
			break;
		case 0xe0:
			opbytes = print_op1 ( opcode, pc, "rpo");
			break;
		case 0xe1:
			opbytes = print_op1 ( opcode, pc, "pop\tH");
			break;
		case 0xe2:
			opbytes = print_op3 ( opcode, pc, "jpo\t", opcode[2], opcode[1]);
			// opbytes = 3;
			break;
		case 0xe3:
			opbytes = print_op1 ( opcode, pc, "xthl");
			break;
		case 0xe4:
			opbytes = print_op3 ( opcode, pc, "cpo\t", opcode[2], opcode[1]);
			// opbytes = 3;
			break;
		case 0xe5:
			opbytes = print_op1 ( opcode, pc, "push\tH");
			break;
		case 0xe6:
			opbytes = print_op2 ( opcode, pc, "ani\t", opcode[1]);
			// opbytes = 2;
			break;
		case 0xe7:
			opbytes = print_op1 ( opcode, pc, "rst\t4");
			break;
		case 0xe8:
			opbytes = print_op1 ( opcode, pc, "rpe");
			break;
		case 0xe9:
			opbytes = print_op1 ( opcode, pc, "pchl");
			break;
		case 0xea:
			opbytes = print_op3 ( opcode, pc, "jpe\t", opcode[2], opcode[1]);
			// opbytes = 3;
			break;
		case 0xeb:
			opbytes = print_op1 ( opcode, pc, "xchg");
			break;
		case 0xec:
			opbytes = print_op3 ( opcode, pc, "cpe\t", opcode[2], opcode[1]);
			// opbytes = 3;
			break;
		case 0xee:
			opbytes = print_op2 ( opcode, pc, "xri\t", opcode[1]);
			// opbytes = 2;
			break;
		case 0xef:
			opbytes = print_op1 ( opcode, pc, "rst\t5");
			break;
		case 0xf0:
			opbytes = print_op1 ( opcode, pc, "rp");
			break;
		case 0xf1:
			opbytes = print_op1 ( opcode, pc, "pop\tPSW");
			break;
		case 0xf2:
			opbytes = print_op3 ( opcode, pc, "jp\t", opcode[2], opcode[1]);
			// opbytes = 3;
			break;
		case 0xf3:
			opbytes = print_op1 ( opcode, pc, "di");
			break;
		case 0xf4:
			opbytes = print_op3 ( opcode, pc, "cp\t", opcode[2], opcode[1]);
			// opbytes = 3;
			break;
		case 0xf5:
			opbytes = print_op1 ( opcode, pc, "push\tPSW");
			break;
		case 0xf6:
			opbytes = print_op2 ( opcode, pc, "ori\t", opcode[1]);
			// opbytes = 2;
			break;
		case 0xf7:
			opbytes = print_op1 ( opcode, pc, "rst\t6");
			break;
		case 0xf8:
			opbytes = print_op1 ( opcode, pc, "rm");
			break;
		case 0xf9:
			opbytes = print_op1 ( opcode, pc, "sphl");
			break;
		case 0xfa:
			opbytes = print_op3 ( opcode, pc, "jm\t", opcode[2], opcode[1]);
			// opbytes = 3;
			break;
		case 0xfb:
			opbytes = print_op1 ( opcode, pc, "ei");
			break;
		case 0xfc:
			opbytes = print_op3 ( opcode, pc, "cm\t", opcode[2], opcode[1]);
			// opbytes = 3;
			break;
		case 0xfe:
			opbytes = print_op2 ( opcode, pc, "cpi\t", opcode[1]);
			// opbytes = 2;
			break;
		case 0xff:
			opbytes = print_op1 ( opcode, pc, "rst\t7");
			break;
		default:
			opbytes = print_unk ( opcode, pc );
			break;
	}

	return opbytes;
}

/* THE END */
