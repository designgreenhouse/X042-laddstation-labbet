# x042
Laddstation 01 - Support id x042
Testkod som körs i labbet på Particle Photon

## Moduler
    Modul A3 - Laddningskontroll: Laddstation_M40 ( Partice med rely shield, övervakning, loggning och smart Power Supply)
    Modul A13 - Kommunikation : Mqtt Particle cloud ( Particle photon, GPS, OLED display )

## Funktioner
    Funktion 1 Particle Tinker, app för mobilapp.
    Funktion 2: Seriekommunikation med Nextion display
    Funktion 3: Logga batterispänning i Particle cloud
    Funktion 4: Logga cykelID (används ej)
    Funktion 5: Smart Powersupply, känner av spänning och kopplar in extern powersupply vid låg spänning (hysteresis)
    Funktion 6: Logga värden till Mqtt server skinny.skycharts.net
    Funktion 7: Integration förberedd för Node-Red

## Integrationer
    Particle Cloud
    - Node-Red som körs på RaspberryPI Zero
    MQTT server skinny.skycharts.net
    
