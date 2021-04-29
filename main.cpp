#include <iostream>
#include <vector>

#include "gtest/gtest.h"

typedef std::vector<std::vector<int>> activitySet;

typedef std::vector<int> timeSet;


const timeSet startTime{
        1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12
};
const timeSet finishTime{
        4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16
};

/*
 * Um teste simples para verificar se copiei todos os valores da tabela
 * do 16.1 do livro algoritmos
 */
TEST(TestGreedyActivitySelector, verificarTamanhoDosConjuntos) {

    EXPECT_EQ(startTime.size(), 11);

    EXPECT_EQ(finishTime.size(), 11);


}

activitySet greedyActivitySelector(timeSet startTime, timeSet finishTime) {

    auto setSize = startTime.size();
    activitySet largeSubSet{{startTime[0], finishTime[0]}}; // A = {a1}
    auto k{0};
    for (auto m = 1; m < setSize; m++) {
        if (startTime[m] >= finishTime[k]) {
            largeSubSet.push_back({startTime[m], finishTime[m]});
            k = m;
        }

    }
    return largeSubSet;
}


/*
 * Segundo o livro algoritmos, apesar desse problema ter mais um valor Otimo
 * o algoritmo gulo encontra o conjuto Otimo {a1,a4,a8,a11}
 */
TEST(TestGreedyActivitySelector, testarAlgoritmo) {

    auto largeSubSet = greedyActivitySelector(startTime, finishTime);

    activitySet expectedSubSet = {
            {startTime[0],  finishTime[0]}, // a1
            {startTime[3],  finishTime[3]}, // a4
            {startTime[7],  finishTime[7]}, // a8
            {startTime[10], finishTime[10]}, // a11
    };

    EXPECT_EQ(largeSubSet, expectedSubSet);


}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);


    return RUN_ALL_TESTS();
}
