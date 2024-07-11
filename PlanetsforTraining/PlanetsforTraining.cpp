#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>

//Library Template Class
template <typename T>
class Library {
protected:
    std::vector<T> items;
    size_t currentSize;
public:
    Library(size_t size) : items(size), currentSize(0) {}

    void addElement(const T& item) {
        if (currentSize >= items.size()) {
            throw std::overflow_error("Library is full. Cannot add more items");
        }
        items[currentSize++] = item;
    }

    void PrintElements() const {
        for (size_t i = 0; i < currentSize; ++i) {
            std::cout << items[i] << std::endl;
        }
    }

    T GetElement(size_t index) const {
        if (index >= currentSize) {
            throw std::out_of_range("Index out of range.");
        }
        return items[index];
    }
};

//PointerLibrary Specialized Template Library
template<typename T>
class PointerLibrary : public Library<std::unique_ptr<T>> {
public:
    using Library<std::unique_ptr<T>>::Library;

    void AddElement(T* item) {
        if (this->currentSize >= this->items.size()) {
            throw std::overflow_error("Library is full. Cannot add more items.");
        }
        this->items[this->currentSize++] = std::unique_ptr<T>(item);
    }

    void PrintElements() const {
        for (size_t i = 0; i < this->currentSize; ++i) {
            std::cout << *(this->items[i]) << std::endl;
        }
    }

    ~PointerLibrary() {
        // Unique pointers will automatically clean up memory
    }
};

class Planets {
public:
    std::string Name;
    Planets() : Name("") {}
    Planets(const std::string& t) : Name(t) {}
    friend std::ostream& operator<<(std::ostream& os, const Planets& Planet) {
        os << "Planet: " << Planet.Name;
        return os;
    }
};

class Stars {
public:
    std::string Name;
    Stars() : Name("") {}
    Stars(const std::string& t) : Name(t) {}
    friend std::ostream& operator<<(std::ostream& os, const Stars& Star) {
        os << "Star: " << Star.Name;
        return os;
    }
};

int main() {
    try {
        //Library for Planets
        Library<Planets> planetLibrary(3);
        planetLibrary.addElement(Planets("Earth"));
        planetLibrary.addElement(Planets("Jupiter"));
        planetLibrary.PrintElements();
        std::cout << "Retrieved: " << planetLibrary.GetElement(1) << std::endl;

        //PointerLibrary for Stars
        PointerLibrary<Stars> starLibrary(1);
        starLibrary.AddElement(new Stars("Sun"));
        starLibrary.PrintElements();
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
