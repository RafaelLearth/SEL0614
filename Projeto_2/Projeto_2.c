unsigned char TMR0H_preset = 0xB;
unsigned char TMR0L_preset = 0xDC;

unsigned char displayNum = 0;

void incrementUntil9(unsigned char *n){
  //Incrementar valor apontado por n
  (*n) += 1;

  // Caso acima de 9, retornar o valor para 0
  if(*n >= 10){
    (*n) = 0;
  }
}

void out7Seg(unsigned char n)
{
  switch (n)
  {      // acionamento do display de 7 segmentos do kit EasyPIC (PORTD)
    case 0:{ latd = 0b00111111; break;}   // 0 no display de 7seg.
    case 1:{ latd = 0b00000110; break;}   // 1 no display de 7seg.
    case 2:{ latd = 0b01011011; break;}   // 2 no display de 7seg.
    case 3:{ latd = 0b01001111; break;}   // 3 no display de 7seg.
    case 4:{ latd = 0b01100110; break;}   // 4 no display de 7seg.
    case 5:{ latd = 0b01101101; break;}   // 5 no display de 7seg.
    case 6:{ latd = 0b01111101; break;}   // 6 no display de 7seg.
    case 7:{ latd = 0b00000111; break;}   // 7 no display de 7seg.
    case 8:{ latd = 0b01111111; break;}   // 8 no display de 7seg.
    case 9:{ latd = 0b01101111; break;}   // 9 no display de 7seg.
    default:{ latd = 0b00000000; break;} // entrada inv�lida, apagar display
  }

}

void INTERRUPCAO_HIGH() iv 0x0008 ics ICS_AUTO {
  // vetor de tratamento da interrup��o (endere�o fixo 0x0008)
  // Definir em Tools > Interrupt Assistant
  // HIGH = interrup��o de alta prioridade
  // LOW = interrup��o de baixa prioridade (endere�o 0x0018)
  // ics = servi�o de acionamento/tratamento da interrup��o


  // tratamento - acionar LED
  if(INTCON.TMR0IF == 1)    //Foi o TIMER0 que gerou a interrup��o ?
  {
    out7Seg(displayNum);
    incrementUntil9(&displayNum);

    TMR0H += TMR0H_preset;
    TMR0L += TMR0L_preset;
    INTCON.TMR0IF = 0;   //N�o esquecer de zerar a Flag
  }
}

void configInterrupt(){
  //Configura��o Global das interrup��es GIE   - chave geral que sinaliza que o
  //programa usar� interrup��es
  INTCON.GIE = 1; // Alta prioridade   - usar somente SE RCON.IPEN =1;

  RCON.IPEN = 1; //habilita n�veis de prioridade - permite que uma interrup��o
  //tenha prioridade no tratamento caso ocorra ao mesmo tempo que outro tipo de
  // interrup��o ou que interrompa uma interrup��o de baixa priordade em atendimento

  INTCON.TMR0IE = 1;   //Habilita a interrup��o individual do TIMER0
}

void configMCU()
{
  // Configurando os pinos como digitais
  ADCON1 |= 0x0F;
  // Config. das portas
  TRISD = 0;    // PORTD como sa�da  (usar LED)
  PORTD = 0;    // LED inicialmente OFF
}

void configTimer(){
  // Timer0 Registers:// 16-Bit Mode; Prescaler=1:32; TMRH Preset=B; TMRL Preset=DC; Freq=1,00Hz; Period=1,00 s
  T0CON.TMR0ON = 1;// Timer0 On/Off Control bit:1=Enables Timer0 / 0=Stops Timer0
  T0CON.T08BIT = 0;// Timer0 8-bit/16-bit Control bit: 1=8-bit timer/counter / 0=16-bit timer/counter
  T0CON.T0CS   = 0;// TMR0 Clock Source Select bit: 0=Internal Clock (CLKO) / 1=Transition on T0CKI pin
  T0CON.T0SE   = 0;// TMR0 Source Edge Select bit: 0=low/high / 1=high/low
  T0CON.PSA    = 0;// Prescaler Assignment bit: 0=Prescaler is assigned; 1=NOT assigned/bypassed
  T0CON.T0PS2  = 1;// bits 2-0  PS2:PS0: Prescaler Select bits
  T0CON.T0PS1  = 0;
  T0CON.T0PS0  = 0;
  TMR0H = TMR0H_preset;    // preset for Timer0 MSB register
  TMR0L = TMR0L_preset;    // preset for Timer0 LSB register
}

void main() {
  // Configura��o inicial do MCU
  configMCU();
  configTIMER();
  configInterrupt();
  
  
  while(1);
}