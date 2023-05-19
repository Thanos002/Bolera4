//PORTS:
#define MOTOR_PORT 1


//MACROS:
// B bit; P registro (p.e. PORTA o 1A), V valor, interrupcion I
#define setBit(P, B) (P |= (1 << B))

#define clearBit(P, B) (P &= ~(1 << B))

//invertir bit
#define toggleBit(P, B) (P ^= (1 << B))

// da el valor del bit
#define readBit(P, B) ((P >> B) & 0x01)

#define setOutput(P, B) (DDR##P |= (1 << B))
#define setInput(P, B) (DDR##P &= ~(1 << B))

#define writePWM(P, V) (OCR##P## = V)

// habilitar interrupciones externas
#define enableInterrupt(I) (EIMSK |= (1 << I))
#define disableInterrupt(I) (EIMSK &= ~(1 << I))
 
// para if/else, comprueba si pin numero B de puerto P es high/low
#define isHigh(P, B) (PIN##P & (1 << B))
 
#define isLow(P, B) (!(PIN##P & (1 << B)))