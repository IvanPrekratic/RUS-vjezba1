# RUS-vjezba1
Rješenje zadanog zadatka za vježbu 1 iz kolegija Razvoj ugradbenih sustava <br>
Link na Wokwi projekt: https://wokwi.com/projects/426955490900012033
!![alt text](image.png)

# Opis zadatka
Ovaj projekt demonstrira korištenje prekida na mikrokontroleru koristeći Arduino Uno. Implementirani su različiti prekidi za obradu signala s tipkala, tajmera i senzora udaljenosti (HC-SR04). 

# Komponente
-Arduino Uno<br>
-3x Tipkala<br>
-4x LED diode<br>
-HC-SR04<br>

# Funkcionalnosti
1. Detekcija pritisaka tipkala s prioritetima<br>
Visoki prioritet (prekid INT0, pin 2)<br>
Srednji prioritet (prekid INT1, pin 3)<br>
Niski prioritet (ručno provjeravanje u glavnoj petlji, pin 4)<br><br>
2. Timer prekid (1 sekunda interval)<br>
Svake sekunde pokreće funkciju za mjerenje udaljenosti pomoću HC-SR04 senzora.<br><br>
3. Mjerenje udaljenosti i aktivacija LED indikatora<br>
Kada je udaljenost manja od 10 cm, uključuje se LED indikator (pin 11).<br><br>
4. Obrada svih prekida u glavnoj petlji prema prioritetima<br>
Prvo se obrađuju prekidi najvišeg prioriteta.<br>
Niski prioritet (tipka na pinu 4) se provjerava samo kada nema viših prioriteta.<br>
