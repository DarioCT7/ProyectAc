# Guion para Exposición de 5 Minutos: Space Invaders EPN

## Introducción  
**[0:00 - 0:30]**  
(30 segundos)  
"Buenos días/tardes a todos. Mi nombre es [tu nombre], y hoy les presentaré *Space Invaders EPN*, un juego desarrollado en C++ con SFML, inspirado en el clásico arcade *Space Invaders*. Este proyecto, disponible en `git@github.com:Nicolax-b/SpaceInvaders.git`, incluye un menú, mecánicas de juego como el jugador y enemigos, y pantallas de victoria y derrota. En los próximos 5 minutos, les explicaré su arquitectura, cómo se estructura, cómo compilarlo, sus mecánicas, y posibles mejoras. ¡Comencemos!"  
*(Pausa breve de 5 segundos para transición)*  

## Desarrollo: Arquitectura y Estructura  
**[0:30 - 2:00]**  
(1 minuto 30 segundos)  
"El juego usa una arquitectura orientada a objetos con clases como `Player` para la nave, `Enemie` para los enemigos en una matriz 7x12, y `Bullet` para las balas. La lógica principal está en `main2.cpp`, que maneja el flujo con SFML para gráficos, audio y controles. [Pausa de 5 segundos] La estructura incluye carpetas: `src` con el código, `textures` con `spritesheetnuevo.png` y `spritesheet.png`, `sounds` con efectos como `Bala.wav`, y `Music` con pistas como `menu.ogg`. Depende de SFML y la librería estándar de C++. Para compilarlo, clona el repositorio y usa `g++` con las banderas adecuadas, asegurando que los recursos estén en las rutas correctas. Se ejecuta en pantalla completa a 60 FPS. [Pausa de 5 segundos]"  

## Desarrollo: Mecánicas y Detalles Técnicos  
**[2:00 - 3:30]**  
(1 minuto 30 segundos)  
"Los controles son intuitivos: usa flechas o joystick para moverte, espacio o botón A para disparar, y Enter o botón A para seleccionar en menús. El jugador tiene 3 vidas, se mueve horizontalmente y dispara balas a -15 de velocidad. Los enemigos se mueven lateralmente, disparan a +15, y su cadencia aumenta al eliminarlos. Muros protegen, degradándose con impactos. Ganas eliminando todos los enemigos, o pierdes si te quedas sin vidas o un enemigo llega al 90% de la pantalla. [Pausa de 5 segundos] Técnicamente, usa un spritesheet escalado, colisiones con `sf::IntRect`, y audio inmersivo con música y efectos. La resolución se adapta dinámicamente. [Pausa de 5 segundos]"  

## Desarrollo: Problemas y Mejoras  
**[3:30 - 4:30]**  
(1 minuto)  
"Hay problemas conocidos: en `main2.cpp`, un bucle anidado usa el mismo índice, causando posibles errores, y `srand` se llama repetidamente, afectando la aleatoriedad. Sugiero mejoras como un `CMakeLists.txt` para facilitar la compilación, una pantalla de pausa, niveles de dificultad, y optimización de colisiones con un quadtree. [Pausa de 5 segundos] Estas mejoras harían el juego más robusto y escalable."  

## Conclusión  
**[4:30 - 5:00]**  
(30 segundos)  
"En conclusión, *Space Invaders EPN* es una implementación sólida del clásico arcade, con potencial para crecer. Este manual es una guía para entenderlo y modificarlo. Gracias por su atención. ¿Alguna pregunta?"  
*(Pausa final de 5 segundos para preguntas)*  

## Notas para la Presentación
- **Tiempo Total**: ~5 minutos con pausas incluidas.
- **Diapositivas Sugeridas**:
  1. Título e introducción.
  2. Diagrama de arquitectura (clases y flujo).
  3. Estructura de carpetas y recursos.
  4. Mecánicas y controles (lista o gráfico).
  5. Problemas y mejoras (lista).
  6. Conclusión y contacto.
- **Práctica**: Ensaya para ajustar el ritmo. Si necesitas más detalles, puedo expandir secciones.