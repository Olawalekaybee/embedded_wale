#define code 5

int mark[code];
String Empty = " ";
bool isfirst = false;
String o[code];
String m, save;
bool a, b, c, d, e;

void setup() {

  Serial.begin(115200);

}

void loop() {

  Code(1);

}

void Code(int n) {
  
  for (int i = 0; i < code; i++)
  {
    mark[0] = 1111;mark[1] = 1112;mark[2] = 1113;mark[3] = 1114;mark[4] = 1112;
    
    Serial.println("Enter your password.");
    while (Serial.available() == 0) {
    }
    o[i] = Serial.readString();
    
    Serial.println("YOUR PASSWORD NO:" + o[i]);

    if (Serial.available() == 0) {
      save = (save, (((a ,(mark[0]==o[i].toInt())? true : false))||(mark[1]==o[i].toInt()) ||(mark[2]==o[i].toInt()) ||(mark[3]==o[i].toInt()) ||(mark[4]==o[i].toInt())) ? "Correct" : "Incorrect");
      //Serial.println(save);
      if (save=="correct" && a==true){
           a = false;
         Serial.println("valid");
         if(a==false){ 
          Serial.println("data used");
          }
         }
        }
    else {
      Serial.println("Input Value");
    }


  }
}
