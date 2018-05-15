#define RECEIVE_MAX_LEN  5 // TODO: change this based on how much data you are sending from Android 
#define SEND_MAX_LEN    3

// Must be an integer between 1 and 9 and and must also be set to len(BLE_SHORT_NAME) + 1
#define BLE_SHORT_NAME_LEN 8 

// The number of chars should be BLE_SHORT_NAME_LEN - 1. So, for example, if your BLE_SHORT_NAME was 'J', 'o', 'n'
// then BLE_SHORT_NAME_LEN should be 4. If 'M','a','k','e','L','a','b' then BLE_SHORT_NAME_LEN should be 8
// TODO: you must change this name. Otherwise, you will not be able to differentiate your RedBear Duo BLE
// device from everyone else's device in class.
#define BLE_SHORT_NAME 'M','a','k','e','L','a','b'  

//
// Will need to define these
//

// Device connected and disconnected callbacks
void bleConnectedCallback(BLEStatus_t status, uint16_t handle);
void bleDisconnectedCallback(uint16_t handle);

static btstack_timer_source_t send_characteristic;
static void bleSendDataTimerCallback(btstack_timer_source_t *ts); // function declaration for sending data callback
int _sendDataFrequency = 200; // 200ms (how often to read the pins and transmit the data to Android)






//
// Other Ble configurations
//

// UUID is used to find the device by other BLE-abled devices
static uint8_t service1_uuid[16]    = { 0x71,0x3d,0x00,0x00,0x50,0x3e,0x4c,0x75,0xba,0x94,0x31,0x48,0xf1,0x8d,0x94,0x1e };
static uint8_t service1_tx_uuid[16] = { 0x71,0x3d,0x00,0x03,0x50,0x3e,0x4c,0x75,0xba,0x94,0x31,0x48,0xf1,0x8d,0x94,0x1e };
static uint8_t service1_rx_uuid[16] = { 0x71,0x3d,0x00,0x02,0x50,0x3e,0x4c,0x75,0xba,0x94,0x31,0x48,0xf1,0x8d,0x94,0x1e };

// Define the receive and send handlers
static uint16_t receive_handle = 0x0000; // recieve
static uint16_t send_handle = 0x0000; // send

static uint8_t receive_data[RECEIVE_MAX_LEN] = { 0x01 };
int bleReceiveDataCallback(uint16_t value_handle, uint8_t *buffer, uint16_t size); // function declaration for receiving data callback
static uint8_t send_data[SEND_MAX_LEN] = { 0x00 };

// Define the configuration data
static uint8_t adv_data[] = {
  0x02,
  BLE_GAP_AD_TYPE_FLAGS,
  BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE, 
  
  BLE_SHORT_NAME_LEN,
  BLE_GAP_AD_TYPE_SHORT_LOCAL_NAME,
  BLE_SHORT_NAME, 
  
  0x11,
  BLE_GAP_AD_TYPE_128BIT_SERVICE_UUID_COMPLETE,
  0x1e,0x94,0x8d,0xf1,0x48,0x31,0x94,0xba,0x75,0x4c,0x3e,0x50,0x00,0x00,0x3d,0x71 
};



void SetupBle()
{
    // Initialize ble_stack.
  ble.init();
  
  // Register BLE callback functions
  ble.onConnectedCallback(bleConnectedCallback);
  ble.onDisconnectedCallback(bleDisconnectedCallback);

  //lots of standard initialization hidden in here - see ble_config.cpp
  configureBLE(); 
  
  // Set BLE advertising data
  ble.setAdvertisementData(sizeof(adv_data), adv_data);
  
  // Register BLE callback functions
  ble.onDataWriteCallback(bleReceiveDataCallback);

  // Add user defined service and characteristics
  ble.addService(service1_uuid);
  receive_handle = ble.addCharacteristicDynamic(service1_tx_uuid, ATT_PROPERTY_NOTIFY|ATT_PROPERTY_WRITE|ATT_PROPERTY_WRITE_WITHOUT_RESPONSE, receive_data, RECEIVE_MAX_LEN);
  send_handle = ble.addCharacteristicDynamic(service1_rx_uuid, ATT_PROPERTY_NOTIFY, send_data, SEND_MAX_LEN);

  // BLE peripheral starts advertising now.
  ble.startAdvertising();
  Serial.println("BLE start advertising.");

  // Start a task to check status of the pins on your RedBear Duo
  // Works by polling every X milliseconds where X is _sendDataFrequency
  send_characteristic.process = &bleSendDataTimerCallback;
  ble.setTimer(&send_characteristic, _sendDataFrequency); 
  ble.addTimer(&send_characteristic);
}


