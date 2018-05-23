#include "RedBearDuoRequiredManual.h"

#include "ble_config.h"
#include "ble_constants.h"

#include "MulticolorThreePinLed.h"
#include "UltrasonicRangeFinder.h"

#include "pitches.h"

#include "pins.h"


//
// Hardware declarations
//

MulticolorThreePinLed output_led(pin_led_red, pin_led_green, pin_led_blue);
Servo servo;
UltrasonicRangeFinder ultrasonic(pin_ultrasonic_trigger, pin_ultrasonic_echo);

//
// Board LED
//
/*
void SetRGB(byte r, byte g, byte b)
{
  RGB.color(r, g, b);
}
*/



void setup() {
  Serial.begin(9600);
  delay(5000);
  Serial.println("Begin Setup");
  
  //RGB.control(true);
  // put your setup code here, to run once:
  output_led.Setup();
  ultrasonic.Setup();
  
  pinMode(pin_piezo, OUTPUT);

/*
  pinMode(pin_led_red, OUTPUT);
  pinMode(pin_led_green, OUTPUT);
  pinMode(pin_led_blue, OUTPUT);
*/
  servo.attach(pin_servo);

  SetupBle();
}

const byte motor_degree_min = 65;
const byte motor_degree_max = 115;


// 0 to 180

byte degree_previous = 90;
void HardwareControlMoveMotorToPosition(byte degree)
{
  if (degree == degree_previous)
  {
    return;
  }

  degree_previous = degree;
  
  if (degree < motor_degree_min)
  {
    degree = motor_degree_min;
  }
  else if (degree > motor_degree_max)
  {
    degree = motor_degree_max;
  }
  
  Serial.print("Motor: ");
  Serial.println(degree);
  
  servo.write(degree);
}


void HardwareControlAlarm()
{
    tone(pin_piezo, NOTE_A6, 1000);
    output_led.On();
    output_led.SetColor(color::BLUE);
    delay(1000);
    output_led.Off();
}


int current_range_centimeters = 400;

void loop()
{
  /*
  // put your main code here, to run repeatedly:
  float range_centimeters = ultrasonic.RangeCentimeters();
  
  // Print out results
  if ( range_centimeters > 400 ) {
    //Serial.println("Out of range");
  } else {
    Serial.print(range_centimeters);
    Serial.println(" cm");
  }
*/
  //current_range_centimeters = range_centimeters;
  
  //Serial.println("loop");
/*
    analogWrite(pin_led_red, 255);
    analogWrite(pin_led_green, 255);
    analogWrite(pin_led_blue, 255);
  delay(5000);
  //output_led.On();
  //delay(2000);
*/
  // LED
/*
    analogWrite(pin_led_red, 0);
    analogWrite(pin_led_green, 0);
    analogWrite(pin_led_blue, 0);
    delay(5000);
  //*/

  /*
  output_led.On();
  output_led.SetColor(color::RED);
  //output_led.On();
  delay(1000);
  output_led.SetColor(color::GREEN);
  //output_led.On();
  delay(1000);
  output_led.SetColor(color::BLUE);
  delay(1000);
  output_led.Off();
  delay(1000);
  */
  
  // Sound
  /*
  tone(pin_piezo, NOTE_A6, 1000);
  delay(1000);
  //*/
  
  // Servo
  /*
  servo.write(0);
  delay(10000);
  servo.write(90);
  delay(10000);
  servo.write(180);
  delay(10000);
  //*/







/*
  for (int i = 0; i < 256; i++)
  {
    Serial.println(i);
    analogWrite(pin_piezo, i);
    delay(100);
    analogWrite(pin_piezo, 0);
    delay(100);
  }
*/

/*
  // notes_length
  for (int i = 0; i < 1; i++)
  {
    Serial.println(notes[i]);
    
  }
  noTone(pin_piezo);
  */
  
  //analogWrite(pin_led_red,128);
  //output_led.On();
  //RGB.color(0, 0, 0);
  //delay(500);
  //output_led.Off();
  //delay(500);



}





// Bel handle


/**
 * @brief Connect handle.
 *
 * @param[in]  status   BLE_STATUS_CONNECTION_ERROR or BLE_STATUS_OK.
 * @param[in]  handle   Connect handle.
 *
 * @retval None
 */
void bleConnectedCallback(BLEStatus_t status, uint16_t handle) {
  switch (status) {
    case BLE_STATUS_OK:
      Serial.println("BLE device connected!");
      //digitalWrite(BLE_DEVICE_CONNECTED_DIGITAL_OUT_PIN, HIGH);
      break;
    default: break;
  }
}

/**
 * @brief Disconnect handle.
 *
 * @param[in]  handle   Connect handle.
 *
 * @retval None
 */
void bleDisconnectedCallback(uint16_t handle) {
  Serial.println("BLE device disconnected.");
  //digitalWrite(BLE_DEVICE_CONNECTED_DIGITAL_OUT_PIN, LOW);
}



/**
 * @brief Callback for receiving data from Android (or whatever device you're connected to).
 *
 * @param[in]  value_handle  
 * @param[in]  *buffer       The buffer pointer of writting data.
 * @param[in]  size          The length of writting data.   
 *
 * @retval 
 */
int bleReceiveDataCallback(uint16_t value_handle, uint8_t *buffer, uint16_t size) {

  if (receive_handle == value_handle)
  {
    memcpy(receive_data, buffer, RECEIVE_MAX_LEN);

    ///*
    Serial.print("Received data: ");
    for (uint8_t index = 0; index < RECEIVE_MAX_LEN; index++)
    {
      Serial.print(receive_data[index]);
      Serial.print(" ");
    }
    Serial.println(" ");
    //*/
    
    // process the data. 
    if (receive_data[0] == 0x01)
    { //receive the face data 
      // CSE590 Student TODO
      // Write code here that processes the FaceTrackerBLE data from Android
      // and properly angles the servo + ultrasonic sensor towards the face
      // Example servo code here: https://github.com/jonfroehlich/CSE590Sp2018/tree/master/L06-Arduino/RedBearDuoServoSweep   


      byte motor_position = receive_data[1];
      HardwareControlMoveMotorToPosition(motor_position);

      if (receive_data[2] > 0 && current_range_centimeters < 50)
      {
        HardwareControlAlarm();
      }
      
      
    }
  }
  return 0;
}

/**
 * @brief Timer task for sending status change to client.
 * @param[in]  *ts   
 * @retval None
 * 
 * Send the data from either analog read or digital read back to 
 * the connected BLE device (e.g., Android)
 */
static void bleSendDataTimerCallback(btstack_timer_source_t *ts) {
  // CSE590 Student TODO
  // Write code that uses the ultrasonic sensor and transmits this to Android
  // Example ultrasonic code here: https://github.com/jonfroehlich/CSE590Sp2018/tree/master/L06-Arduino/RedBearDuoUltrasonicRangeFinder
  // Also need to check if distance measurement < threshold and sound alarm

  //Serial.println("BLE SendDataTimeCallback");

  float range_centimeters = ultrasonic.RangeCentimeters();
  int range_cm = (int) range_centimeters;

  current_range_centimeters = range_cm;

  Serial.print(range_cm);
  Serial.println(" cm");

  if (ble.attServerCanSendPacket())
  {
    send_data[0] = (0x0A);
    send_data[1] = highByte(range_cm);
    send_data[2] = lowByte(range_cm);
    ble.sendNotify(send_handle, send_data, SEND_MAX_LEN);
  }

  // Restart timer.
  ble.setTimer(ts, _sendDataFrequency);
  ble.addTimer(ts);
  
}
