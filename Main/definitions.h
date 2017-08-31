//moving all the variable definitions here because arduino
// concats all ino files alphabetically

// properly initiliazing all variables to avoid memory misalignment issues

// unsigned int hour = 0 , minute = 0, second = 0, day = 0, month = 0, year = 0;

// float temperature = 0.0;
// float humidity = 0.0;

// int CO2 = 0;
// unsigned int PM1 = 0,PM25 = 0,PM10 = 0;
// char PIR = '0';


unsigned int hour = 0, minute = 0, second = 0, day = 0, month = 0, year = 0;

float temperature = 0.0;
float humidity = 0.0;

int CO2 = 0;
unsigned int PM1 = 0, PM25 = 0, PM10 =0;
char PIR = '0';
// char Buffer[54] = "\0";
char Buffer[66] = "\0";

/// make sd buffer smaller by chunking then reduce global buffer

// All the p versions of our functions are macros that use the PSTR macro for working with flash 
// memory succinctly

#define show_P(arg) flash_show(PSTR(arg))
#define save_P(arg) flash_save(PSTR(arg))
// #define layout_P(arg1, ...) layout(PSTR(arg1), __VA_ARGS__)
