
hw_timer_t *My_timer = NULL;
int TimerTick; 

bool SysTimer_10ms;
bool SysTimer_20ms;
bool SysTimer_50ms;
bool SysTimer_100ms;
bool SysTimer_200ms;
bool SysTimer_500ms;
bool SysTimer_1s;   //1000 ms
bool SysTimer_5s;   //5000 ms
bool SysTimer_10s;  //10000 ms

void Timer_Init(){
  //Init variables
  TimerTick = 0;
  SysTimer_10ms = FALSE;
  SysTimer_20ms = FALSE;
  SysTimer_50ms = FALSE;
  SysTimer_100ms = FALSE;
  SysTimer_200ms = FALSE;
  SysTimer_500ms = FALSE;
  SysTimer_1s  = FALSE;   
  SysTimer_5s  = FALSE;   
  SysTimer_10s = FALSE;  
   // initialize timer1 
  My_timer = timerBegin(0, 80, true); //80 prescaler -> 1 000 000 tick
  timerAttachInterrupt(My_timer, &onTimer, true);
  timerAlarmWrite(My_timer, 1000, true); //every 1 ms
  timerAlarmEnable(My_timer);
}

void onTimer(){
  //cant call uart from interrupt
  TimerTick++;
  if(TimerTick % 10 == 1){
    SysTimer_10ms = TRUE;
  }
  if(TimerTick % 20 == 1){
    SysTimer_20ms = TRUE;
  }
  if(TimerTick % 50 == 1){
    SysTimer_50ms = TRUE;
  }
  if(TimerTick % 100 == 1){
    SysTimer_100ms = TRUE;
  }
  if(TimerTick % 200 == 1){
    SysTimer_200ms = TRUE;
  }
  if(TimerTick % 500 == 1){
    SysTimer_500ms = TRUE;
  }
  if(TimerTick % 1000 == 1){
    SysTimer_1s = TRUE;
  }
  if(TimerTick % 5000 == 1){
    SysTimer_5s = TRUE;
  }
  if(TimerTick % 10000 == 1){
    SysTimer_10s = TRUE;
  }
}

bool CheckTimerState(int _FreqTyp){
  switch(_FreqTyp){
    case 10:{
        if(SysTimer_10ms){
          SysTimer_10ms = FALSE;
          return TRUE;
        }else{
          return FALSE;
        }
      break;
    }

    case 20:{
        if(SysTimer_20ms){
          SysTimer_20ms = FALSE;
          return TRUE;
        }else{
          return FALSE;
        }
      break;
    }
    case 50:{
        if(SysTimer_50ms){
          SysTimer_50ms = FALSE;
          return TRUE;
        }else{
          return FALSE;
        }
      break;
    }
    case 100:{
        if(SysTimer_100ms){
          SysTimer_100ms = FALSE;
          return TRUE;
        }else{
          return FALSE;
        }
      break;
    }
    case 200:{
        if(SysTimer_200ms){
          SysTimer_200ms = FALSE;
          return TRUE;
        }else{
          return FALSE;
        }
      break;
    }
    case 500:{
        if(SysTimer_500ms){
          SysTimer_500ms = FALSE;
          return TRUE;
        }else{
          return FALSE;
        }
      break;
    }
    case 1000:{
        if(SysTimer_1s){
          SysTimer_1s = FALSE;
          return TRUE;
        }else{
          return FALSE;
        }
      break;
    }
    case 5000:{
        if(SysTimer_5s){
          SysTimer_5s = FALSE;
          return TRUE;
        }else{
          return FALSE;
        }
      break;
    }
    case 10000:{
        if(SysTimer_10s){
          SysTimer_10s = FALSE;
          return TRUE;
        }else{
          return FALSE;
        }
      break;
    }
    
    default:{
      return FALSE;
    }
  }
}
