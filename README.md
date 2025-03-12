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
Za ovaj projekat mi je bio potreban dictionary struktura podataka koju c++ nema, pa sam napravio svoju. Ovo sam uradio koristeci dve klase: <a href="GameTamplate/DictionaryItem.cpp">DictionaryItem</a> i <a href="GameTamplate/Dictionary.cpp">Dictionary</a>
<h4><a href="GameTamplate/DictionaryItem.cpp">DictionaryItem.cpp</a></h4>
Ova klasa je genericka klasa koja ima dve promenljive, jednu tipa <b>K</b> za kljuc i jednu tipa <b>V</b> za vrednost. Sve funkcije ove klase su samo za vracanje ovih promenljivih i vise sluzi kao "building block" za <a href="GameTamplate/Dictionary.cpp">Dictionary</a> klasu.
<h4><a href="GameTamplate/Dictionary.cpp">Dictionary.cpp</a></h4>
Moja implementacija dictionary-ja je nista drugo nego vektor tipa <a href="DictionaryItem.cpp">DictionaryItem</a>, i dictionary klasa je takodje genericka klasa na isti nacin kao item. Funkcije ove klase su sve koje bi se ocekivale od dictionary-ja da dodajemo, sklanjamo item-e, da im menjamo vrednost, da vidimo koliko ih ima i da vidimo da li dictionary sadrzi neki kljuc.
<h3><a href="GameTamplate/AudioManager.cpp">Audio Manager</a></h3>
