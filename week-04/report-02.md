# 📅 Relatório - 30/06/2025

## 📌 Atividades realizadas:
Hoje, registro as atividades da semana passada relacionadas à implementação e integração de cálculos de distância entre pontos de referência no aplicativo mobile do repositório [@JaoVicy/AppDistanceCalc](https://github.com/JaoVicy/AppDistanceCalc).

---

### **2.172. Início da Implementação de Cálculo de Distâncias no Mobile**
- Na semana passada, iniciei a implementação do código para cálculo de distâncias entre pontos utilizando coordenadas geográficas.
- **Versão Python:**
  - Desenvolvi e testei um script em Python utilizando a biblioteca `geopy` para calcular as distâncias entre pontos de referência.
- **Migração para Swift (UIKit):**
  - Comecei a portar a lógica do cálculo para o app mobile, utilizando UIKit com Swift.
  - Para a geolocalização, utilizei a biblioteca nativa `CoreLocation`, que permite acessar e manipular coordenadas no iOS.
  - A lógica foi adaptada para receber coordenadas de referência e calcular distâncias diretamente no dispositivo móvel.

---

## 🔍 Status do Projeto:
### Implementação Mobile:
- ✅ Script Python funcional para cálculo de distâncias.
- 🚧 Implementação da lógica em Swift iniciada, utilizando UIKit e CoreLocation.
- ✅ CoreLocation integrado ao projeto para acesso à geolocalização.

### Próximos passos:
1. **Finalizar Integração em Swift:**
   - Completar a lógica de cálculo de distância entre múltiplos pontos no app.
2. **Testar Precisão dos Resultados:**
   - Comparar os resultados obtidos no app com os do script Python (geopy) para validar a implementação.
3. **Aprimorar Interface:**
   - Integrar a funcionalidade à interface do usuário no UIKit para facilitar o uso e visualização das distâncias calculadas.

---

## 🔗 Recursos Utilizados:
- **Python:** Script de referência com biblioteca geopy.
- **Swift (UIKit):** Desenvolvimento mobile.
- **CoreLocation:** Biblioteca nativa para geolocalização em iOS.
- **Repositório:** [@JaoVicy/AppDistanceCalc](https://github.com/JaoVicy/AppDistanceCalc)

---