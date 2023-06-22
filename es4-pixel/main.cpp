//
// Created by Federico Marra on 02/07/2020.
//
#include <iostream>
#include <string>
#include <stdexcept>


struct Pixel {
    explicit Pixel(int r = 0, int g = 0, int b = 0) : R(r), G(g), B(b) {}

    int R, G, B;
};


Pixel *decompressImage(std::string &basicString) {
    return new Pixel();
}

Pixel *compressBuffer(Pixel *buffer) {
    return new Pixel();
}

void saveCompressedBuffer(std::string &basicString, Pixel *buffer) {}

void freeBuffer(Pixel *buffer) {}

std::string computeSHA512(Pixel *buffer) {
    return std::string();
}


class Image {
public:
    explicit Image(int w = 1, int h = 1, bool s = false) : width(w), height(h), saved(s) {
        buffer = new Pixel[w * h];
    }

    ~Image() {
        delete[] buffer;
    }

    void load(std::string name) {
        buffer = decompressImage(name);
        std::cout << name << " loaded." << std::endl;
    }

    void save(std::string name) {
        Pixel *compressedBuffer = compressBuffer(buffer);
        saveCompressedBuffer(name, compressedBuffer);
        freeBuffer(compressedBuffer);
        saved = true;
        std::cout << name << " saved." << std::endl;
    }

    void setPixel(int x, int y, const Pixel &pix) {
        if (pix.R >= 0 && pix.G >= 0 && pix.B >= 0 && pix.R <= 255 && pix.G <= 255 && pix.B <= 255) {
            if (x >= 0 && y >= 0 && x <= width && y <= height) {
                buffer[x * width + y] = pix;
                saved = false;
            } else
                throw (std::out_of_range("Out of bound"));
        } else
            throw (std::out_of_range("Error pixel"));
    }

    Pixel getPixel(int x, int y) {
        if (buffer->R >= 0 && buffer->G >= 0 && buffer->B >= 0 && buffer->R <= 255 && buffer->G <= 255 &&
            buffer->B <= 255) {
            if (x >= 0 && y >= 0 && x <= width && y <= height) {
                std::cout << "Pixel in posizione: (" << x + 1 << ";" << y + 1 << ")" << std::endl;
                std::cout << "Rosso:" << buffer[x * width + y].R;
                std::cout << " Giallo:" << buffer[x * width + y].G;
                std::cout << " Blu:" << buffer[x * width + y].B << std::endl << std::endl;
                return buffer[x * width + y];
            } else
                throw (std::out_of_range("Out of bound"));
        } else
            throw (std::out_of_range("Error pixel"));
    }

    bool operator==(const Image &that) const {
        auto l = computeHash();
        auto r = computeHash();
        return l == r;
    }

    bool operator!=(const Image &that) const {
        return !(this == &that);
    }

protected:
    std::string computeHash() const {
        return computeSHA512(buffer);
    }

private:
    int width;
    int height;
    bool saved;
    Pixel *buffer;
};

int main() {
    std::cout << "Esercizio 4:" << std::endl << std::endl;

    Pixel pixel1(255, 0, 255);  //pixel viola
    Pixel pixel2(255, 255, 255);    //pixel bianco

    Image image1(2, 1); //immagine 2*1

    try {
        image1.setPixel(0, 0, pixel1);
    } catch (std::out_of_range &e) {
        std::cerr << e.what() << std::endl;
        return 0;
    }

    try {
        image1.getPixel(0, 0);  //pixel (1,1)
    } catch (std::out_of_range &f) {
        std::cerr << f.what() << std::endl;
        return 0;
    }

    try {
        image1.setPixel(2, 1, pixel2);
    } catch (std::out_of_range &g) {
        std::cerr << g.what() << std::endl;
        return 0;
    }

    image1.save("Image1.jpg");

    image1.load("Image1.jpg");
}
