# 📅 Relatório - 3 a 5 de Novembro de 2025

Durante a primeira semana de novembro (3 a 5/11) concentrei-me em estudos e no início de um projeto em Python voltado à análise de dados do DATASUS, hospedado no repositório @jawc-05/SUS_PROJECT (https://github.com/jawc-05/SUS_PROJECT). A ideia principal do projeto é utilizar conjuntos de dados disponíveis no Kaggle e no DATASUS para realizar exploração, limpeza e análises que suportem pesquisas e visualizações relevantes para saúde pública.

## 📌 Atividades por dia

- Dia 3  
  - Levantamento inicial sobre as bases de dados do DATASUS e pesquisa de conjuntos relacionados no Kaggle para identificar fontes adequadas (formatos, granularidade e variáveis de interesse).  
  - Planejamento do escopo inicial do repositório: decidir usar Jupyter Notebooks para EDA, scripts para processamento e um diretório para dados brutos e processados.

- Dia 4  
  - Estruturei o repositório (folders para notebooks, scripts, dados e documentação) e iniciei o ambiente de desenvolvimento em Python (virtualenv/venv / lista de dependências básicas: pandas, numpy, matplotlib/seaborn, jupyter).  
  - Criei o notebook inicial para EDA com importações, carregamento de uma amostra de dados e primeiras inspeções (tipos, contagem de valores nulos, estatísticas descritivas).

- Dia 5  
  - Realizei as primeiras limpezas e transformações nos dados de amostra (tratamento de valores faltantes, padronização de colunas e filtragem inicial).  
  - Documentei os passos iniciais no README do projeto explicando a proposta, fontes dos dados (Kaggle/DATASUS) e próximos objetivos para a análise.

---

## 🔍 Resultados e status

- ✅ Repositório criado e estruturado: notebooks, scripts e diretórios de dados iniciais.  
- ✅ Ambiente Python configurado com dependências básicas e notebook de EDA iniciado.  
- ✅ Levantamento de datasets do DATASUS/Kaggle concluído e amostras carregadas para testes.  
- ⚠️ Dados completos ainda precisam ser baixados e organizados para análises em escala; etapas de limpeza mais profundas permanecem pendentes.

---

## ⚡ Próximos passos

1. Baixar conjuntos completos do DATASUS/Kaggle e organizar os dados brutos no repositório.  
2. Continuar o EDA em profundidade (análises temporais, geográficas e por variáveis-chave) e gerar visualizações iniciais.  
3. Implementar pipelines de limpeza reutilizáveis (scripts ou notebooks modularizados) e documentar o processo de reproducibilidade.  
4. Avaliar questões analíticas específicas a serem respondidas (por exemplo, tendências por região, correlações relevantes) e preparar notebooks de análise direcionada.

Segui a semana alternando entre aprendizado sobre as fontes de dados e tarefas práticas de setup e EDA, estabelecendo uma base sólida para avançar nas análises mais detalhadas nas próximas semanas.