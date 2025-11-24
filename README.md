# 🎮 | Lógica, Lógica e Mais Lógica

Jogo em **C**, executado no terminal Linux (incluindo WSL), desenvolvido para reforçar habilidades de **raciocínio lógico**, **pensamento computacional** e **resolução de problemas**.

O jogo utiliza a **biblioteca personalizada `cli-lib`**, que fornece ferramentas avançadas para manipulação do terminal, renderização de mapas, leitura não bloqueante de teclado, animações e interface ASCII.

---

## Sobre o Projeto

**Lógica, Lógica e Mais Lógica** é um jogo acadêmico desenvolvido em linguagem **C**, utilizando a biblioteca `cli-lib`, que permite criar experiências de jogo diretamente no terminal Linux.
O objetivo é incentivar o pensamento estruturado por meio de uma jogabilidade leve, divertida e totalmente textual.

Ele combina exploração de mapas, narrativa interativa e desafios lógicos, incluindo:

* perguntas de lógica,
* charadas,
* enigmas,
* batalhas baseadas em raciocínio,
* coleta de itens e feitiços.

---

## Características do Jogo

* Criado em **C puro**
* Usa a biblioteca **cli-lib** (renderização, teclado, animações, cursor, cores)
* Possui **Makefile** para build automatizado
* Utiliza arquivo **ranking.txt** para pontuações persistentes
* Mapas interativos com múltiplas fases
* Questões aleatórias e desafios lógicos
* Controles em tempo real via teclado
* Cores e elementos gráficos via ANSI
* Arquitetura modular (cada módulo em seu arquivo .c e .h)
* Execução leve e rápida em qualquer terminal Linux/WSL

---

## Arquitetura do Código

O projeto está organizado em módulos, cada um responsável por uma parte específica da lógica do jogo.

### Estrutura Geral do Projeto

```
cli-lib/
│
├── include/            # Arquivos .h (interfaces públicas)
│   ├── historia.h
│   ├── jogador.h
│   ├── keyboard.h
│   ├── mapa.h
│   ├── menu.h
│   ├── questoes.h
│   ├── ranking.h
│   ├── screen.h
│   └── timer.h
│
├── src/                # Implementações .c
│   ├── historia.c
│   ├── jogador.c
│   ├── keyboard.c
│   ├── mapa.c
│   ├── menu.c
│   ├── questoes.c
│   ├── ranking.c
│   ├── screen.c
│   ├── timer.c
│   └── main.c
│
├── ranking.txt         # Arquivo persistente de pontuações
├── Makefile            # Automação de build (gera obj/ e build/)
└── README.md
```

---

### Descrição dos Principais Módulos

#### **historia.c / historia.h**

* Introdução animada
* Narrativas e cutscenes
* Finalização do jogo

#### **jogador.c / jogador.h**

* Status, inventário e feitiços
* Funções de uso de itens
* Progressão e atributos

#### **keyboard.c / keyboard.h**

* Input não bloqueante
* Modo raw do terminal
* Captura de teclas especiais

#### **mapa.c / mapa.h**

* Carregamento das fases
* Renderização estruturada
* Lógica de colisão e movimento

#### **questoes.c / questoes.h**

* Banco de perguntas
* Seleção aleatória
* Questões da vila, batalha e baús

#### **ranking.c / ranking.h**

* Leitura e escrita do ranking
* Ordenação
* Exibição no terminal

> **O arquivo `ranking.txt` é usado para armazenar as pontuações dos jogadores**, sendo atualizado automaticamente a cada partida.

#### **screen.c / screen.h** (parte central do cli-lib)

* Controle do cursor
* Animações
* Desenho de quadros
* Atualização de tela

#### **timer.c / timer.h**

* Simulação de delays e tempo de jogo

#### **main.c**

* Loop principal
* Interações gerais
* Combate lógico
* Transição de fases

---

## 🎯 | Como Jogar?

---

### Controles

| Tecla              | Ação         |
| ------------------ | ------------ |
| **W / A / S / D**  | Movimentação |
| **Enter / Espaço** | Interagir    |
| **ESC**            | Sair         |

---

### Objetivo do Jogo

* Explorar mapas temáticos
* Resolver questões de lógica
* Superar desafios interativos
* Coletar itens e feitiços
* Enfrentar o mestre final
* Registrar sua pontuação no arquivo **ranking.txt**

---

## 👥 | Equipe

* **Aline de Albuquerque Henriques** — @aline-henriques
* **Eduardo Borges** — @Eduardo-Borges18
* **Gabriel Leal** — @Lealgbm
* **Luiz Rocha** — @Luizrocha0
* **Ricardo Severiano de Souza Filho** — @byteric
* **Sérgio Chousinho** — @sergiochou

---

## ©️ | Licença MIT

Software distribuído sob a licença MIT.
© Todos os direitos reservados aos autores.
