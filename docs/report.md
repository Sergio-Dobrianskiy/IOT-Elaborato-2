# Assignment #02 - Smart Drone Hangar

**Studente:**
- Sergio Dobrianskiy (matr. 0001019553)  

[Repository Github](https://github.com/Sergio-Dobrianskiy/IOT-Elaborato-2.git)
[Video](https://youtu.be/OgXl_vaSwfY?si=mMaW5FSMNkpD5Uk6)


## Abstract 
La FSM del progetto è composta da **8 stati**, ottenuti combinando lo **stato delle porte dell’hangar** (Closed, Opening, Open, Closing) con lo **stato del drone** (Rest, Waiting, Taking-off, Landing, Operating).

Rispetto alle specifiche, per la gestione delle porte sono stati introdotti due stati intermedi, **Opening** e **Closing**, necessari per modellare correttamente il comportamento fisico dell’attuatore: in questo modo il sistema attende che trascorra **DOOR_TIME** prima di considerare la porta completamente aperta o chiusa, evitando di avviare decollo/atterraggio mentre le porte sono ancora in movimento.

All’accensione il sistema esegue un breve **check di funzionamento delle porte**, effettuando un ciclo di apertura/chiusura; terminata questa fase, lo stato di default diventa **porta chiusa e drone a riposo** (`CLOSED_REST`).

Il comportamento operativo segue due flussi principali:

* **Take-off**: dalla condizione di riposo con porte chiuse, una richiesta valida porta allo stato **Opening**, poi a **Open/Waiting**; il decollo parte solo con porta aperta e termina quando il drone risulta stabilmente all’esterno (soglia **D1** mantenuta per almeno **T1**), dopodiché le porte passano a **Closing** e infine a **Closed/Operating**.
* **Landing**: dalla condizione “drone operativo” con porte chiuse, la richiesta di rientro avvia **Opening**, poi **Open/Waiting** e quindi **Landing**; l’atterraggio si conclude quando il drone risulta stabilmente all’interno (soglia **D2** mantenuta per almeno **T2**), quindi le porte si richiudono passando a **Closed/Rest**.

Infine, per facilitare il collaudo tramite l’interfaccia Java, è stato aggiunto un pulsante che **attiva/disattiva manualmente lo stato di allarme dell’hangar**. Questo consente di testare rapidamente i comportamenti legati all’allarme senza dipendere esclusivamente dal sensore di temperatura, che in condizioni reali sarebbe l’unico responsabile dell’attivazione e del reset dell’allarme.


## Grafico
```mermaid
stateDiagram-v2
    direction TB

    [*] --> CLOSED_REST
    state "Door: CLOSED<br/>Drone: REST" as CLOSED_REST
    state "Door: CLOSED<br/>Drone: OPERATING" as CLOSED_OPERATING
    state "Door: OPENING<br/>Drone: WAITING" as OPENING_WAITING
    state "Door: OPEN<br/>Drone: WAITING" as OPEN_WAITING
    state "Door: OPEN<br/>Drone: TAKING_OFF" as OPEN_TAKING_OFF
    state "Door: OPEN<br/>Drone: LANDING" as OPEN_LANDING
    state "Door: CLOSING<br/>Drone: OPERATING" as CLOSING_OPERATING
    state "Door: CLOSING<br/>Drone: REST" as CLOSING_REST

    %% Typical flow: request -> opening -> open waiting -> action -> closing -> closed
    CLOSED_REST --> OPENING_WAITING : take-off request acknowledged
    CLOSED_OPERATING --> OPENING_WAITING : landing request acknowledged

    OPENING_WAITING --> OPEN_WAITING : elapsed time > DOOR_TIME

    OPEN_WAITING --> OPEN_TAKING_OFF : take-off sequence starts
    OPEN_WAITING --> OPEN_LANDING : landing sequence starts

    OPEN_TAKING_OFF --> CLOSING_OPERATING : distance >= D1 && elapsed time > T1 (stable outside)
    OPEN_LANDING --> CLOSING_REST : distance <= D2 && elapsed time > T2 (stable inside)

    CLOSING_OPERATING --> CLOSED_OPERATING : elapsed time > DOOR_TIME
    CLOSING_REST --> CLOSED_REST : elapsed time > DOOR_TIME
```

## TODO
Per far far funzionare il progetto servono, se si usa VS Code, servono:
- PlatformIO
- Pacchetto Java
- nel file `Arduino\Assignment-02-Drone-Hangar\java\src\iot\drone_carrier\DashboardLauncher.java` 
  cambiare `String portName = "COM5";` inserendo la porta che viene utilizzata dal proprio pc
- nel file `Assignment-02-Drone-Hangar\arduino\src\config.h` settare i PIN utilizzati per il proprio Arduino