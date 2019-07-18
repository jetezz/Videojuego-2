# Videojuego-2
Videojuego creado con c++ y sfml

https://www.youtube.com/watch?v=_oH9T0xlglc


1.Ficha del juego
=====

Título del juego
Raid Humans

Sistema de juego
Estrategia y batalla. 

Público al que va dirigido
Pegi 7 el juego contiene acciones de batalla pero no una violencia explícita.

Resumen de la historia del juego orientada a la jugabilidad
El juego se basa en un sistema de niveles en el cual en los diferentes niveles aparecerán diferentes oleadas de enemigos de menor a mayor complejidad y el objetivo será matar el boss final de cada nivel. A lo largo del juego conforme se vaya avanzando de nivel se irán desbloqueando diferentes armas y torretas.

Distintos modos de juego 
A priori hemos decidido únicamente implementar un modo de juego, el modo historia. Es decir, el usuario deberá superar los diferentes niveles con sus respectivos bosses finales, aunque no descartamos añadir nuevas mejoras o diferentes modos de juego si lo consideramos necesario a lo largo del desarrollo.

 Puntos únicos de vuestro juego: cinco mínimo que destacan a vuestro juego del resto
Durante el avance del juego el personaje va adquiriendo nuevas skills.
El jugador puede modificar el mapa (colocación de torretas,minas, etc).
Sistema monetario interno, el jugador para poder mejorar y/o colocar nuevos elementos deberá almacenar monedas que obtendrá jugando.
Carga de una habilidad especial distinta por nivel.
El jugador puede luchar en tiempo real y enfrentarse a los enemigos de forma directa.

Juegos parecidos
Nuclear Throne
Plantas vs Zombies
Enter the Gungeon
Kingdom Rush

2.Ámbito y jugabilidad
=====


Jugabilidad
Al principio del juego se habilita el “Modo Compra”, en el cual, el jugador podrá comprar un par de torretas básicas con unas monedas iniciales que se les proporcionará al principio del juego. Una vez haya realizado la compra, tendrá que dar a un botón de play para que cambie al “Modo Oleada”.

En el momento que el jugador está en el modo oleada solamente tendrá las torretas que haya construido, su arma y su habilidad con los movimientos del personaje para defender el castillo.

Los enemigos están diseñados para que primero vayan a destruir aquello que esté más cerca de su alcance. Estos enemigos rodean a su objetivo y empiezan a destruir todo aquello que el jugador haya construido o atacar al enemigo directamente. 

Para finalizar el nivel, el jugador tendrá que destruir a todos los enemigos y recibirá una bonificación de monedas por superar el nivel que será mayor dependiendo de la ronda en la que estemos. Una vez recibidas las monedas, se volverá a habilitar el “Modo Compra” y dando paso a la siguiente fase. 

Si los enemigos derrotan al jugador o los enemigos destruyan el castillo, se finalizará el juego. 

Cuantificación
El juego se desarrollará en una Época medieval fantástica en la que tendremos que salvar el castillo de la ciudad de las oleadas enemigas. 
Contará con dos niveles, cada uno con diferentes oleadas 
Tendrá 3 tipos de NPCs, tres enemigos. Los enemigos tendrán diferentes objetivos: solo atacan a torretas o héroes. De esta manera diferenciamos qué tipo de enemigo aparece en cada oleada . Se generarán en diversos puntos, introduciendo aleatoriedad a la hora de generarse y seguir un camino abierto, que no todos los enemigos sigan el mismo camino pero sí un mismo objetivo. Los enemigos que vayan a atacar al héroe causarán daño físico. 
El jugador podrá acceder a las armas, torretas y objetos defensivos mediante un sistema de compra, que se generarán una vez finalizada la oleada l.Cuanto más rápido pases al siguiente nivel, mayor será el bonus de monedas recibidas. Estas monedas tendrá una vida de 15 segundos de vida, si no se recogen, desaparecerán. Las monedas también se pueden conseguir en el mismo momento en el que se destruyan a los enemigos.El jugador tendrá que ir a recoger las monedas y estas serán atraídas hacia él cuando esté cerca 
El jugador tendrá a su disposición dos tipos de armas. Dispondrá de un arma principal, que es una espada simple con la que tendrá que derrotar a los enemigos, y podrá utilizar un arma secundaria, que se desbloqueara mediante la compra de la misma en una tienda. 

