## A Pythonic wrapper for C++

```cpp
// C++17
// enum a vector
std::vector<int> vect{ 1, 2, 3 };
for (auto&& [i, val] : enumerate(vect))
{
    // do something
}

// enumerate initializer_list
for (auto&& [i, val] : enumerate({ 1, 2, 3 })
{
    // do something
}
```
