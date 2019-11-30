---
layout: post
title:  "Compiladores 2018: Linguagem Orientada a Eventos para Robótica Educacional"
date:   2018-12-01 18:44:14 -0200
categories: Research 
---

Atualização do projeto no ano de 2018: orientação a eventos com interrupções de tempo e em portas lógicas.

Durante o ano de 2018, o aluno Danilo Martins Rodrigues [@bccdanilo](https://github.com/bccdanilo), no desenvolvimento de seu projeto de final de curso (PFC), acrescentou recursos de orientação à eventos na linguagem, suportando eventos acionados com base em relógios do AVR e também em interrupções de borda em portas lógicas. A implementação foi realizada através da modificação dos parsers léxico e sintático. A biblioteca [TimerOne](https://www.arduinolibraries.info/libraries/timer-one), em C, foi empregada para prover a funcionalidade de eventos baseados em relógio. O código implementado em seu trabalho pode ser visto no branch [robcmp-danilo](https://github.com/thborges/robcmp/tree/pfc_danilo). O texto final do PFC pode ser obtido em [Monografia Danilo Martins](https://github.com/thborges/robcmp/raw/pfc_danilo/docs/pfc2%20danilo%20banca_.pdf).

Exemplo de código com eventos:
```
x = 0;
quando porta1 esta crescendo {
	//evento acionado quando porta 1 cresce (RISING)
    x = (1-x);
}
a cada 0.5 segundos {
	//evento acionado a cada 500ms
}
// pisca led no loop principal
enquanto(1>0) {
	saida13 = 255;
	espera(500);
	saida13 = 0;
	espera(500);
}
```

{% include disqus.html %}