Flujos de juego
Empieza el juego -> Tutorial(opcional) -> 
Bucle ( 
Animación -> Nivel [ Bucle ( 
Oleada enemigos -> Fase construcción ) -> Oleada final ) ]
) -> Resultados -> Fin.


3.Interfaz
=====

Sistema Visual

Es videojuego con un arte retro, con una vista aérea de la zona de juego.

HUD y Controles

Menús

En el menú inicial aparece el boton de jugar 
El menú de compra tendrá el mapa, el personaje(con sus movimientos) 4 botones (3 para comprar torretas o mejores y 1 para continuar )

Características Motor 2D: 
El motor 2D lo hemos implementado nosotros en SFML

Cámara:
Cámara fija con vista aérea.

Controles


W
Arriba
A
Izquierda
S
Abajo
D
Derecha
Click Izq
Atacar-> En modo lucha
Seleccionar/Colocar Torreta/ Mejorar arma -> En modo compra
F6
Modo Debug/ Modo Dios / Añadir dinero
Space
Añadir torreta -> en modo Dios


Sonido

El videojuego carece de sonido.

Sistema de ayuda

Al ser un juego bastante intuitivo, carece de un sistema de ayuda.


4.Mecánica
=====

Reglas del juego explícitas e implícitas

Fisica
La física del juego se desarrolla en un mundo 2D. El personaje realiza una animación que simula el movimiento de izquierda a derecha, pero de arriba hacia abajo se desplaza sin animación. También realiza una animación de ataque con la que da visibilidad a la hora de realizar dicha acción. Cuando el personaje está quieto, realiza una animación moviendo los hombros.
  
Movimiento
El movimiento del personaje está dirigido por el jugador. Los enemigos se mueven según la posición de los objetos que haya alrededor, eligiendo los más cercanos como los principales. El movimiento de las balas es lineal, hacia el enemigo más cercano en el momento de disparo.

Objetos
El objeto que se encuentra en el mapa es la moneda. Tiene un tiempo de vida y si el jugador no la recoge desaparece. Cuando el personaje se aproxima hacia las monedas se sentirán atraídas por el personaje y se dirigen hacia él. 

Acciones
Las acciones que puede realizar un personaje son: Atacar, Comprar, Colocar Torreta y Moverse.

Economía
El personaje empieza con unas monedas iniciales con las que poder comprar algunas defensas. Las monedas aparecerán después de eliminar a un enemigo o finalizar la fase. 

Transición de pantallas

Diagrama de transición de pantallas
-Introducción->-Menú inicial->*Menu de compra*->pantalla oleadas->*->game over/juego completado

Descripción de las pantallas
En el pantalla introducción aparece el logo , nombre del equipo y la universidad.
En el menú inicial aparece el boton de jugar 
El menú de compra tendrá el mapa, el personaje(con sus movimientos) 4 botones (3 para comprar torretas o mejores y 1 para continuar )
En la pantalla de oleadas aparece el mapa, castillo, personaje, enemigos ,torretas y monedas
La pantalla del game over.
La pantalla de finalizar el juego.


Pantallas del Juego

Menús






Opciones del juego: Cuales son y cómo afectan a la mecánica
No habrá opciones como tal, solamente las opciones cuando esté el modo compra.

Rejugar y salvar
La rejugabilidad será viable gracias al respawn de los enemigos, que será diferente en cada ronda y soltarán dinero aleatorio cuando mueran, por lo que el jugador deberá limitarse a las monedas que consiga.
En el juego no se podrá salvar, cuando mueres o eliminas a todos os enemigos se acabará el juego.

Trucos e Easter Eggs

F6 para poder jugar en modo Dios -> Torretas ilimitadas, personaje con vida infinita y ganar 500 monedas al pulsar. No hay Easter Eggs.

5.Historia, Características y Personajes
=======


Historia
Historia de fondo
Nos encontramos en Acho Villa en la Época Medieval. Ha habido una epidemia en los pueblos adyacentes y las personas afectadas se han vuelto salvajes y quieren destruir el resto de los pueblos. El rey de Acho Villa ha mandado al mejor de los caballeros, Avast Call, a combatir esta plaga de seres, dispuesto a imponer su autoridad y tranquilidad en Acho Villa.

Elementos principales
El personaje dispone de una tienda en la que puede comprar objetos defensivos y la posibilidad de enviar su arma a un herrero y forjar un arma más poderosa. A través de la estrategia de posicionar la torre y su habilidad para moverse y atacar, hará frente a las oleadas de enemigos que vienen a destruir Acho Villa.  
 
