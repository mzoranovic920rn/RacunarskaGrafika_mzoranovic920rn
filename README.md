# RacunarskaGrafika_mzoranovic920rn

Dokumentacija za projekat: 

Ideja za projekat je bila galerija, koja se dosta pojednostavila tokom izrade — najviše tehnika i efekata je primenjeno na jednom eksponatu u prostoru. 

Korišćene tehnike:

1. Post-processing
Rađena su dva efekta — vinjeta (zatamnjenje na rubovima ekrana) i filmsko zrno (animirani šum preko cele slike).

2. Proceduralne šare
Na podu i na zidu je šara generisana proceduralno u šejderu, nije učitana iz slike.

3. GUI/tekst u 3D prostoru
Na postolju se nalazi mala pločica sa tekstom, iscrtana kao tekstura i postavljena na 3D objekat u prostoru.

4. Animirani sistem čestica (Animated particle systems)
Oko kristala kruže čestice — kombinacija kružnog kretanja i lebdenja gore-dole, animirano u realnom vremenu.

5. Opšta 3D grafika
Kreirana je soba sa zidovima i podom  sa osvetljenjem po strani objekta (svaka strana ima svoju normalu pa se drugačije osvetljava u zavisnosti od ugla). Kamera se kreće preko WASD/space/shift i ograničena je da ne izađe iz sobe. Svi 3D objekti u prostoru (kristal, postolje, kutije, kupa, valjak) su proceduralno generisani ručnim pisanjem koordinata temena. Kristal se dodatno i rotira oko svoje ose (animacija).

6. Nove i/ili modifikovane šejdere (shader programe)
Korišćeno je više novih/prilagođenih šejdera: glavni šejder za scenu, poseban šejder za pločicu, i po jedan šejder za svaki post-processing efekat.
