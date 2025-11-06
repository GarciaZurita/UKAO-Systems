# UKAO-Systems
Codigo Arduino

El proyecto consiste en el diseño, prototipado y validación de una pulsera de triage inteligente que funcione como un nodo de información médica crítica portátil

Descripción del proceso de pruebas I/O y depuración en vivo 

Durante esta etapa del proyecto se realizó un proceso de debug intensivo 
sobre el sistema de triage médico desarrollado con Arduino UNO, con el 
objetivo de verificar la correcta operación de las entradas y salidas (I/O), 
además de depurar los errores que afectaban el funcionamiento del circuito y 
del código. 

El sistema implementa un sensor de pulso simulado con potenciómetro, una 
pantalla LCD I2C 20x4, cuatro LEDs indicadores (verde, amarillo, rojo y azul) y 
un buzzer piezoeléctrico, los cuales permiten mostrar de manera visual y 
auditiva el estado de salud del paciente según su frecuencia cardíaca. 

Durante las pruebas se empleó el Monitor Serial del IDE de Arduino para 
realizar seguimiento en tiempo real de los valores de pulso leídos, verificar la 
ejecución correcta de los condicionales y comprobar que los mensajes 
enviados por el microcontrolador coincidieran con los valores mostrados en la 
pantalla LCD. 

También se aplicaron pruebas de voltaje y continuidad para garantizar la 
correcta alimentación de cada componente y descartar fallos de conexión. 

Sketch (.ino) comentado y funciones principales: 

El código final fue documentado línea por línea para facilitar su comprensión y 
futuras modificaciones. Entre sus principales funciones se encuentran: 

1. Lectura de entrada analógica (A0): el valor proveniente del 
potenciómetro se convierte mediante la función map() a un rango de 20 
a 130 bpm, simulando un sensor de pulso real.

2. Procesamiento de datos: con base en los valores obtenidos, el sistema 
clasifica el estado del paciente en cuatro niveles: 

 o Estable (verde): pulso entre 60 y 80 bpm. 
 
 o Riesgo (amarillo): pulso ligeramente fuera del rango normal. 
 
 o Crítico (rojo): pulso alto o bajo que requiere atención inmediata. 
 
 o Muerto (azul): pulso extremadamente alto o bajo, indicando paro. 
 
3. Salida visual: la pantalla LCD muestra continuamente el pulso, estado y 
datos del paciente (nombre, edad, tipo de sangre, alergias y ubicación 
GPS). 

4. Salida auditiva: el buzzer emite tonos de diferente frecuencia según el 
nivel de riesgo detectado. 

5. Comunicación serial: todos los datos se envían también al monitor serial 
para diagnóstico y registro de pruebas. 
Cada sección del código fue probada individualmente, documentando su 
comportamiento en el log de depuración. 

Pruebas de entrada/salida (I/O): 

Se realizaron múltiples pruebas de funcionamiento tanto en software como en 
hardware: 

Prueba 1: Alimentación y continuidad 

 • Se verificó que la línea de 5V alimentara correctamente la breadboard. 
 
 • Se midió con multímetro la continuidad entre GND del Arduino y la línea negativa de la protoboard. 

 • Resultado: 5.01 V estables; sin pérdida de tensión. 
 
Prueba 2: Lectura analógica del sensor de pulso 

 • Se conectó el potenciómetro en A0 y se imprimieron los valores por monitor serial. 

 • Resultado: el rango de lectura fue de 0 a 1023, confirmando una conversión analógica correcta. 

Prueba 3: Comunicación I2C de la pantalla LCD 

 • Se usó un escáner I2C para encontrar la dirección del módulo (0x26). 
 
 • Resultado: LCD reconocida correctamente y operativa tras ajustar la dirección en el código. 

Prueba 4: Salidas digitales 

 • Cada LED fue probado individualmente con un sketch simple para verificar polaridad y resistencias. 
 
 • El buzzer respondió correctamente a tonos de 700 Hz, 1000 Hz y 2000 Hz. 
 
Prueba 5: Ejecución del sketch completo 

 • Se observó en el monitor serial y en el LCD el comportamiento del sistema al girar el potenciómetro. 
 
 • Resultado: el estado cambiaba automáticamente según el valor del pulso simulado. 
 
  o Entre 60–80 → LED verde encendido, buzzer apagado.
  
  o Menor a 40 o mayor a 100 → LED rojo y tono de alerta. 
  
  o Menor a 30 o mayor a 120 → LED azul y tono continuo indicando paro. 

Registro de depuración (Debug Log):
<img width="643" height="494" alt="image" src="https://github.com/user-attachments/assets/e5fccd98-1949-4971-b3dd-81123c8a7472" />


Conclusiones:

El proceso de depuración intensiva permitió garantizar la estabilidad y 
funcionalidad completa del sistema de triage, asegurando que tanto el 
hardware como el software trabajen de manera sincronizada.

Gracias a las pruebas I/O, el uso del monitor serial y la corrección de errores en 
tiempo real, se logró que el sistema identifique de forma confiable el estado del 
paciente y active las señales visuales y auditivas correspondientes.

Además, el código quedó totalmente documentado, con comentarios 
explicativos y preparado para ser publicado en GitHub, junto con el registro de 
depuración (DEBUG_LOG.md) y la evidencia fotográfica del circuito final. 
Esta fase fortaleció las habilidades de análisis, detección de fallos y corrección 
de errores en entornos de desarrollo embebido, aportando al aprendizaje 
práctico del control de sistemas electrónicos mediante Arduino.
