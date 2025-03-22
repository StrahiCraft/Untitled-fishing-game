<h1>Dokumentacija</h1>
<h2>Ideja igrice</h2>
Ova igrica je zamisljena da bude pecaroska igrica u kojoj je cilj da igrac upeca sto vise riba je moguce kako bi osvojio najvisi score.
<h2>Koriscene biblioteke</h2>
U projektu su koriscene neke biblioteke, prva i najbitnija je <i>GLUT</i> biblioteka koja sluzi za renderovanje, uz nju smo takodje dobili template u kome su klase za <a href="GameTamplate/GameObject.h">GameObject</a>, <a href="GameTamplate/Primitives.h">Primitives</a>,  
<a href="GameTamplate/Input.h">Input</a> i <a href="GameTamplate/Sprite.h">Sprite</a>.<br>
Osim <i>GLUT-a</i> sam koristio <i><a href="https://github.com/g-truc/glm">GLM</a></i> biblioteku koja mi daje neke matematicke funkcije i vektore.<br>
Za renderovanje sprite-ova je koriscena <i><a href="https://github.com/SpartanJ/SOIL2">SOIL</a></i> biblioteka i za zvuk je koriscen <i>FMOD</i>.
<h2>Utility klase</h2>
<h3>Dictionary</h3>
Za ovaj projekat mi je bio potreban dictionary struktura podataka koju C++ nema, pa sam napravio svoju. Ovo sam uradio koristeci dve klase: <a href="GameTamplate/DictionaryItem.cpp">DictionaryItem</a> i <a href="GameTamplate/Dictionary.cpp">Dictionary</a>
<h4><a href="GameTamplate/DictionaryItem.cpp">DictionaryItem.cpp</a></h4>
Ova klasa je genericka klasa koja ima dve promenljive, jednu tipa <b>K</b> za kljuc i jednu tipa <b>V</b> za vrednost. Sve funkcije ove klase su samo za vracanje ovih promenljivih i vise sluzi kao "building block" za <a href="GameTamplate/Dictionary.cpp">Dictionary</a> klasu.
<h4><a href="GameTamplate/Dictionary.cpp">Dictionary.cpp</a></h4>
Moja implementacija dictionary-ja je nista drugo nego vektor tipa <a href="DictionaryItem.cpp">DictionaryItem</a>, i dictionary klasa je takodje genericka klasa na isti nacin kao item. Funkcije ove klase su sve koje bi se ocekivale od dictionary-ja da dodajemo, sklanjamo item-e, da im menjamo vrednost, da vidimo koliko ih ima i da vidimo da li dictionary sadrzi neki kljuc.
<h3><a href="GameTamplate/AudioManager.cpp">Audio Manager</a></h3>
Kao sto ime kaze ova klasa nam sluzi za rad sa zvukom. Korisit FMOD biblioteku da pusta zvuk i ova klasa je staticna tako da zvuk moze da se pusti od bilo gde. Da bi se neki zvuk ili pesma pustili prvo mora taj zvuk da se doda u <a href="GameTamplate/Dictionary.cpp">Dictionary</a> kome je kljuc string a vrednost zvuk, ovo se radi u <a href="GameTamplate/Main.cpp">Main</a> fajlu tokom inicijalizacije, ovo takodje vazi za sve pesme. Funkcije ove klase su: funkcija za inicijalizaciju koja inicijalizuje sistem za zvuk, funkcije za dodavanje i pustanje zvuka i slicne za muziku. Razlika izmedju funkcija za zvuk i muziku su to sto muzici treba kanal na kome se pusta, a zvuku ne. Ova klasa je radjena po uzoru one koja je u <i>LAMS</i> lekciji.
<h3><a href="GameTamplate/EventSystem.cpp">Event System</a></h3>
Moj sistem koji sam radio po onom koji ima C# programski jezik. Eventove cuva u <a href="GameTamplate/Dictionary.cpp">Dictionary-ju</a> kome je kljuc string a vrednost pointer na void funkciju bez parametara. To malo ogranicava koje funkcije mogu da se pozivaju ovim sistemom ali je zavrsilo posao za ovaj projekat, isto moze samo da poziva funkcije koje se nalaze u <a href="GameTamplate/Main.cpp">Main</a> fajlu zato sto se za svaku klasu razlikuju pointeri ka njihovim funkcijama posto su to pointeri na void funkcije od neke instance klase, sto jos vise ogranicava sistem, ali za projekat ove velicine skroz je zavrsio svoj posao. Kada bih povecavao projekat nasao bih nacin da prepravim ovaj sistem da bih se otarasio prethodno navedenih ogranicenja. <a href="GameTamplate/EventSystem.cpp">EventSystem</a> klasa je takodje staticna tako da joj se moze pristupiti od bilo gde. Njene funkcije su za dodavanje, sklanjanje funkcije, dodavanje kanala i sklanjanje kanala i konacno funkcija za pozivanje svih funkcija nekog kanala.
<h3><a href="GameTamplate/FishStats.cpp">Fish Stats</a></h3>
Ova klasa sluzi za citanje podataka iz .fish fajlova koji se nalaze <a href="GameTamplate/FishStats">ovde</a> i generisanja i cuvanja statistika odabrane ribe. Sve funkcije ove klase sluze za vracanje vrednosti navedenih podataka: sprite ribe, tezina ribe, brzina ribe, brzina hvatanja ribe, velicina krajnjeg kruga, score koji daje riba i njeno ime.
<h3><a href="GameTamplate/ScoreManager.cpp">Score Manager</a></h3>
U ovoj staticnoj klasi se desava sve vezano za score. Cuva trenutan score i najbolje scoreove koji se update-uju svaki put kada igrac zavrsi igru(ako je novi score veci od jednog od 5 najboljih, dodat je u listu i upisuje se u fajl). Za sortiranje high score-ova sam koristio optimizovani bubble sort algoritam. Ostale funkcije ove klase su za dodavanje novog scorea i za uzimanje high score-ova.
<h3><a href="GameTamplate/TextRenderer.cpp">Text Renderer</a></h3>
Posto sam odlucio da ne koristim ugradjen text renderer iz gluta, napravio sam svoj. Moj text renderer koristi sprite font i u sustini cuva vektor sprite-ova koji su svi offsetovani (svaki karakter je jedan sprite). Jedine funkcije ove klase su za setovanje teksta i za njegovo renderovanje.
<h3><a href="GameTamplate/Time.cpp">Time</a></h3>
Staticna klasa za stvari koje imaju veze sa vremenom, u sustini ona sluzi da mi daje nacin da skaliram delta time i da imam real time koji nije skaliran. Ova klasa postoji posto sam hteo da imam <a href="GameTamplate/ChaosControl.cpp">pickup koji zaustavlja vreme</a>.
<h3><a href="GameTamplate/BackgroundManager.cpp">Background Manager</a></h3>
Staticna klasa za rad sa pozadinom igrice. Boja pozadine se racuna pomocu custom lerp funkcije i gradijenta koji je definisan u kodu. Funkcija za racunanje boje radi tako sto joj damo odredjenu lerp vrednost (vrednost od 0 do 1) i ta vrednost je prebacena u novu vrednost (koja je isto izmedju 0 i 1) koja se koristi da bi se izracunala boja u tacci t izmedju tacke a i b, gde su a i b dve boje na gradijentu, a t boja izmedju njih.<br>
Ova klasa je takodje zaduzena za cuvanje i pomeranje <a href="GameTamplate/Bubble.cpp">mehura</a>.
<h2>Game Object klase</h2>
<h3>Pickup-ovi</h3>
U igrici postoje 3 pickup-a i svi nasledjuju klasu <a href="GameTamplate/Pickup.cpp">Pickup.cpp</a>, pickup klasa nasledjuje <a href="GameTamplate/GameObject.h">GameObject</a> klasu koju smo dobili za projekat. Pickup klasa ima funkcije za update i renderovanje koje dolaze iz game object-a, dodatne funkcije su mu za dobijanje njegove velicine, virtuelna funkcija koja se poziva kada igrac pokupi pickup i svaka klasa koja nasledjuje ovu mora da definise sta se desi i funkcija za pomeranje pickup-a. Pickup uvek ide sa desna na levo, ali i ova funkcija moze da se predefinise kako bi se drugacije pomerao pickup.
<h4><a href="GameTamplate/Ring.cpp">Ring.cpp</a></h4>
Ovaj pickup je manje vise ista stvar kao prstenje iz Sonic igrica (cak je i spritesheet iz jedne), prsten povecava igracev score za zadat broj kada je pokupljen, taj broj je 1 po default-u.
<h4><a href="GameTamplate/ChaosControl.cpp">ChaosControl.cpp</a></h4>
Radjeno po moci od Shadow The Hedgehoga, ovaj pickup zaustavlja vreme na 5 sekundi i stvara zeleni overlay. (Za ovo mi je trebala <a href="GameTamplate/Time.cpp">time</a> klasa).
<h4><a href="GameTamplate/BurstStream"></a>BurstStream.cpp</h4>
Radjeno po napadu od legendarne karte "Blue Eyes White Dragon", ovaj pickup se stvara u fazi "<a href="GameTamplate/ReelingIn.cpp">Reeling in</a>" i kada je pokupljen unistava sve bombe dok laser prolazi po ekranu.
<h3>UI elementi</h3>
Ovde idu game object-i koji su UI elementi, ovde je verovatno mogao da bude svrstan i <a href="GameTamplate/TextRenderer.cpp">text renderer</a> ali sam odlucio njega da svrstam u utility klasu.
<h4><a href="GameTamplate/Button.cpp">Button</a></h4>
Klasicno dugme, moze da se napravi na nekoliko nacina: prvi je da mu damo tekst, font i pozadinu, drugi je da mu damo tekst, font i boju pozadine (ovaj sam ja koristio svuda u projektu posto je najlaksi za koriscenje) i poslednji kome samo dajemo pozadinu. Dugme funkcionise tako sto kad god kliknemo, unutar stanja u kome smo se poziva funkcija koja proverava da li je tacka na koju smo kliknuli unutar nekog dugmeta od tog stanja (stanja su u sustini razlicite scene, vise o njima kasnije), nakon cega se poziva onClick funkcija koja poziva event koji smo namestili pri kreiranju dugmeta.
<h4><a href="GameTamplate/ProgressBar.cpp">ProgressBar.cpp</a></h4>
Ova klasa je za liniju koja se puni ili prazni u zavisnosti od kog stanja u igri smo i pokazuje nam ili koliko vremena je ostalo da upecamo ribu ili jos koliko vremena imamo da je uhvatimo. Sastoji se iz vise slojeva: pozadine, decay sloja koji se javlja kada naglo promenimo vrednost, da bi dao vise glatku animaciju i glavnog progress sloja. Funkcije ove klase su sve za manipulisanje ovim slojevima.
<h3><a href="GameTamplate/Bomb.cpp">Bomb</a></h3>
Glavna prepreka igrice dok izvlacimo ribu. Kada igrac udari u nju <a href=GameTamplate/ProgressBar.cpp>progress bar</a> se smanjuje za odredjenu kolicinu.
<h3><a href="GameTamplate/Fish.cpp">Fish</a></h3>
Klasa koja radi sve vezano sa ribom. Ako je igra u stanju pecanja, riba se nasumicno pomera po ekranu i igrac treba da drzi udicu blizu nje kako bi krenuo da je peca. Kada igra pocne, ribi su ucitane statistike iz jednog od .fish fajlova koji su definisani u <a href="GameTamplate/Main.cpp">Main.cpp</a>.
<h3><a href="GameTamplate/Hitbox.cpp">Hitbox</a></h3>
Objekti ove klase blokiraju put igracu i koristi se za kamenje koje se nasumicno stvara pri pocetku igre.
<h3><a href="GameTamplate/Player.cpp">Player</a></h3>
Igrac se pomera na WASD i pokusava da upeca ribu, nakon sto je zakaci na udicu, igrac je usporen u zavisnosti od tezine ribe.
<h2>Game State klase</h2>
Game state klase u ovom projektu su klase koje koristim kao scene. Bazicna klasa, <a href="GameTamplate/GameState.cpp">GameState.cpp</a> sadrzi reference na igraca i ribu, kao i na sve dugmice koji se nalaze unitar tog stanja. Takodje je u svakom stanju moguce da se pauzira igrica, samo sto ako u nekom stanju zelimo da implementiramo pauzu, moramo da dodamo nacin da menjamo _paused bool.
<h3><a href="GameTamplate/Bubble.cpp">Bubble</a></h3>
Pozadinski element koji cini igricu da se oseca kao da je pod vodom, moze biti jedan od 7 mogucih sprite-ova.
<h3>Stanja pecanja</h3>
<h4><a href="GameTamplate/Fishing.cpp">Fishing.cpp</a></h4>
Pocetno stanje igre (ne racunajuci main meni i tako to, vec kad zapocnemo nas pokusaj), u kom igrac pokusava da krene da peca ribu, u ovom stanju se stvaraju pickup-ovi i stva se kamenje koje blokira igraca.
<h4><a hreef="GameTamplate/ReelingIn.cpp">ReelingIn.cpp</a></h4>
Stanje upecavanja ribe, igrac drzi ribu na udici sto ga usporava u zavisnosti od njene tezine, i igrac mora da izbegava bombe dok mu se progress bar ne napuni. Bombe dolaze sa vrha ekrana i sto je igrac blize vrhu ekrana to se brze puni progress bar.
<h4><a href="GameTamplate/FishCaught.cpp">FishCaught.cpp</a></h4>
U ovom stanju se igracu prikazuje sta je upecao i score ribe se dodaje njegovom trenutnom.
<h3>Main menu stanja</h3>
Stanja koja su meniji.
<h4><a href="GameTamplate/Intro.cpp">Intro.cpp</a></h4>
Intro scena, kada se igrica pali pise ime igrice i moje ime, prezime i indeks.
<h4><a href="GameTamplate/MainMenu.cpp">MainMenu.cpp</a></h4>
Main meni igrice, odavde moze da se zapocne igra, pogleda high score i da se iskljuci igra.
<h4><a href="GameTamplate/HighScore.cpp">HighScore.cpp</a></h4>
Ovde su prikazani 5 najboljih high score-ova.
<h3>Game Over stanje</h3>
Kada igrac izgubi tako sto mu istekne vreme dok peca ili udari u previse bombi ovde zavrsi, odavde moze da se vrati na main meni ili da igra ponovo.
