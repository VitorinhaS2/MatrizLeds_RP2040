# Atividade Prática — RP2040 — Geração de Animações em Matriz de LEDs 5x5

## Objetivo
Desenvolver duas animações interativas em uma matriz de LEDs 5x5 (WS2812), controladas via botões A e B da placa BitDogLab, utilizando o microcontrolador Raspberry Pi Pico W e o simulador Wokwi. Implementar debounce por software nos botões e, opcionalmente, emitir som com buzzer.

---

## Descrição das Animações

### 1️⃣ Animação 1 — Desenho Estático
Animação representando um coração, que se forma gradualmente, acionada pelo botão **A** (GPIO 6).

### 2️⃣ Animação 2 — Fogo de Artifício
Animação em 5 frames representando uma explosão de luz que se expande do centro para as bordas, com fade gradual para criar o efeito de dissipação, acionada pelo botão **B** (GPIO 5).


---

## Especificações Técnicas
- Microcontrolador: Raspberry Pi Pico W
- Matriz de LEDs: 5x5 WS2812
- Botões: GPIO 5 (B) e GPIO 6 (A)
- Linguagem: C
- Ambiente: VS Code + Pico SDK + simulador Wokwi
- Debounce por software implementado
- Código modular com função `desenho_pio` para exibição de frames

---

## Como Executar
1. Clone este repositório:
    ```bash
    git clone https://github.com/VitorinhaS2/MatrizLeds_RP2040.git
    cd MatrizLeds_RP2040
    ```

2. Compile o projeto com o **Pico SDK**.
3. Execute a simulação no **Wokwi** ou grave o firmware no Raspberry Pi Pico W.
4. Pressione o botão **A** para executar a animação do coração.
5. Pressione o botão **B** para executar a animação do fogo de artifício.

---

## Organização da Equipe
- **Líder de Projeto:** [VITÓRIA CAVALCANTI] — responsável pelo gerenciamento do repositório e revisão dos pull requests.
- **Desenvolvedor 1:** [LÁISA BIANCA] — responsável pela animação Coração.
- **Desenvolvedor 2:** [LAÍSE CAFÉ] — responsável pela animação Fogo de Artifício.

---

## Demonstração em Vídeo
Assista ao vídeo demonstrando o funcionamento das animações:

 [Link para o vídeo]()

---

## Conclusão
A atividade foi concluída com sucesso, implementando as animações propostas, debounce por software, e integração completa com a matriz de LEDs WS2812. O código está versionado no GitHub, e o vídeo de apresentação demonstra o resultado final.

---

## Contribuições
Pull requests são bem-vindos! Por favor, envie sugestões ou melhorias.

---

## Licença
Este projeto é destinado exclusivamente para fins acadêmicos na disciplina **ELET0021 — Microcontroladores e Microprocessadores**.

---

