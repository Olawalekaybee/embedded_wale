#define code 5

int mark[code];
String Empty = " ";
bool isfirst = false;
String o[code];
String m, save;
bool a[code], b[code];

void setup()
{

  Serial.begin(115200);
}

void loop()
{

  Code(1);
}

void Code(int n)
{

  for (int i = 0; i < code; i++)
  {
    mark[0] = 1111; mark[1] = 1112; mark[2] = 1113; mark[3] = 1114; mark[4] = 1112;
   // mark[i] = {1111, 1112, 1113, 1114, 1115};
    Serial.println("Enter your password.");
    while (Serial.available() == 0)
    {
    }
    o[i] = Serial.readString();

    Serial.println("YOUR PASSWORD NO:" + o[i]);

    if (Serial.available() == 0)
    {
      a[i] = (*(a + i), (*(mark + i) == o[i].toInt()) ? true : false);
      Serial.println((String(m), ( ( b[i] !=0)&&(a[i] == 1)) ? "card Used" : (( b[i] !=0)&&(a[i] == 1)) ? "Access Granted" : "Access Denied"));
      if (a[i] == 1)
      {
        b[i] = false;
      }
       
      
    }
    else
    {
      Serial.println("Input Value");
    }
  }
}