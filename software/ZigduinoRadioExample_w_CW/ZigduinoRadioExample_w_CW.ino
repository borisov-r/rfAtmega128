/*
Run this sketch on two Zigduinos, open the serial monitor at 9600 baud, and type in stuff
Watch the Rx Zigduino output what you've input into the serial port of the Tx Zigduino
*/

#include <ZigduinoRadio.h>

int incomingByte = 0;

void setup()
{
  // ZigduinoRadio.begin(11);
  Serial.begin(9600);
  // ZigduinoRadio.attachError(errHandle);
  // ZigduinoRadio.attachTxDone(onXmitDone);
}

void loop()
{
  if (Serial.available())
  {
      incomingByte = Serial.read();
      Serial.print("Received data: ");
      Serial.println(incomingByte, DEC);

      if (incomingByte == 70)                  // Shift + 'f' - start CW transmitf
      {
        int process_start = cwStart();
        delay(1);

        if (process_start == 1)
        {
            Serial.println("CW started.");

            while (process_start == 1)
            {
               if (Serial.available())
               {
                  incomingByte = Serial.read();

                  if (incomingByte == 83)        // Shift + 's' - stop CW transmit
                  {
                    process_start = cwStop();
                    Serial.println("CW stoped.");
                  }
               }
            }
        }

        else
        {
           Serial.println("PLL not locked.");
        }
      }
  }

  delay(100);
}

void errHandle(radio_error_t err)
{
  Serial.println();
  Serial.print("Error: ");
  Serial.print((uint8_t)err, 10);
  Serial.println();
}

void onXmitDone(radio_tx_done_t x)
{
  Serial.println();
  Serial.print("TxDone: ");
  Serial.print((uint8_t)x, 10);
  Serial.println();
}

int cwStart()
{
  int count = 1000;
  int offset;


  TRXPR |= TRXRST;    // Reset the transceiver
  IRQ_MASK |= PLL_LOCK_EN; // Set IRQ mask register, enable PLL_LOCK interrupt and set global AVR IRQ enable
  TRX_CTRL_1 = 0x00;  // Disable TX_AUTO_CRC_ON
  TRX_STATE = 0x03;   // FORCE_TRX_OFF
  PHY_CC_CCA = 0x32;  // Set Channel 18 (2440MHz) mode 1(Energy above threshold)
  PHY_TX_PWR = 0x0A;  // Set Power to Pmax = 3,5 dBm - PHY_TX_PWR = 0x00; | Set power to 0.5 dBm - PHY_TX_PWR = 0x06; 

  do{
    delay(1);
    count--;
  } while ((TRX_STATUS != 0x08) && (count));
  if (count == 0){
    return (0);
  }

  TST_CTRL_DIGI = 0x0F; // Enable Continuous Transmission Test Mode – step # 1
  TRX_CTRL_2 = 0x03;    // Enable High Data Rate Mode, 2Mb/s
  RX_CTRL = 0xA7;       // ???? Configure High Data Rate Mode
  TRXFBST = 128;        // Frame lenght
  for (offset = 1; (TRXFBST + offset) <= TRXFBEND; offset++){\
    _SFR_MEM8(0x180 + offset) = 0xFF;   //  fCH + 0.5 MHz, CW signal
  }
  PART_NUM = 0x54;     // Enable Continuous Transmission Test Mode – step # 2
  PART_NUM = 0x46;     // Enable Continuous Transmission Test Mode – step # 3
  TRX_STATE = 0x09;    // Enable PLL_ON state

  count = 1000;

  do{
    delay(1);
    count --;
  } while (!(IRQ_STATUS | 0x01)); // Wait for PLL_LOCK interrupt
  if (count == 0){
    return (0);
  }
  TRX_STATE = 0x02;  // Initiate Transmission, enter BUSY_TX state
  return(1);
}

int cwStop()
{
   PART_NUM = 0x00;  // Disable Continuous Transmission Test Mode
   TRXPR |= TRXRST;  // Reset the transceiver
   return(0);
}
