# 📅 Relatório - 06/06/2025

## 📌 Atividades realizadas:
Hoje, além da continuidade dos testes de firmware em trackers, realizamos extensos testes de campo utilizando patinetes elétricos pela cidade de Ijuí, conforme detalhado abaixo:

---

### **2.163. Teste de Implementação de Firmware em Todos os Trackers Não Funcionais**
- Realizado o upload do firmware fornecido pelo professor Batisti nos trackers inicialmente não funcionais.
- **Problemas Identificados:**
  - Falhas de configuração do ambiente.
  - Bibliotecas não estavam corretamente instaladas.
  - **Incompatibilidade das bibliotecas LMIC:** Observou-se que o problema de funcionamento dos demais trackers com o firmware decorre de uma incompatibilidade da biblioteca LMIC utilizada. Isso faz com que eles reiniciem (resetem) automaticamente durante a execução do código.
- **Correções Realizadas:**
  - Ajustes no ambiente e instalação das bibliotecas necessárias.
  - Seleção correta da placa na IDE do Arduino.
- **Resultado Final:**
  - Firmware carregado com sucesso após os ajustes em trackers compatíveis. Os trackers com incompatibilidade de LMIC continuam apresentando reboots.

---

### **2.164. Upload do Firmware no Tracker 1**
- **Descrição do Processo:**
  - Firmware carregado com sucesso no Tracker 1.
- **Resultado:**
  - Nenhuma falha durante a gravação do código na placa.

---

### **2.165. Upload do Firmware no Tracker 2**
- **Descrição do Processo:**
  - Processo de gravação aparentemente concluído, porém o display do dispositivo não apresentou notificações ou respostas visuais.
- **Situação Atual:**
  - Causa do problema ainda sob investigação.

---

### **2.166. Upload do Firmware no Tracker 3**
- **Descrição do Processo:**
  - Firmware carregado com sucesso no Tracker 3.
- **Limitações:**
  - Tracker não possui módulo GPS, limitando o funcionamento completo do firmware.

---

## 🛴 Testes de Campo com Patinetes Elétricos (06/06/2025)
- Utilização de patinete elétrico da universidade para percorrer diversos pontos de Ijuí, acompanhado de um amigo ([@jawc-05](https://github.com/jawc-05)) que também utilizou patinete.
- Testes realizados até o campus da universidade e em outros locais, com foco no uso do tracker do professor Batisti.
- **Observações:**
  - O tracker apresentava um fio desconectado, ocasionando mau funcionamento do sensor de temperatura e umidade.
  - Apesar da falha no sensor, não foram observados erros nos requests de captura de coordenadas.
  - Em áreas próximas à entrada do campus e regiões mais afastadas da antena/hotspot, o tracker deixou de enviar atividade para o Chirpstack.
  - Realizados mais de 60 testes de captura de coordenadas, todos registrados para análise posterior.

---

## 🔍 Status do Projeto:
### Implementação de Firmware:
- ✅ Firmware funcional em dois dispositivos (Tracker 1 e Tracker 3).
- ⚠️ Problema identificado no Tracker 2, em investigação.
- ⚠️ Trackers com incompatibilidade LMIC continuam reiniciando.

### Configuração de Ambiente:
- ✅ Ambiente ajustado com sucesso, bibliotecas instaladas.

### Funcionalidades dos Trackers:
- 🚫 Tracker 3 com limitações devido à ausência de módulo GPS.
- ⚠️ Sensor de temperatura/umidade do tracker do professor Batisti apresentando falha.

### Testes de Campo:
- 🛴 Testes extensivos em diferentes áreas da cidade, com destaque para pontos distantes do hotspot.

---

## ⚡ Próximos passos:
1. **Investigar o Problema no Tracker 2:**
   - Analisar logs e revisar o processo de upload.
   - Testar hardware, especialmente o display.

2. **Avaliar Funcionalidades Limitadas no Tracker 3:**
   - Planejar integração de módulo GPS.

3. **Corrigir Falha no Tracker do Professor Batisti:**
   - Reconectar fio responsável pelo sensor de temperatura/umidade.

4. **Investigar e Resolver Incompatibilidade LMIC nos demais trackers:**
   - Testar diferentes versões da biblioteca LMIC ou ajustes no firmware visando compatibilidade.

5. **Documentar Resultados:**
   - Atualizar documentação principal da bolsa IoT com resultados e ajustes.

6. **Analisar Dados Capturados:**
   - Avaliar os mais de 60 testes de coordenadas registrados.

---

## 🔗 Recursos Utilizados:
- **IDE:** Arduino IDE
- **Firmware:** Fornecido pelo professor Batisti
- **Dispositivos Testados:** Trackers 1, 2, 3 e tracker do professor Batisti
- **Patinetes Elétricos:** Da universidade
- **Companheiro de Testes:** [@jawc-05](https://github.com/jawc-05)

---