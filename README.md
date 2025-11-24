

# 🎮 **Lógica, Lógica e Mais Lógica**

Jogo em **C**, rodando no terminal Linux (incluindo WSL), criado para estimular **raciocínio lógico**, **pensamento computacional** e **resolução de problemas**.
Utiliza a biblioteca personalizada **`cli-lib`** para renderização no terminal, animações, teclado não bloqueante e interface ASCII.

---

## 📌 **Sobre o Projeto**

**Lógica, Lógica e Mais Lógica** é um jogo textual que combina exploração, narrativa e desafios de lógica.
O jogador progride resolvendo:

* charadas,
* perguntas de lógica,
* enigmas,
* batalhas estratégicas,
* interações com itens e feitiços.

A proposta é transformar conceitos de lógica em uma dinâmica divertida e envolvente.

---

## ⭐ **Características do Jogo**

* Desenvolvido em **C puro**
* Usa a biblioteca **cli-lib** (tela, teclado, animação, cores)
* **Makefile** para build automatizado
* Arquivo **`ranking.txt`** para pontuações persistentes
* Mapas interativos e narrativas diferentes
* Questões aleatórias e desafios lógicos
* Interface colorida via ANSI
* Estrutura modular (arquivos .c e .h separados)

---

## 🧠 **Arquitetura do Código**

O código é organizado em módulos independentes, cada um responsável por uma parte do jogo.

### 📁 Estrutura Geral

```
cli-lib/
│
├── include/       # Headers (.h)
│   historia.h  jogador.h  keyboard.h
│   mapa.h      menu.h     questoes.h
│   ranking.h   screen.h   timer.h
│
├── src/           # Código-fonte (.c)
│   historia.c  jogador.c  keyboard.c
│   mapa.c      menu.c     questoes.c
│   ranking.c   screen.c   timer.c
│   main.c
│
├── ranking.txt    # Registro de pontuação
├── Makefile       # Compilação automatizada
└── README.md
```

### 🧩 Principais Módulos

* **historia.c** – introdução, narrativas e finalização
* **jogador.c** – status, inventário e feitiços
* **keyboard.c** – captura de teclado em tempo real
* **mapa.c** – carregamento e renderização dos mapas
* **questoes.c** – banco de perguntas e enigmas
* **ranking.c** – leitura e gravação do ranking (`ranking.txt`)
* **screen.c** – controle do cursor, cores e desenho da interface
* **timer.c** – delays e temporização
* **main.c** – loop principal, combate e fluxo do jogo

---

## 🎯 **Como Jogar**

### ▶️ Compilar

### ▶️ Executar

### 🎮 Controles

| Tecla              | Função     |
| ------------------ | ---------- |
| **W / A / S / D**  | Movimentar |
| **Enter / Espaço** | Interagir  |
| **ESC**            | Sair       |

### 🎯 Objetivo

* Explorar mapas
* Resolver desafios lógicos
* Coletar itens e feitiços
* Enfrentar inimigos
* Finalizar a aventura
* Registrar seu score no **ranking.txt**

---

## 👥 **Equipe**

* **Aline de Albuquerque Henriques** — @aline-henriques
* **Eduardo Borges** — @Eduardo-Borges18
* **Gabriel Leal** — @Lealgbm
* **Luiz Rocha** — @Luizrocha0
* **Ricardo Severiano de Souza Filho** — @byteric
* **Sérgio Chousinho** — @sergiochou

---

## © **Licença MIT**

Software distribuído sob a Licença MIT.
© Todos os direitos reservados aos autores.
