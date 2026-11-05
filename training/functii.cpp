
#include <Arduino.h>
#include "functii.h"
void task1_setup()
{
   // put your setup code here, to run once:

  DDRB |=(1<<DDB5) | (1<<DDB4) | (1<<DDB3);
  PORTB |=(1<<PORTB5) | (1<<PORTB4) | (1<<PORTB3);
}
volatile uint32_t timer;
void task1()
{
   PORTB &=~(1<<PORTB5);
  PORTB &=~(1<<PORTB4); // toate ledurile stinse
  PORTB &=~(1<<PORTB3);
  timer=180000;
  while(timer--); // un delay
  
  PORTB |=(1<<PORTB5); 
  PORTB &=~(1<<PORTB4);   // led 1=1, led 2=0, led3=0;
  PORTB &=~(1<<PORTB3);
  timer=180000;
  while(timer--);
  PORTB |=(1<<PORTB5);
  PORTB |=(1<<PORTB4);    //led 1=1 led2=1 led3=0;
  PORTB &=~(1<<PORTB3);
  timer=180000;
  while(timer--);
  PORTB |=(1<<PORTB5);
  PORTB |=(1<<PORTB4);  //led 1=1 led2=1 led3=1;
  PORTB |=(1<<PORTB3);
  timer=180000;
  while(timer--);
}
void task2_setup()
{
  DDRB |=(1<<DDB2) | (1<<DDB1); //led 1 lled 2
  PORTB |=(1<<PORTB2) | (1<<PORTB1);
  DDRD &=~(1<<DDD2); //butonul
  PORTD |=(1<<DDD2); 
}
volatile uint32_t i;
volatile uint32_t stare=0;
void task2()
{
  i=PIND &(1<<PIND2); // citesc starea pinului PD2 (unde este legat butonul)
  if(i==0)
  {
    if(stare==i)
    {
    PORTB|=(1<<PORTB2); //led1=1
    PORTB &=~(1<<PORTB1); //led2=0
    stare=1;  //salvez noua stare ca la următoarea apăsare sa execute cealaltă ramura
    }
    else
    {
    PORTB &=~(1<<PORTB2); //led1=0
    PORTB |=(1<<PORTB1); //led2=1
    stare=0;
    }
     timer=180000;
    while(timer--); // pun un delay pt ca procesorul functioneaza foarte rapid si nu apuc sa mi ia starea
    while((PIND &(1<<PIND2))==0); // astept sa las butonul, ca o apasare sa schimbe o singura data
  } 
  

}
void task3_setup() {
  // put your setup code here, to run once:
  DDRB|=(1<<DDB5);  
  PORTB|=(1<<PORTB5);

  DDRD&=~(1<<DDD2); 
  PORTD|=(1<<PORTD2);

  EIMSK|=(1<<INT0); // permit intreruperi
  EICRA|=(1<<ISC01); // setez 1 0 sa reactioneze doar la coborari de la 1 la 0
  EICRA&=~(1<<ISC00);// 
  SREG |= (1 << 7); //activez intreruperile globale
  
}
ISR(INT0_vect) //vectorul de intreruperi 
{
  PORTB^=(1<<PORTB5);
}
void task3() {
  // put your main code here, to run repeatedly:
  
  
  
}
void task4_setup()
{
  DDRB |=(1<<DDB5) | (1<<DDB4) | (1<<DDB3);
  //PORTB |=(1<<PORTB5) | (1<<PORTB4) | (1<<PORTB3);
  PORTB &= ~((1 << PORTB5) | (1 << PORTB4) | (1 << PORTB3));

 
  TCCR1A = 0;
  TCCR1B = (1 << WGM12) | (1 << CS12); // CTC (clear timer on compare) // Prescaler 256 pornește timerul
  OCR1A = 15624; // valoarea maxima ((0.25sec *16.000.000/256)-1)
  TCNT1=0; //setez timer pe 0
}
volatile uint32_t pas=0;
void task4()
{
  if(pas>3)
  {
    pas=0;
  }
  if ((TIFR1 & (1 << OCF1A))!=0) // s a aprins flag-ul
  {
    TIFR1 = (1 << OCF1A);     // resetez flag la 0
    if(pas==0)
    {
    PORTB &=~(1<<PORTB5);
    PORTB &=~(1<<PORTB4); // toate ledurile stinse
    PORTB &=~(1<<PORTB3);
    }

    if(pas==1)
    {
    PORTB |=(1<<PORTB5); 
    PORTB &=~(1<<PORTB4);   // led 1=1, led 2=0, led3=0;
    PORTB &=~(1<<PORTB3);
    }

    if(pas==2)
    {
    PORTB |=(1<<PORTB5);
    PORTB |=(1<<PORTB4);    //led 1=1 led2=1 led3=0;
    PORTB &=~(1<<PORTB3);
    }

    if(pas==3)
    {
    PORTB |=(1<<PORTB5);
    PORTB |=(1<<PORTB4);  //led 1=1 led2=1 led3=1;
    PORTB |=(1<<PORTB3);
    }
    pas++;
  }
}
