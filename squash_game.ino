//機盒按鈕，比數 point_1 : point_2
const int point_1 = A5;
const int point_2 = 1;
const int R = 2;
const int L = A4;
const int hot = A3;
const int rest = 7;
//7段顯示器（共陽）
const int a = 5;
const int b = 3;
const int c = 4;
const int d = 6;
const int dp = A2;
const int one = 8;
const int two = 9;
const int three = A0;
const int four = A1;

int pointA = 0 ;//A的得分
int pointB = 0 ;//B的得分
int i = 0 ;//區別 A or B 的連續得分
int site = 0 ;//1右   2左  
int hot_point = 0 ;//讀取熱身輸入
int rest_point = 0 ;//讀取休息輸入

// 定義七個節段的腳位，將 A, B, C, D, E, F, G 依序放入陣列
byte segs[4] = { a , b , c , d };

// 定義共陽極七段顯示器的字型(digit pattern)
// define the LED digit patterns, from 0 - 9
// 0 = LED on, 1 = LED off, in this order:
//                Mapping to       a,b,c,d,e,f,g of Seven-Segment LED
byte seven_seg_digits[10][4] = { { 0,0,0,0 },  // = 0
                                 { 1,0,0,0 },  // = 1
                                 { 0,1,0,0 },  // = 2
                                 { 1,1,0,0 },  // = 3
                                 { 0,0,1,0 },  // = 4
                                 { 1,0,1,0 },  // = 5
                                 { 0,1,1,0 },  // = 6
                                 { 1,1,1,0 },  // = 7
                                 { 0,0,0,1 },  // = 8
                                 { 1,0,0,1 }   // = 9
                             }; 

// 定義每個七段顯示器顯示的時間 (延遲時間), 預設 1ms 
int delay_time = 1;

void setup() {
  //機盒按鈕
  pinMode(point_1 , INPUT);
  pinMode(point_2 , INPUT);
  pinMode(R , INPUT);
  pinMode(L , INPUT);
  pinMode(hot , INPUT);
  pinMode(rest , INPUT);
  //7段顯示器(7447)
  pinMode(a , OUTPUT);
  pinMode(b , OUTPUT);
  pinMode(c , OUTPUT);
  pinMode(d , OUTPUT);  
  pinMode(dp , OUTPUT);
  pinMode(one , OUTPUT); 
  pinMode(two , OUTPUT);
  pinMode(three , OUTPUT);
  pinMode(four , OUTPUT);    
}

void loop() {

  print_point();
  
  if(digitalRead(point_1)==HIGH)
  {
    
    pointA++;//加一分

    if( i == 2 )//A連續得分
    {
      det_site();
    }

    else//換發球權
    {
      switch_sit();      
    }
    i=2;
    delay(20);
  }

  if(digitalRead(point_2)==HIGH){
    pointB++;

    if( i == 3 ){//B連續得分
      det_site();
    }

    else{//換發球權
      switch_sit();     
    }
    i=3;
    delay(20);
  }

  if ( win() ){
    for (unsigned int number = 0 ; number <= 3; number++) {
      // 每一秒鐘計數一次
      unsigned long startTime = millis();
     for (unsigned long elapsed=0; elapsed < 1000; elapsed = millis() - startTime) {
       // 多工掃瞄，輪流點亮個、十、百、以及千位數的七段顯示器
       print_point();  
      }
      delay(250);  
    }
    pointA=0;
    pointB=0;
    i=1;// i!=2 && i!=3              
  }
  
  if( digitalRead(hot) == HIGH ){
  passing(2,150);//熱身
  pointA = 0 ;
  pointB = 0 ;
  i=1;
  }
  
  if( digitalRead(rest)== HIGH ){
  passing(1,90);//休息90秒
  pointA = 0 ;
  pointB = 0 ;
  i=1;
  }
}

void det_site()//判斷位置
{
    switch(site){
      case 1:site=2 ; break;
      case 2:site=1 ; break;
    }
}

void switch_sit(){
   do{
        if(digitalRead(R) == HIGH){
          site = 1 ;
          delay(20);
          break;
        }

        if(digitalRead(L) == HIGH){
          site = 2 ;
          delay(20);
          break;
        }
      }while( 1 );
}

int win(){//判斷輸贏
    if (pointA==11 && pointB<10){
        return 1;
    }
    
    else if (pointB==11 && pointA<10){
        return 1;
    }
    
    else if (pointA>=10 && pointB>=10){
        if ( (pointA-pointB)==2 ){
            return 1;
        }
        
        else if ( (pointB-pointA)==2 ){
            return 1;
        }
    }
    return 0;
}

void passing(int i , int sec)
{
  for( ; i > 0 ; i-- ){
    for (unsigned int number = sec ; number > 0 ; number--) {
      // 每一秒鐘計數一次
      unsigned long startTime = millis();
     for (unsigned long elapsed=0; elapsed < 1000; elapsed = millis() - startTime) {//1/4秒
       // 多工掃瞄，輪流點亮個、十、百、以及千位數的七段顯示器
      
        // 顯示個位數
        lightDigit(1 , number%10);
        delay(delay_time);
        // 顯示十位數
        lightDigit(2,(number/10)%10);
        delay(delay_time);
        // 顯示百位數
        lightDigit(3,(number/100)%10);            
        delay(delay_time);
        // 顯示千位數
        lightDigit(4,(number/1000)%10);
        delay(delay_time);            
      }    
    }
//    digitalWrite(bee);
//    delay(500);
//    digitalWrite(bee);
//    delay(500);
//    digitalWrite(bee);
  }
}

// 選擇顯示的位數 (4:千、3:百、2:十、或 1:個位數)
void pickDigit(int x) {
  digitalWrite(one, LOW);
  digitalWrite(two, LOW);
  digitalWrite(three, LOW);
  digitalWrite(four, LOW);
  digitalWrite( dp , HIGH );
 
  switch(x) {
    case 1: digitalWrite(one, HIGH); break;
    case 2: digitalWrite(two, HIGH); break;
    case 3: digitalWrite(three, HIGH); break;
    case 4: digitalWrite(four, HIGH); break;    
  }
}

// 點亮" i "位數
void lightDigit( int i , int number) {
  pickDigit(i);   
  lightSegments(number);  
}

// 點亮七段顯示器
void lightSegments(byte number) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(segs[i], seven_seg_digits[number][i]);
  }
}

void print_point()//顯示分數
{  
  // 顯示b個位數
  lightDigit(1 , pointB%10);
  
  if( i == 3 ){
    if( site == 1 ){    
      digitalWrite( dp , LOW );//B得分，右邊發球
    }
  }
  delay(delay_time);
  
  // 顯示b十位數
  lightDigit(2,(pointB/10)%10);
  
  if( i == 3 ){
    if( site == 2 ){
       digitalWrite( dp , LOW );//B得分，左邊發球    
    }
  }
  delay(1);
  
  // 顯示a個位數
  lightDigit(3,pointA%10);   

  if( i == 2 ){
    if( site == 1 ){
       digitalWrite( dp , LOW );//A得分，右邊發球     
    }
  }
  delay(1);
  
  // 顯示a十位數
  lightDigit(4,(pointA/10)%10);
  
  if( i == 2 ){
    if( site == 2 ){
       digitalWrite( dp , LOW );//A得分，左邊發球 
    }
  }
  delay(1); 
  digitalWrite(four, LOW);
}
