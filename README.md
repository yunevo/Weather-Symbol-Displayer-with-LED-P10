# ESP32 with Arduino framework 
This projects is run using Arduino framework with board WEMOS D1 MINI ESP32.
It aims to display weather symbols with the purpose for weather forecast. 
It can display 4 gifs representing sunny, cloudy, rainy and windy weather according to the states of two slide switches

# Components of the project are as follow:
![diagram](https://github.com/yunevo/Weather-Symbol-Displayer-with-LED-P10/assets/156734673/cf9da2ef-0fe3-42df-b317-fd419c855629)

# Pin configuration
To change the pin connection between ESP32 and other components please change the pin definition in src/main.cpp:
* LED P10 (OE, A, B, CLK, SCKL, DS)
* 2 slide switches (SW0, SW1) 
* Relay (RELAY)

# Static images captured from the running gifs 
![2024-01-16_15h40_17](https://github.com/yunevo/Weather-Symbol-Displayer-with-LED-P10/assets/156734673/17106d5a-24fc-4046-afc9-1f9df75c3822)

![2024-01-16_15h40_05](https://github.com/yunevo/Weather-Symbol-Displayer-with-LED-P10/assets/156734673/c68f6041-6b29-4ffa-973a-b24191147cc4)

![2024-01-16_15h40_29](https://github.com/yunevo/Weather-Symbol-Displayer-with-LED-P10/assets/156734673/41c453a7-de48-4cc7-8307-0b9bc0e8bde2)

![2024-01-16_15h41_05](https://github.com/yunevo/Weather-Symbol-Displayer-with-LED-P10/assets/156734673/5c72c5c2-a998-4861-b528-7796b8ed092e)


