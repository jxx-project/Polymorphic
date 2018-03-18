# Polymorphic -- Safe subclassing of C++ containers

C++ containers like `std::vector`, `std::list`, `std::map`, `std::unordered_map` are non-polymorphic by design, first by relying on template member functions. These can't be virtual and therefore not overridden in a polymorphic way. Last but not least by not having virtual destructors.

The first limitation, however, doesn't need to stop us from adding new behaviour (i.e. new meber functions) to container subclasses in a polymorphic way, while still exposing the well known container interfaces. Just don't override the non-virtuals. The second limitation is a show stopper, though. Nothings stops us from subclassing C++ containers directly. When such an object is deleted via a base class pointer, however, bad things happen, ranging from memory leaks to heap corruption.

The idea behind the Polymorphic decorators is very simple but effective. They

 * aggregate C++ container class templates with the same set of template parameters,
 * provide 1-by-1 non-virtual inline members and templates forwarding to the aggregated containers. That's a lot of typing, but not exciting, and finally
 * add a virtual destructor!

## License

Free Software, licensed under the [Boost Software License](https://spdx.org/licenses/BSL-1.0).
