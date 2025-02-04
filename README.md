# 🚦 Projeto: Controle de Temporizadores no Raspberry Pi Pico W  

## 📌 Descrição  
Este projeto implementa dois sistemas distintos utilizando o **Raspberry Pi Pico W**:  
1. **Semáforo com temporizador periódico**: Alterna automaticamente entre as cores vermelha, amarela e verde a cada 3 segundos.  
2. **Acionamento de LEDs com temporizador de um disparo (One Shot)**: Os LEDs acendem em sequência após o pressionamento de um botão.  

Ambos os sistemas utilizam as funções **add_repeating_timer_ms()** e **add_alarm_in_ms()** do **Pico SDK** para controle de temporização.  

## 👤 Desenvolvedor  
- Mariana Farias da Silva  

## 🛠 Tecnologias Utilizadas  
- 🔹 **Linguagem C** com **Pico SDK**  
- 🔹 **Ambiente de Desenvolvimento VS Code**  
- 🔹 **Simulador Wokwi** para testes  
- 🔹 **Git e GitHub** para versionamento  

## 🎯 Funcionalidades  

### ✅ Atividade 1: Semáforo com Temporizador Periódico  
🔴 **Inicia no vermelho**, alternando para amarelo e depois para verde.  
⏳ **Troca de estado a cada 3 segundos** usando a função `add_repeating_timer_ms()`.  
💻 **Exibe mensagens na serial** a cada segundo.  
🛠 **Utiliza três LEDs (vermelho, amarelo e verde) e resistores de 330Ω**.    

### ✅ Atividade 2: Temporizador de Um Disparo (One Shot)  
🔘 **Os LEDs são acionados pelo pressionamento de um botão (pushbutton)**.  
🌟 **Os LEDs acendem progressivamente e apagam em sequência** após 3 segundos entre cada estágio.  
⏳ **Utiliza a função `add_alarm_in_ms()` para temporização**.  
🔄 **O botão só pode ser pressionado novamente após a última etapa**.   

## 📜 Requisitos do Projeto  
1️⃣ **Ambiente de desenvolvimento VS Code** configurado com **Pico SDK**.  
2️⃣ **Código em C**, utilizando os recursos de temporização do Raspberry Pi Pico.  
3️⃣ **Simulação no Wokwi** para validação das funções.  
4️⃣ **Criação de repositório no GitHub** para controle de versão.  
5️⃣ **Implementação de testes básicos** para garantir funcionamento correto.  
6️⃣ **Arquivo README.md** com instruções detalhadas do projeto.  

## 📥 Instalação e Configuração  
1. Clone o repositório:  
   ```sh
   git clone https://github.com/seu-usuario/projeto-temporizadores.git
   cd projeto-temporizadores
   ```
2. Configure o ambiente VS Code e Pico SDK.
3. Simule o código no Wokwi para validação.
   
## 🚀 Como Executar
1️⃣ **Compile o código no VS Code.**  
2️⃣ **Carregue no Raspberry Pi Pico W.**   
3️⃣ **Teste a alternância automática do semáforo e o acionamento dos LEDs pelo botão.**    

