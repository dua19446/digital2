#include <SPI.h>
#include <SD.h>

// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;
int lecturaserial;
const int chipSelect = PA_3; //cs PIN
File archivo;
void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  SPI.setModule(0);

  Serial.print("\nInitializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  pinMode(PA_3, OUTPUT);     // change this to 53 on a mega


  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card is inserted?");
    Serial.println("* Is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    return;
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }

  // print the type of card
  Serial.print("\nCard type: ");
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Unknown");
  }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    return;
  }


  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print("\nVolume type is FAT");
  Serial.println(volume.fatType(), DEC);
  Serial.println();

  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize *= 4096;                            // SD card blocks are always 512 bytes
  Serial.print("Volume size (bytes): ");
  Serial.println(volumesize);
  Serial.print("Volume size (Kbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (Mbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);


  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
  root.openRoot(volume);

  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);

/*  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");

  Serial.print("Apache 1 para la figura de corazon");
  Serial.print("\nApache 2 para la figura de lentes");
  Serial.print("\nApache 3 para la figura de pokebola");*/

}


void loop(void) {

  /*if (Serial.available() > 0) {
    lecturaserial = Serial.read();
    if (lecturaserial == 49) { // tecla 1 INFORMACI??N DE LA TARJETA
      Corazon();
        Serial.print("Apache 1 para la figura de corazon");
  Serial.print("\nApache 2 para la figura de lentes");
  Serial.print("\nApache 3 para la figura de pokebola");
    }
    if (lecturaserial == 50) { // tecla 2 GUARDA TEXTO
      Lentes();
        Serial.print("Apache 1 para la figura de corazon");
  Serial.print("\nApache 2 para la figura de lentes");
  Serial.print("\nApache 3 para la figura de pokebola");
    }
    if (lecturaserial == 51) { // tecla 3 MUESTRA EL TEXTO
      Pokebola();
        Serial.print("Apache 1 para la figura de corazon");
  Serial.print("\nApache 2 para la figura de lentes");
  Serial.print("\nApache 3 para la figura de pokebola");
    }
  }*/

}

  void Corazon(void) {
    archivo = SD.open("corazon.txt");

    if (archivo) {
      Serial.print("\nEl contenido de: ");
      Serial.println("corazon.txt");
      while (archivo.available()) {
        Serial.write(archivo.read());
      }
      archivo.close();
    } else {
      Serial.print("\nError abriendo "); Serial.println("corazon.txt");
      archivo.close();
    }

  }

  void Lentes(void) {
    archivo = SD.open("lentes.txt");

    if (archivo) {
      Serial.print("\nEl contenido de: ");
      Serial.println("lentes.txt");
      while (archivo.available()) {
        Serial.write(archivo.read());
      }
      archivo.close();
    } else {
      Serial.print("\nError abriendo "); Serial.println("lentes.txt");
      archivo.close();
    }

  }

  void Pokebola(void) {
    archivo = SD.open("pokebola.txt");

    if (archivo) {
      Serial.print("\nEl contenido de: ");
      Serial.println("pokebola.txt");
      while (archivo.available()) {
        Serial.write(archivo.read());
      }
      archivo.close();
    } else {
      Serial.print("\nError abriendo "); Serial.println("pokebola.txt");
      archivo.close();
    }

  }
