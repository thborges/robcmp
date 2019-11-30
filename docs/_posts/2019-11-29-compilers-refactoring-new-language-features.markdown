---
layout: post
title:  "Compiladores 2019: Refatoração e Novos Recursos na Linguagem"
date:   2019-12-01 18:44:14 -0200
categories: teaching research
---

Em 2019, durante a disciplina de Compiladores/2019-1, foi escrito um compilador em C, desta vez separando a geração de código da análise semântica. Através de um padrão visitor simplificado, a árvore sintática ou AST foi percorrida, simplificada e validada (parcialmente). A integração com o LLVM foi aprimorada e recursos de otimização foram adicionados, como -O1, -O2, -Os e -Oz. o código final do projeto pode ser visto no repositório [Cmp2019](https://github.com/thborges/cmp2019). Parte destas funcionalidades estão sendo migradas para o projeto Robcmp.

No projeto Robcmp, o aluno Vítor Almeida Subhi [@vitorsubhi](https://github.com/vitorsubhi), durante o desenvolvimento de seu projeto de final de curso (PFC), fez uma profunda remodelagem da estrutura do código, iniciando a separação de validação semântica da geração de código. Acrescentou também recursos à linguagem como funções com parâmetros, vetores e matrizes alocados em pilha. O resultado de seu trabalho pode ser visto no branch [robcmp-vitorsubhi](https://github.com/thborges/robcmp/tree/vitorsubhi). O texto final do PRC pode ser obtido em [Monografia Vitor Subhi]() (Será disponibilizado após a defesa, em Dezembro/2019).

{% include disqus.html %}

