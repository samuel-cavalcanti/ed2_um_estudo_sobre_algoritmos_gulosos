# Algoritmos Gulosos
[![Build Status](https://www.travis-ci.com/samuel-cavalcanti/ed2_um_estudo_sobre_algoritmos_gulosos.svg?branch=main)](https://www.travis-ci.com/samuel-cavalcanti/ed2_um_estudo_sobre_algoritmos_gulosos)
[![codecov](https://codecov.io/gh/samuel-cavalcanti/ed2_um_estudo_sobre_algoritmos_gulosos/branch/main/graph/badge.svg)](https://codecov.io/gh/samuel-cavalcanti/ed2_um_estudo_sobre_algoritmos_gulosos)

## Notas do Professor

O objetivo é escrever um relatório que explique o que são algoritmos gulosos
e dê um exemplo de algoritmo guloso (implementação em C ou CPP)
que soluciona um problema qualquer.


## O que é um algoritmo guloso ?

Um algoritmo para ser conciderado guloso deve sempre
fazer a escolha __localmente ótima__.
É muito comum em problemas de otimização escolher
a a melhor solução no momento, na esperaça que essa
escolha leve ao ótimo global, algo que nem sempre é
verdade, mas em uma parte dos casos tomar sempre a
a melhor __escolha localmente__ resulta em soluções
satisfatórias. Para um algoritmo guloso resultar em
uma solução globalmente otima, essa solução deve
ser compostas por soluções localmente ótimas, essas
característica também é chamada de __Propriedade de escolha gulosa__ . Como
no caso do famoso algoritmo de
[menor caminho de Dijkstra](https://pt.wikipedia.org/wiki/Algoritmo_de_Dijkstra)
onde o menor caminho entre dois nós é composto por menores caminhos.
Um outro problema também possui a propriedade da escolha gulosa __No Problema De Seleção De Atividades__.

## UM PROBLEMA DE SELEÇÃO DE ATIVIDADES (Exemplo de um algoritmo guloso)
Com o objetivo de selecionar um conjunto de tamanho máximo de atividades mutuamente
compatíveis. Suponha que tenhamos um conjunto S = {a1, a2, ..., an} de n atividades propostas que desejam usar um
recurso (por exemplo, uma sala de conferências) que só pode ser utilizado por uma única atividade por vez. Cada
atividade ai tem um tempo de início si e um tempo de término f i , onde 0 ≤ si < f i < ∞. Se selecionada, a atividade ai
ocorre durante o intervalo de tempo meio aberto [si, f i). As atividades ai e aj são compatíveis se os intervalos [si, f i) e
[sj, f j) não se sobrepõem. Isto é, ai e aj são compatíveis se si ≥ f j ou sj ≥ f i). No __problema de seleção de atividades__,
queremos selecionar um subconjunto de tamanho máximo de atividades mutuamente compatíveis.

| i      | 1 | 2 | 3 | 4 | 5 | 6 | 7  | 8  | 9  | 10 | 11 |
|--------|---|---|---|---|---|---|----|----|----|----|----|
| _S_    | 1 | 3 | 0 | 5 | 3 | 5 | 6  | 8  | 8  | 2  | 12 |      |
| _f_    | 4 | 5 | 6 | 7 | 9 | 9 | 10 | 11 | 12 | 14 | 16 |  

O _S_ são os tempos começam a atividade, e  _f_ os tempos de término.
Observe que os valores estão organizados em ordem monotonicamente crescente
de tempos de  término.
Nesse problema foi provado que escolhendo sempre  uma atividade que deixa o
recurso disponível para o maior número possível de outras atividades Agora, entre
as atividades que acabamos escolhendo, uma deve ser a primeira a terminar.
Portanto, nossa intuição nos diz para escolher a atividade em __S__ que tenha
o tempo de término mais cedo, já que isso deixaria o recurso disponível para o 
maior número possível de atividades que ocorram depois dessa.
(Se mais de uma atividade em S tiver o mesmo tempo  de término mais cedo,
poderemos escolher qualquer uma delas.) Em outras palavras, visto que as
atividades são ordenadas em ordem monotônica crescente por tempo de término,
a escolha gulosa é a atividade a1.

### algoritmo greedy Activity Selector
```c++
typedef std::vector<std::vector<int>> activitySet;
typedef std::vector<int> timeSet;

activitySet greedyActivitySelector(timeSet startTime, timeSet finishTime) { 
    auto setSize = startTime.size();
    activitySet largeSubSet{{startTime[0], finishTime[0]}}; // largeSubSet = {a1}
    auto k{0};
    for (auto m = 1; m < setSize; m++) {
        if (startTime[m] >= finishTime[k]) { // escolha gulosa
            largeSubSet.push_back({startTime[m], finishTime[m]}); // largeSubSet = {...,a_m}
            k = m;
        }

    }
    return largeSubSet;
}
```
O procedimento funciona da maneira descrita a seguir. A variável k indexa a adição mais recente a largeSubSet.
Visto que consideramos as atividades em ordem monotonicamente crescente de tempos de término,
finishTime[k] é sempre o tempo de término máximo de qualquer atividade em A.
As linhas 3–4 selecionam a atividade a1 = {startTime[0], finishTime[0]},
inicializam largeSubSet para conter apenas essa atividade e inicializam k para indexar essa
atividade. O laço __for__ encontra a atividade que termina mais cedo em S_k. O laço considera cada atividade
a_m ={startTime[m], finishTime[m]} por vez e acrescenta am a largeSubSet se ela for compatível com todas as
atividades selecionadas anteriormente; tal atividade é a que termina mais cedo S_k. Se a atividade a_m é compatível,
as linhas 6–7 adicionam a atividade a_m a largeSubSet e atribue k com m.

### Informações importantes caso queiremos a solução ótima

Apesar de ser muito tentador seguir apenas a intuição e dizer
que criamos um algoritmo guloso, por que cremos que estamos
seguindo uma sub-estrutura ótima. Na verdade para podermos
realmente afirmar que nosso algoritmo é guloso temos que
seguir  as seguites etapas: 

1. Expressar o problema de otimização como um problema no qual fazemos uma escolha e ficamos com um único
   subproblema para resolver.
2. Provar que sempre existe uma solução ótima para o problema original que usa a escolha gulosa, de modo que a
   escolha gulosa é sempre segura.
3. Demonstrar subestrutura ótima mostrando que, tendo feito a escolha gulosa, o que resta é um subproblema com a
   seguinte propriedade: se combinarmos uma solução ótima para o subproblema com a escolha gulosa que fizemos,
   chegamos a uma solução ótima para o problema original.


