#include <string>
#include <format>
#include <iomanip>
#include <sstream>
#include <iostream>


using namespace std;

struct TabletScanner {
    string ModelName;
    float Price;
    float HorizontalSize;
    float VerticalSize;

    TabletScanner(string modelName, float price, float horizontalSize, float verticalsize)
    {
        ModelName = modelName;
        Price = price;
        HorizontalSize = horizontalSize;
        VerticalSize = verticalsize;
    }

    string ToString() {
        stringstream stream;

        stream << fixed << setprecision(2) << HorizontalSize;

        return format("{} {}x{} {}\n", ModelName, HorizontalSize, VerticalSize, Price);
    }
};
