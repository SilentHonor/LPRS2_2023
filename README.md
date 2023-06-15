# LPRS2_2023

RF Networking

# O projektu
```
Projekat čine 4 Arduino Uno mikrokonrolera, i po jedan nRF24L01 Transciever modul povezan na svaki.
Svaki mikrokontroler sa Transciever modulom je u mogućnosti da komuniciraju sa drugim mikrokontrolerima, po multicast principu.
Drugim rečima, svaki mikrokontroler će primiti poruku poslatu sa jednog od njih
```

# Način rada
```
Ovaj projekat predstavlja način komunikacije između više Arduino UNO mikrokontrolera koristeći nRF24L01 transciever module.
Postavlja se jednostavan sistem slanja poruka gde jedan Arduino šalje poruke drugima.
Na početku potrebno je skinuti potrebne biblioteke RF24 i nRF24L01. Pored toga, definišu se RF24 objekat radi specificiranja CE i CSN
pinova, kao i niz koji adrese komunikacionih kanala. Radi skladištenja poruka, kreiran je i niz koji ima ulogu buffer-a.

U setup funkciji otvaramo kanale u režimu čitanja i pisanja preko kojih moduli komuniciraju serijski.

Loop funkcija se sastoji iz 2 dela:
1. - U prvi deo pokriva slučaj kada se poruka primi. U tom slučaju poruka biva ispisana na serijski
monitor i u zavisnosti od 'shouldEcho' flag-a, poruka se prenosi i drugim modulima izmenom kanala za pisanje. Ovo se radi da bi se
izbegla kolizija poruka, i da neki modul ne bi primio istu poruku više puta.
2. - Drugi deo pokriva slučaj kada korisnik unese poruku preko serijskog monitora da bi se slala drugim modulima. Uneta poruka biva pročitana, nakon čega se uklone prazna mesta sa početka i kraja poruke. Zatim, postavlja se 'shouldEcho' flag na true, zaustavlja se režim slušanja i preko petlje gde se menjaju kanali za pisanje, poruka se šalje svim ostalim modulima. Režim slušanja se ovde prekida zato što transciever ne može da sluša i da šalje poruke u isto vreme.

```

# Video koji je upotrebljen kao materijal za sastavljanje sistema

https://youtu.be/LhBIRMMAGGE

# Šema

![transciever pic](https://github.com/SilentHonor/LPRS2_2023_RF_Networking/assets/37028568/cd64998e-57a0-4932-b97c-35b82df74e9a)

# Demonstracija

https://youtu.be/TZ0xDiRO63o
