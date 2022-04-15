#include <functional>
#include <iostream>
using namespace std;

template <typename Ret, typename... Args>
class Curry {
  public:
    using func = std::function<Ret(Args...)>;

  private:
    func _f;

  public:
    Curry(func f) : _f(f) {}

    Ret operator()(Args... args) { return _f(args...); }

    template <typename... Arg2>
    auto operator()(Arg2... args2) {
        return [this, args2...](Args... args) { return _f(args..., args2...); };
    }
};

int main() {
    return 0;  // world!
}