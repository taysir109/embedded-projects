//******ARDUINO IDE NEEDS TO BE INSTALLED TO RUN THE CODE ALONG WITH ARDUINO*******//
int i=0,j=0,k,n,q,p,t;
float x=34.9,y=46,z=30,valx=0.034,valy=0.037,valz=0.038;
class read_value{
  protected:
  String name;float length,breadth,height,inches,diameter;
  float duration,distance;double volume;
float read_val(int a,int b,float value){
    inches=0;
    int echoPin=a;
    int trigPin=b,
    sum=0,dis=0;
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT);

    for(int f=1;f<=20;f++){
      digitalWrite(trigPin, LOW);   // Makes trigPin low
      delay(2);       // 2 mili second delay 
      digitalWrite(trigPin, HIGH);  // tigPin high 
      delayMicroseconds(10);      // trigPin high for 10 micro seconds
      digitalWrite(trigPin, LOW);   // trigPin low
      duration = pulseIn(echoPin, HIGH); //Read echo pin, time in microseconds
      dis=duration/10;
      sum+=dis;
    }
    distance = (sum/20)*10*value/2.0;        //Calculating actual/real distance
    inches = distance / 2.54;
    return distance;
  }
  void read_name(){
    Serial.println("Name of the object: ");
    while(Serial.available()==0){}
    name=Serial.readString();
    Serial.println(name);
  }
};
class dimention:public read_value
{	
public:
	void cube_getter()
	{  
    read_name();
    breadth = 0; height = 0;diameter = 0;
    length = x-read_val(2,3,valx); delay(20);    //reading values from sensors
	  volume = length*length*length; delay(20);
    setter();
		i++;   
	}
	void cuboid_getter()
	{
		read_name();diameter=0;
    length  = x - read_val(2,3,valx);  delay(20);           //pinNumber where sensor is attached
    breadth = y - read_val(4,5,valy);  delay(20);          //pinNumber
    height  = z - read_val(6,7,valz);  delay(20);           //pinNumber
		volume  = length*breadth*height;
		setter();
    i++;
	}
	void cone_getter()
	{
		read_name();
    length=0;breadth=0;
    diameter = x - read_val(2,3,valx);
    height   = z - read_val(6,7,valz);
		volume   = 3.1416*(diameter*diameter*height)/12;
    setter();
    i++;
	}
	void cylinder_getter()
	{
		read_name();
    length=0;breadth=0;
    diameter = read_val(2,3,valx) - x;
    height   = read_val(6,7,valz) - z;	
		volume=3.1416*(diameter*diameter*height)/4;
    setter();
    i++;
	}
	void sphere_getter()
	{
		read_name();
    length=0;breadth=0;height=0;
    diameter = read_val(2,3,valx) - x;
		volume=3.1416*(diameter*diameter*diameter)/6;
    setter();
    i++;
	}
  void length_(){
    read_name();
    diameter=0;breadth=0;height=0,volume=0;
    length = read_val(2,3,valx) - x;
    setter();
    i++;
  }
  void height_(){
    read_name();
    diameter=0;breadth=0;length=0,volume=0;
    height = read_val(6,7,valz) - z;
    setter();
    i++;
  }
  
	void setter()
	{
    Serial.print(".........(");Serial.print(j+1);Serial.println(")..........");
    Serial.print("Name of the object:     ");Serial.println(name);
    Serial.print("Length of the object:   ");Serial.println(abs(length));
    Serial.print("Breadth of the object:  ");Serial.println(abs(breadth));
    Serial.print("Height of the object:   ");Serial.println(abs(height));
    Serial.print("Diameter of the object: ");Serial.println(abs(diameter));
    Serial.print("Volume of the object:   ");Serial.println(abs(volume));j++;
	}
};
class display{
  public:
  static void print()
	{
    Serial.println("\t\t\t\t________________________\t\t\t\t");
    Serial.println("\t\t\t\t Auto Dimention Counter \t\t\t\t");
    Serial.println("\t\t\t\t________________________\t\t\t\t");
    Serial.println("1) Calculate My Object Dimention:-");
    Serial.println("2) Show previous Entry :-");
    Serial.println("3) Exit:-");
    Serial.println("make your choice");
	}
	static void print_2()
	{
    Serial.print(".........(");
    Serial.print(k);
    Serial.println(")..........");
    Serial.println("1) Cube");
    Serial.println("2) Cuboid");
    Serial.println("3) Cone");
    Serial.println("4) Cylinder");
    Serial.println("5) Sphere");
    Serial.println("6) Length");
    Serial.println("7) Height");
    Serial.println("make your choice");
    k++;
	}
};
class adminLogin{
  private:
  int admin(){
    String username="faysal",password="taysir",user,pass;
    Serial.println("UserName: ");
    while(Serial.available()==0){}
    user=Serial.readString();Serial.println(user);  
    Serial.println("Password: ");
    while(Serial.available()==0){}
    pass=Serial.readString();Serial.println(pass);  
    if(user==username && pass==password){
      return 5;
    }
    else return 0;  
  }
  friend int admin_worker();    // user and password will remain protected
};
void setup(){       // ***********************like void main()
  Serial.begin(9600);
	dimention a[10];
  int n_value();int q_value();
  login:
  p=admin_worker();
  if(p==5){  // ******************* admin
    while(1){
      inside_login:
      display::print();j=0;
      t=t_value();
      if(t==2){     //*********** displaying 
        for(int j=0;j<i;j++)
          a[j].setter();
      }
      else if(t==1){    //**********input
			  n=n_value();
        while(n--){
				  display::print_2();
          q=q_value();
          input(q,a);   //*** sending the object array to the funtion  
		    }
      }
      else if(t==3) {
        Serial.println("***You Successfully Exited from the FrameWORK***");
        Serial.println("           THANKS FOR STAYING WITH US     \n\n\n");
        goto login;
      } 
		}
  }
  else if(p==0){
    Serial.println("********        INVALID ACCESS          ************");
    Serial.println("                  TRY AGAIN                         ");
    goto login;
  }
}
void input(int q,dimention a[]){
  if(q==1)
    a[i].cube_getter();
  else if(q==2)
    a[i].cuboid_getter();
  else if(q==3)
	  a[i].cone_getter();
	else if(q==4)
	  a[i].cylinder_getter();
	else if(q==5)
		a[i].sphere_getter();
  else if(q==6)
	  a[i].length_();
	else if(q==7)
		a[i].height_();
} 
int admin_worker(){ //******************* friend funtion of adminLogin class
  adminLogin a;
  Serial.println("\n\nWelcome to Automatic Dimention Counter frameWork ");
  Serial.println("Sir please write ''login'' to enter");
  while(Serial.available()==0){}
  String s=Serial.readString();
  if(s=="login")
    return a.admin();
  else 
    return 0;
}
int n_value(){
  Serial.println("Number of Objects you Want to measure: ");
	while(Serial.available()==0){}
  n=Serial.parseInt();Serial.println(n);Serial.println("");k=1;
  return n;
}
int q_value(){
  while(Serial.available()==0){}
	q=Serial.parseInt();Serial.println(q);Serial.println("");
  return q;
}
int t_value(){
  while(Serial.available()==0){}
	t=Serial.parseInt();Serial.println(t);Serial.println("");
  return t;
}
void loop(){
}





