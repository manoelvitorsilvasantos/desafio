# MEGA NEWS - desafio

O desafio envolverá uma implementação na linguagem C de um programa para resolver o jogo Sudoku utilizando a menor quantidade de instruções condicionais possíveis e a entrega de um modelo de solução para uma problemática.

Gostaríamos de informá-lo que esta atividade deve ser entregue até as 00:00 horas de 06 de maio de 2023, devendo ser respondido o presente e-mail com o link do github. Certifique-se de ler atentamente todas as instruções e os prazos. Se precisar de alguma ajuda, estamos à disposição para orientá-lo e tirar todas as suas dúvidas.


## Instruções do desafio nº 1:

Sudoku é um jogo muito conhecido que apesar do nome japonês, tem sua origem na Suíça, onde foi criado por um designer de jogos chamado Howard Garns em 1979. Na época, o jogo era conhecido como "Number Place" e só ganhou popularidade no Japão na década de 1980, quando foi rebatizado como Sudoku, que significa "números isolados" em japonês. A partir daí, o jogo se tornou um sucesso mundial e hoje em dia é uma das atividades de quebra-cabeça mais populares e viciantes do mundo.

**1ª Regra - Cada linha deve conter os números de 1 a 9, sem repetições**:
O jogador deve preencher cada linha da tabela com cuidado para que não exista duplicação nestas no final. A ordem numérica é irrelevante.
Cada puzzle, independentemente do seu nível de dificuldade, inicia com números pré-colocados na tabela. O jogador deve utilizar estes dígitos como pistas para encontrar quais os números em falta em cada linha e as suas posições.

**2ª Regra - Os números de 1 a 9 apenas podem estar presentes uma vez por coluna**:
As regras do Sudoku para as colunas são exatamente as mesmas que para as linhas. Também para estas o jogador deve preencher as quadrículas com os números de 1 a 9, sem repetições por coluna. Os números oferecidos ao início do puzzle funcionam como pistas para descobrir quais são os dígitos em falta em cada coluna.

**3ª Regra - Cada dígito apenas pode estar presente uma vez por grupo**:
Uma tabela de Sudoku tradicional de 9 x 9 está dividida em 9 grupos mais pequenos de 3 x3. Os números de 1 a 9 apenas podem estar presentes uma vez em cada um destes grupos.
Na prática, isto significa que o processo de preencher as colunas e linhas sem duplicados encontra dentro de cada grupo restrições ao posicionamento dos números.

**4ª Regra - O valor da soma de cada linha, coluna e grupo é de 45.**



## Instruções do desafio nº 2:

A empresa Comércio Leve LTDA tem um sistema de frente de caixa que faz o registo das vendas e identifica os métodos de pagamento além de se integrar com o sistema da área financeira e contábil.
O gestor da empresa Comercio Leve está buscando a melhor forma de desenvolver um novo sistema para integrar com o sistema frente de caixa para passar a receber valores utilizando o PIX.  

Como desenvolvedor responsável pelo sistema de integração com o PIX para a empresa Comércio Leve LTDA, os requisitos que você precisa atender são:

**1. Receber pagamentos em várias contas de vários bancos distintos:** 
O sistema deve ser capaz de receber pagamentos de diferentes bancos, em diferentes contas bancárias da empresa.

**2. Receber a confirmação de recebimento do banco:** 
O sistema deve receber uma confirmação de que o pagamento foi processado e recebido pelo banco, para que possa registrar a transação e atualizar o sistema de frente de caixa.

**3. Gerar o código QR:**: 
O sistema deve ser capaz de gerar um código QR que possa ser lido pelos clientes para realizar o pagamento usando o PIX.

*Antes de começar o desenvolvimento do sistema, é importante apresentar um esboço do modelo para os gerentes da empresa avaliarem e, em seguida, definir um contrato que será usado na integração. Isso ajudará a garantir que as expectativas dos gerentes e da empresa estejam alinhadas com o que o sistema é capaz de fazer.*


# COMO CONFIGURAR OS ARQUIVOS E LIBS.

## 1. INSTALAÇÃO DA IDE Falcon C++ IDE. 
[FALCON C++ IDE](http://sourceforge.net/projects/falconcpp/files/Binaries/3.3.0.0/Falcon%20C++-3.3.0.0-Setup.exe)

## 2. Depedências:

**1). Sqlite3:**[Sqlite3 API](https://falconcpp.sourceforge.net/packages/database/sqlite)
**2). openssh:**[Openssh API](https://falconcpp.sourceforge.net/packages/cryptography)

## 3. ETAPA DE CONFIGURAÇÃO DO COMPILADOR (E necessário fazer sempre que abrir a IDE):

**1. Instale a IDE;**
**2. Instale o kit de pacote de depedência do SQLITE3;**
**3. No projeto configure a lib para compilar o projeto.**

### 1 - Clique no arquivo Main.c com botão esquerdo do Mouse.
![image](https://user-images.githubusercontent.com/23035967/236598121-1bdd51b7-7e58-4876-bf2b-6e5f762c6436.png)
### 2 - Clique em Propriedades.
![image](https://user-images.githubusercontent.com/23035967/236598128-76521c11-5808-42de-b29a-91a345c4ae13.png)
### 3 - Clique na Opção [Compilador].
![image](https://user-images.githubusercontent.com/23035967/236598137-5b58c33d-de02-4b35-8dcd-c37afe4625c1.png)
### 4 - Na caixa copie os seguintes comandos: 
**-lsqlite3, -lssl, -lssl32, -lcrypto**, e vai adicionando os comandos.
![image](https://user-images.githubusercontent.com/23035967/236598149-a9a81a70-e263-4be3-86cd-a40f2f293bc7.png)
![image](https://user-images.githubusercontent.com/23035967/236598156-0f9db18f-2584-4cf7-840a-ff1975e0d636.png)
![image](https://user-images.githubusercontent.com/23035967/236598160-f25a2a93-fa2a-4ba1-a3c6-6ea41053c123.png)
![image](https://user-images.githubusercontent.com/23035967/236598172-c3f70a90-6b36-47d7-bc7e-13a578466429.png)
![image](https://user-images.githubusercontent.com/23035967/236598178-74681447-ce06-46fd-8ba1-7edfd2832c2b.png)
### 5 - Em seguida clique no botão aplicar e Ok.
![image](https://user-images.githubusercontent.com/23035967/236602395-00dcc42f-57e8-4e23-a2e9-97131ee6c32b.png)
### 6 - Agora só compilar e executar o projeto.
![image](https://user-images.githubusercontent.com/23035967/236598191-9a2e0d56-afc6-4d16-b31c-f22624005d43.png)

## Credências para Logar no Sistema.
### Usuários: mvictor,meganews, admin
### Senhas: 1234, 1234, admin
## Credências para Usar o cartão de Crédito e Débito:
### Senha: 2161