Progresión del juego
La única forma de progresar en el juego es acabando con las oleadas enemigas.

Escenas de animación
Hay una animación inicial para indicar quién es el creador del videojuego. 

Mundo del juego





Personajes

Avast Call:			

Es el gran caballero de Acho Villa dispuesto a defender el territorio con su propia vida y los objetos defensivos que compra de la villa. Tiene un carácter fuerte, dominante y quiere liberar a su villa de los personajes invasores que no son de la ciudad y quieren destruir su preciado hogar. 
Su escudo rojo representa la ira y la furia que siente al ver que su villa va a ser atacada por gente procedente de otros lugares. Lleva un casco que le cubre el rostro, pero por dentro es un ser de luz.
Cuando adquiere una mejora en el arma, pasa a tener una maza que hace más daño y es más fácil de exterminar a los enemigos.
Al ser el personaje principal, el caballero tiene una gran importancia, ya que si es derrotado acaba la partida y la villa será destruida. 

Vida
500
Fuerza Base
100
Fuerza Mejora Arma
150


Troll:

Era un aldeano más de una villa cercana, pero después de la epidemia, ha sido infectado y lo único que tiene en mente es destruir todo aquello que se encuentre alrededor suya. Está cegado por la epidemia y quiere arrasar el resto de territorios cercanos e instaurarse como la mejor raza que de este territorio.
Al sufrir la epidemia, cambia de forma física, quedando en un estado lamentable, con la ropa desollada y adquiriendo un hacha poderosa con la que llevar su objetivo a cabo. 
Después de derrotarlos en la primera oleada, los enemigos se vuelven más furiosos y van más rápido a por los objetivos.
Es el principal enemigo del juego al que nuestro caballero deberá derrotar.

Vida
500
Objetivo
Torretas y luego jugador
Daño
100



Murciélago:

Vida
50
Objetivo
Jugador
Daño Jugador
25
Velocidad 
rápida



Purple Pumpkin


Vida
500
Daño Castillo
100
Objetivo
Castillo


6.Niveles
=====

Nivel 1

Resumen :
Aparecen 1 tipo de enemigo que va primero a por las torres y si las mata va a por el personaje 
Material de introducción: animación…:
 El personaje tiene animación de moverse y atacar. Las torres tienen su animación de disparar y el enemigo tiene la animación de moverse y atacar

Objetivos: 
Matar a todos los enemigos de la ronda ayudándote de las torretas y conseguir el mayor número de monedas.

Descripción física:

Mapa
Caminos

Encuentros: 
Emboscadas: Los enemigos ralentizan al jugador por lo que si el jugador se expone mucho será encerrado y no podrá salir:

Guía del nivel: 
Construir torretas al iniciar el nivel, atacar a los enemigos sin acercarte demasiado para que no rompan las torretas.

Material de cierre: 
Game over.
Nivel 2

Resumen :
Tienen que derrotar a los enemigos igual que en el nivel 1 pero esta vez los enemigos aparecen más rápido.
Material de introducción: animación…: 
El personaje tiene animación de moverse y atacar. Las torres tienen su animación de disparar y el enemigo tiene la animación de moverse y atacar

Objetivos: 
Matar a todos los enemigos de la ronda ayudándote de las torretas y mejoras  conseguir el mayor número de monedas.

Descripción física:

Mapa
Caminos

Encuentros: 
Emboscadas: Los enemigos ralentizan al jugador por lo que si el jugador se expone mucho será encerrado y no podrá salir:

Guía del nivel: 
Construir más torretas y mejorar el arma para derrotar a los enemigos sin acercarte demasiado e intentar que  no rompan las torretas.

Material de cierre: 
Game over.


7.Inteligencia Artificial
=====
IA del Oponente(que lucha ahora mismo contra el protagonista)
Antes del comienzo de la oleada se generará un número aleatorio, este valor determinará la forma de actuar de los enemigos durante esa ronda, pueden ser más agresivos y atacar constantemente al jugador o a la base ignorando las torretas o centrarse en estas. De este modo en cada ronda actuarán de forma distinta ofreciendo al jugador el desafío de adaptarse a cada una de las posibles situaciones.








IA de los amigos
Serán las torretas que compre en el modo compra. Existen dos tipos de torreta, Una torreta marrón simple que disparará al enemigo más cercano con un proyectil que seguirá una trayectoria recta y otra torreta superior, que disparará más lento pero hará el doble de daño a los enemigos.



