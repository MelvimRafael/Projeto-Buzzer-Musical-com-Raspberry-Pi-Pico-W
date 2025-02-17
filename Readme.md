# Projeto Buzzer Musical com Raspberry Pi Pico W

Este projeto utiliza o Raspberry Pi Pico W para gerar sons usando um buzzer piezoelétrico. O código é capaz de reproduzir diferentes músicas e notas, controlando o buzzer por meio de PWM (Pulse Width Modulation). Além disso, o sistema pode ser controlado por dois botões, cada um responsável por acionar uma música diferente.

## Funcionalidades

- **Notas Musicais**: O buzzer pode tocar uma escala musical de Dó (C) e a música "Parabéns Pra Você" ao pressionar os botões.
- **Controle por Botões**: Dois botões são usados para controlar as músicas. O primeiro botão toca a escala musical e o segundo toca a música "Parabéns Pra Você".
- **PWM para Controle de Frequência**: Utilização de PWM para gerar frequências de áudio para o buzzer.
- **Debounce de Botões**: Implementação de uma lógica de debounce para evitar múltiplos acionamentos acidentais dos botões.

## Vídeo de Demonstração

Veja o vídeo de demonstração do funcionamento do projeto:

[Assista ao vídeo de demonstração](https://drive.google.com/file/d/1Gdhz9KTUOZOjS2CGxOHW8Xjpa__dr20i/view?usp=share_link)


## Componentes Utilizados

- **Raspberry Pi Pico W**: Microcontrolador para controlar o buzzer e os botões.
- **Buzzer Piezoelétrico**: Componente responsável por emitir os sons.
- **Botões**: Usados para disparar as músicas.
- **Bibliotecas**:
  - `pico/stdlib.h`: Biblioteca padrão para o Raspberry Pi Pico.
  - `hardware/pwm.h`: Biblioteca para controle de PWM.
  - `hardware/clocks.h`: Biblioteca para controle de clock.

## Funcionalidade de Músicas

1. **Escala Musical de Dó (C)**: O buzzer toca as notas da escala de Dó (C) com durações definidas.
2. **Parabéns Pra Você**: O buzzer toca a melodia de "Parabéns Pra Você" quando o segundo botão é pressionado.

## Diagrama de Circuito

O circuito é simples, consistindo em:

- **Buzzer**: Conectado ao pino 21 do Raspberry Pi Pico W.
- **Botão A**: Conectado ao pino 5 do Raspberry Pi Pico W.
- **Botão B**: Conectado ao pino 6 do Raspberry Pi Pico W.

O botão é configurado com um resistor de pull-up interno, o que significa que ele será lido como `0` quando pressionado.


### Inicialização do Buzzer

A função `pwm_init_buzzer(uint pin)` configura o buzzer para funcionar com PWM. O valor de `clkdiv` é ajustado para controlar a velocidade do PWM.

### Reproduzindo uma Nota

A função `play_tone(uint pin, uint frequency, uint duration_ms)` recebe a frequência e a duração de uma nota musical e a reproduz no buzzer. A função limita a frequência entre 262 Hz (Dó) e 880 Hz (Lá), que são as frequências das notas do C4 ao A5.

### Reproduzindo Música

A função `play_music(const uint *notes, const uint *durations, int length)` percorre os arrays de notas e durações, chamando a função `play_tone` para reproduzir cada nota.

### Controle de Botões

Os botões A e B são lidos a cada ciclo do loop principal. Quando o botão A é pressionado, o código reproduz a escala de notas. Quando o botão B é pressionado, o código toca a música "Parabéns Pra Você". Ambos os botões têm um delay de 200ms para evitar múltiplos acionamentos acidentais (debounce).

## Como Usar

1. **Conecte o Raspberry Pi Pico W ao computador**.
2. **Conecte o buzzer** ao pino 21 do Raspberry Pi Pico W.
3. **Conecte os botões** aos pinos 5 e 6 do Raspberry Pi Pico W.
4. **Carregue o código** no Raspberry Pi Pico W usando um ambiente de desenvolvimento como o VS Code.
5. **Pressione os botões** para reproduzir a escala ou a música "Parabéns Pra Você".

## Possíveis Melhorias

- **Adicionar mais músicas**: Você pode adicionar outras músicas ou até mesmo melodias personalizadas, modificando os arrays de notas e durações.
- **Aprimorar a interface**: É possível adicionar mais botões ou uma tela LCD para controlar o tipo de música a ser tocada.
- **Melhorar a qualidade do som**: Usar um amplificador para aumentar o volume do som emitido pelo buzzer.

## Licença

Este projeto está licenciado sob a [MIT License](LICENSE).
