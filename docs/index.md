Veja nesta página os projetos desenvolvidos na disciplina Compiladores, na Universidade Federal de Jataí (UFG - Regional Jataí), usando alguns conceitos de Robótica Educacional para estimular os alunos nesta que é uma disciplina complexa e fortemente teórica.

Usando o código no github associado a esta página (github.com/robcmp), os alunos desenvolvem um frontend de linguagem de programação, usando ferramentas como flex e yacc. A linguagem de programação é desenvolvida pelo aluno com o propósito de executar os programas num processador AVR (placa Arduino). Devido ao curto prazo (1 semestre), o backend para AVR da suíte LLVM é integrado ao frontend desenvolvido pelo aluno.

Veja alguns vídeos dos projetos finais apresentados pelos alunos. A linguagem criada pode ser vista nos arquivos deste repositório e nos forks do projeto.

# Compiladores 2019
Em 2019, durante a disciplina de Compiladores/2019-1, foi escrito um compilador em C, desta vez separando a geração de código da análise semântica. Através de um padrão visitor simplificado, a árvore sintática ou AST foi percorrida, simplificada e validada (parcialmente). A integração com o LLVM foi aprimorada e recursos de otimização foram adicionados, como -O1, -O2, -Os e -Oz. o código final do projeto pode ser visto no repositório [Cmp2019](https://github.com/thborges/cmp2019). Parte destas funcionalidades estão sendo migradas para o projeto Robcmp.

No projeto Robcmp, o aluno Vítor Almeida Subhi [@vitorsubhi](https://github.com/vitorsubhi), durante o desenvolvimento de seu projeto de final de curso (PFC), fez uma profunda remodelagem da estrutura do código, iniciando a separação de validação semântica da geração de código. Acrescentou também recursos à linguagem como funções com parâmetros, vetores e matrizes alocados em pilha. O resultado de seu trabalho pode ser visto no branch [robcmp-vitorsubhi](https://github.com/thborges/robcmp/tree/vitorsubhi). O texto final do PRC pode ser obtido em [Monografia Vitor Subhi]() (Será disponibilizado após a defesa, em Dezembro/2019).

# Compiladores 2018

No projeto Robcmp, o aluno Danilo Martins Rodrigues [@bccdanilo](https://github.com/bccdanilo), durante o desenvolvimento de seu projeto de final de curso (PFC), acrescentou recursos de orientação à eventos na linguagem, suportando eventos acionados com base em relógios do AVR e também em interrupções de borda em portas lógicas. A implementação foi realizada através da modificação dos parsers léxico e sintático. A biblioteca [TimerOne](https://www.arduinolibraries.info/libraries/timer-one), em C, foi empregada para prover a funcionalidade de eventos baseados em relógio. O código implementado em seu trabalho pode ser visto no branch [robcmp-danilo](https://github.com/thborges/robcmp/tree/pfc_danilo). O texto final do PFC pode ser obtido em [Monografia Danilo Martins](https://github.com/thborges/robcmp/raw/pfc_danilo/docs/pfc2%20danilo%20banca_.pdf).

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

# Compiladores 2017
No ano de 2017, devido à complexida do projeto, os alunos não tiveram tempo de usar o hardware disponibilizado (máquina plotter) e as apresentações não foram filmadas. No entanto, o código foi testado em um simulador G-Code. O código e os slides das apresentações estão disponíveis para referência no código deste projeto no [Github](https://github.com/thborges/robcmp/tree/master/2017).

Algumas imagens do resultado final dos projetos no simulador:

![Código de Calculadora de Números Romanos e resposta usando G-Code](https://raw.githubusercontent.com/thborges/robcmp/master/2017/Guilherme/exemplo.jpg)

![Código e Desenho de um Robô usando G-Code](https://raw.githubusercontent.com/thborges/robcmp/master/2017/Roberto/exemplo.jpg)


# Compiladores 2016
[![Video 1 2016](https://img.youtube.com/vi/a5fkYkQ6bhI/0.jpg)](https://www.youtube.com/watch?v=a5fkYkQ6bhI)
[![Video 2 2016](https://img.youtube.com/vi/ahtgTIoUnZ0/0.jpg)](https://www.youtube.com/watch?v=ahtgTIoUnZ0)

# Compiladores 2015
[![Video 1 2015](https://img.youtube.com/vi/N4Rxfpfs7k0/0.jpg)](https://www.youtube.com/watch?v=N4Rxfpfs7k0)
[![Video 2 2015](https://img.youtube.com/vi/YoPKFKp7MBE/0.jpg)](https://www.youtube.com/watch?v=YoPKFKp7MBE)
[![Video 3 2015](https://img.youtube.com/vi/PuXYiVzmQs4/0.jpg)](https://www.youtube.com/watch?v=PuXYiVzmQs4)


# Espaço das Profissões na UFG/UFJ e em outras instituições

Alguns vídeos do projeto de Robótica Educacional, ferramentas para auxiliar na construção de robôs e os próprios robôs que estão sendo desenvolvidos:

[![Video RE 4](https://img.youtube.com/vi/WiL6HWBrZoA/0.jpg)](https://www.youtube.com/watch?v=WiL6HWBrZoA)
[![Video RE 3](https://img.youtube.com/vi/-Id48-MvaR4/0.jpg)](https://www.youtube.com/watch?v=-Id48-MvaR4)
[![Video RE 2](https://img.youtube.com/vi/-zfRB2uEZyY/0.jpg)](https://www.youtube.com/watch?v=-zfRB2uEZyY)
[![Video RE 1](https://img.youtube.com/vi/g4sYlFEB-1E/0.jpg)](https://www.youtube.com/watch?v=g4sYlFEB-1E)


# Tutorial da construção de frontend usando Robcmp

[![Video Tutorial Robcmp 1](https://img.youtube.com/vi/0sjMMcToySM/0.jpg)](https://www.youtube.com/watch?v=0sjMMcToySM)
[![Video Tutorial Robcmp 2](https://img.youtube.com/vi/tcHpQz9_d8g/0.jpg)](https://www.youtube.com/watch?v=tcHpQz9_d8g)

