#include <M5StickCPlus2.h>
#include <BluetoothA2DPSource.h>
#include <LittleFS.h>

BluetoothA2DPSource a2dp_source;

// O código comentado é para o uso do módulo joystick

// const int pinX = 25;  //  Pino eixo X
// const int pinY = 26;  //  Pino eixo Y


SoundData* loadSound(const char* path) {
    File file = LittleFS.open(path, "r");
    if (!file) {
        Serial.println("Erro ao abrir o arquivo de áudio.");
        return nullptr;
    }
    size_t length = file.size();
    int8_t* buffer = new int8_t[length];
    file.readBytes((char*)buffer, length);
    file.close();
    return new OneChannel8BitSoundData(buffer, length);
}

void setup() {
    Serial.begin(115200);
    auto cfg = M5.config();
    StickCP2.begin(cfg);

    if (!LittleFS.begin()) {
        Serial.println("Erro ao inicializar o LittleFS");
        return;
    }

    StickCP2.Display.setRotation(3);
    StickCP2.Display.setTextColor(GREEN);
    StickCP2.Display.setTextDatum(middle_center);
    StickCP2.Display.setTextFont(&fonts::Orbitron_Light_24);
    StickCP2.Display.setTextSize(1);
    StickCP2.Display.drawString("Aperte pra\n frase", StickCP2.Display.width() / 2,
                                  StickCP2.Display.height() / 2);

    a2dp_source.start("Anker SoundCore");
    a2dp_source.set_volume(20);

}

void loop() {
    StickCP2.update();

    // int xValue = analogRead(pinX);
    // int yValue = analogRead(pinY);

    // Serial.println(xValue);
    // Serial.println(yValue);

    // if (yValue > 3600) { // Cima
    //     StickCP2.Display.clear();
    //     StickCP2.Display.drawString("Bom dia", StickCP2.Display.width() / 2, StickCP2.Display.height() / 2);
    //     SoundData* bom_dia = loadSound("/bom_dia.bin");
    //     a2dp_source.write_data(bom_dia);
    //     delay(1000); // Delay para evitar múltiplas leituras
        
    // } else if (yValue < 500) { // Baixo
    //     StickCP2.Display.clear();
    //     StickCP2.Display.drawString("Boa tarde", StickCP2.Display.width() / 2, StickCP2.Display.height() / 2);
    //     SoundData* boa_tarde = loadSound("/boa_tarde.bin");
    //     a2dp_source.write_data(boa_tarde);
    //     delay(500);
    // }

    // if (xValue > 3600) { // Esquerda
    //     StickCP2.Display.clear();
    //     StickCP2.Display.drawString("Por favor", StickCP2.Display.width() / 2, StickCP2.Display.height() / 2);
    //     SoundData* por_favor = loadSound("/por_favor.bin");
    //     a2dp_source.write_data(por_favor);
    //     delay(500);

    // } else if (xValue < 500) { // Direita
    //     StickCP2.Display.clear();
    //     StickCP2.Display.drawString("Obrigado", StickCP2.Display.width() / 2, StickCP2.Display.height() / 2);
    //     SoundData* obrigado = loadSound("/obrigado.bin");
    //     a2dp_source.write_data(obrigado);
    //     delay(500);
    // }

    if (StickCP2.BtnA.wasPressed()) {
      StickCP2.Display.clear();
      StickCP2.Display.drawString("Pix", StickCP2.Display.width() / 2, StickCP2.Display.height() / 2);
      SoundData* pix = loadSound("/pix.bin");
      a2dp_source.write_data(pix);
      delay(500);

    }

    if (StickCP2.BtnB.wasPressed()) {
      StickCP2.Display.clear();
      StickCP2.Display.drawString("Cachaca", StickCP2.Display.width() / 2, StickCP2.Display.height() / 2);
      SoundData* cachaca = loadSound("/cachaca.bin");
      a2dp_source.write_data(cachaca);
      delay(500);
    }
    
    if (M5.BtnPWR.wasPressed()) {
      StickCP2.Display.clear();
      StickCP2.Display.drawString("Neymar", StickCP2.Display.width() / 2, StickCP2.Display.height() / 2);
      SoundData* neymar = loadSound("/neymar.bin");
      a2dp_source.write_data(neymar);
      delay(500);
    }

    delay(10);

}