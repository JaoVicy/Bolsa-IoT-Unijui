# 📅 Relatório - 13/05/2025

## 📌 Atividades realizadas:
Hoje, foram realizados diversos testes relacionados à implementação de firmware em trackers não funcionais e individuais, conforme descrito abaixo:

---

### **2.163. Teste de Implementação de Firmware em Todos os Trackers Não Funcionais**
- Foi realizado o teste de upload do firmware fornecido pelo professor Batisti, já em funcionamento no modelo de tracker montado por ele.
- **Problemas Identificados:**
  - Falhas iniciais relacionadas à configuração do ambiente.
  - Bibliotecas necessárias não estavam corretamente instaladas.
- **Correções Realizadas:**
  - Ajustes no ambiente e instalação das bibliotecas necessárias.
  - Seleção correta da placa na IDE do Arduino.
- **Resultado Final:**
  - Firmware carregado com sucesso após os ajustes.

---

### **2.164. Upload do Firmware no Tracker 1**
- **Descrição do Processo:**
  - O firmware foi carregado com sucesso no Tracker 1.
- **Resultado:**
  - Não houve falhas durante a gravação do código na placa.

---

### **2.165. Upload do Firmware no Tracker 2**
- **Descrição do Processo:**
  - Apesar do procedimento de gravação ter sido aparentemente concluído com sucesso, a tela do dispositivo não apresentou notificações ou respostas visuais após o upload.
- **Situação Atual:**
  - A causa do problema ainda está sob investigação.

---

### **2.166. Upload do Firmware no Tracker 3**
- **Descrição do Processo:**
  - O firmware foi carregado com sucesso no Tracker 3.
- **Limitações:**
  - Este dispositivo não possui módulo GPS integrado, o que compromete o funcionamento completo do firmware, limitando funcionalidades dependentes desse componente.

---

## 🔍 Status do Projeto:
### Implementação de Firmware:
- ✅ Firmware funcional e carregado com sucesso em dois dispositivos (Tracker 1 e Tracker 3).
- ⚠️ Problema identificado no Tracker 2, com causa ainda sob investigação.

### Configuração de Ambiente:
- ✅ Ambiente ajustado com sucesso, com bibliotecas necessárias instaladas.

### Funcionalidades dos Trackers:
- 🚫 Tracker 3 possui limitações funcionais devido à ausência de módulo GPS.

---

## ⚡ Próximos passos:
1. **Investigação do Problema no Tracker 2:**
   - Analisar logs e revisar o processo de upload para identificar a causa da ausência de notificações na tela do dispositivo.
   - Testar o hardware para verificar possíveis problemas no display ou no circuito.

2. **Avaliação de Funcionalidades Limitadas no Tracker 3:**
   - Planejar a integração de um módulo GPS ao Tracker 3 para ativar todas as funcionalidades do firmware.

3. **Documentação dos Resultados:**
   - Atualizar o documento principal da bolsa de IoT com os resultados obtidos e os ajustes realizados.

---

## 🔗 Recursos Utilizados:
- **IDE Utilizada:** Arduino IDE
- **Firmware:** Fornecido pelo professor Batisti
- **Dispositivos Testados:** Trackers 1, 2 e 3