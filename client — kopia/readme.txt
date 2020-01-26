Opis:

RconClient.py:
W pliku tym znajduje się klasa umożliwiająca na komunikację z naszą łodzią podwodną.
Klasa ta ma umożliwiać wysyłanie pakietów oraz ich odbieranie.

Ma istnieć możliwość włączania potwierdzenia odebrania pakietów oraz ich retransmisja 
(ilość retransmisji oraz timeout).

Możliwość oczekiwania na odpowiedź odpowiadającą wysłanemu pakietowi z zadanym timeoutem.

AuvAR.py:
AuvAddressResolver - klasa umożliwiająca na pozyskanie adresu łodzi.
Łódź wysyła na adres rozgłoszeniowy swoją sygnaturę, co kilka sekund.
Nasłuchując takich transmisji i rozpoznając w nich sygnaturę łodzi, można zdobyć jej adres.

client.py:
Główny plik klienta.
Najpierw pozyskuje adres łodzi.
Następnie się z nim łączy.