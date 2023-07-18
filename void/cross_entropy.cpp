#include <vector>
#include <cmath>
#include <iostream>

//cross entropy loss function

double cross_entropy_loss(const std::vector<double>& predictions, const std::vector<double>& true_labels) {
    double loss = 0.0
    for (int i = 0; i < predictions.size(); i++) {
        loss -= true_labels[i] * log(predictions[i]); //compute the loss for each class and add it to the total loss
    }
    return loss;
}


int main() {
    //define some example prediction and true labels
    std::vector<double> predictions = {0.7, 0.2, 0.1};
    std::vector<double> true_labels = {1.0, 0.0, 0.0};

    //compute the cross entropy loss
    double loss = cross_entropy_loss(predictions, true_labels)

    //prin the loss 
    std::cout << "Cross Entropy Loss: " << loss << std::endl;

    return 0;
}