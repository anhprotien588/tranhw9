/*
 * This script takes 3 command-line arguments as input to control the GPIO LED
 * The first argument is the gpio number for one pin used for output (GPIO60)
 * The second argument is the state of that pin (GPIO60)
 * The third argument is the gpio number for the pin used for input (GPIO46)
 *Example invocations: ./control_GPIO 60 hi 46 or ./controlGPIO 60 low 46
 */

#include<iostream>
#include<sstream>
#include<fstream>
using namespace std;

#define GPIO_PATH "/sys/class/gpio/"
void writeGPIO(string gpio_number,string filename, string value){
  ostringstream s;
  fstream fs;
  s << "gpio" << gpio_number;
  string name = string(s.str());
  string path = GPIO_PATH + name;
  fs.open((path + filename).c_str()); 
  fs << value;
  fs.close();
}

void setDirection(string gpio_number,string filename, string direction){
  ostringstream s;
  fstream fs;
  s << "gpio" << gpio_number;
  string name = string(s.str());
  string path = GPIO_PATH + name;
  fs.open((path + filename).c_str());
  fs << direction;
  fs.close();
}

string readGPIO(string gpio_number,string filename){
  ostringstream s;
  fstream fs;
  s << "gpio" << gpio_number;
  string name = string(s.str());
  string path = GPIO_PATH + name;
  fs.open((path + filename).c_str());
  string input;
  getline(fs,input);
  fs.close();
  return input;
}

int main(int argc, char*argv[]){
   if(argc!=4){
	   cout << "Usage is: control_GPIO gpio_number state gpio_number " << endl;
	   cout << "  gpio_number: GPIO number to control" << endl;
	   cout << "  state: low or hi" << endl;
           cout << " e.g. control_GPIO 60 hi 46" << endl;
   }
   string cmd1(argv[1]);
   string cmd2(argv[2]);
   string cmd3(argv[3]);
   if(cmd2=="low"){
	   cout << "Setting the GPIO_" << cmd1 << " to low" << endl;
	   setDirection(cmd1,"/diretion","out");
	   writeGPIO(cmd1,"/value","0");
   }

   else if(cmd2=="hi"){
	   cout << "Setting the GPIO_" << cmd1 << " to high" << endl;
	   setDirection(cmd1,"/direction","out");
	   writeGPIO(cmd1,"/value","1");
   }
   cout << "The value of GPIO_" << cmd3 << " is: " << endl;
   cout << readGPIO(cmd3,"/value") << endl;
}
