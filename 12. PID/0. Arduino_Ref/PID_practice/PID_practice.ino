
#define sampling_time     
#define inv_sampling_time 1/sampling_time

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

void PID_setup (void)
{   
      cli();                // stop interrupt

      /* RESET T/C1 */
      TCCR2A=0;
      TCCR2B=0;
      TIMSK2=0;

      /*Setup T/C 1*/
      TCCR2B=0x04;            // khoi dong timer scale/64=250 000 Hz
      TCNT2=6;                 // 1ms=250

      /*Timer/Counter 1 Interrupt(s) initialization */
      TIMSK2=(1<<TOIE2);    
      sei()             ;    // cho phep ngat toan cuc
}

void Motor_Speed_PID(long int des_Speed)
{
  rSpeed=Pulse-pre_Pulse;
  pre_Pulse=Pulse;
  Err=des_Speed-abs(rSpeed);

  //cac thanh phan PID
  pPart=Kp*Err;
  dPart=Kd*(Err-pre_Err)*inv_sampling_time;
  iPart+=Ki*Err*sampling_time;

  Output+=pPart+dPart+iPart;
  pre_Err=Err;
}
