# Polymorphic — safely derive from C++ standard containers

## Problem

C++ containers like `std::vector`, `std::list`, `std::map`, `std::unordered_map` are non-polymorphic by design, first of all by relying on template member functions. These cannot be virtual and therefore cannot be overridden in a polymorphic way.

This first limitation wouldn't necessarily stop us from adding new behaviour (i.e. new member functions) to container subclasses in a polymorphic way, while still exposing the well known non-polymorphic container interfaces. Just refrain from overriding the non-virtuals!

Another limitation, standard containers' lack of virtual destructors, is a show stopper. We can easily subclass C++ containers directly. When such an object is deleted via a base class pointer, however, bad things happen, ranging from memory leaks to heap corruption.

## The idea behind Polymorphic decorators

is very simple but effective. They

 * compose C++ container class template delegates with the same set of template parameters,
 * provide 1-by-1 forwarding non-virtual inline members and member templates, reference type conversions, constructors, assignment operators, and
 * add a virtual destructor!

## Modern C++ features

 * Can be used almost interchangeably with C++11 standard containers.
 * Implicit conversions allow transparent substitution of one for the other almost everywhere, except as pointer targets. (Note: delegate type rvalue reference conversions are explicit.)
 * Move semantics, rvalue references.

Decorator pattern is cool and old school. Typing hundreds of forwarding members is neither cool nor fun, but a one time task. Fortunately, C++ library standards, while evolving, do not alter signatures of existing public container members.

## Performance impact

### Read and update

None, assuming compilers manage to collapse inline decorator members into the delegate container operations.

### Create and delete

Adds the cost for setting the hidden vtable pointer per decorator instance on creation, and the check for subclass destructors on deletion.

### Memory footprint

Adds one hidden vtable pointer per decorator instance, compared to the raw container.

## Testing

The Polymorphic package is harnessed with a set of test suite templates located in namespace `Testee`. Main focus is template member signatures and return types, but also includes basic plausibility checks of results.

Test suites are not based on any particular framework. With test cases being self contained it is amazing how far you can get with template templates, a plain `std::list<TestCase>`, initializer lists and lambda expressions.

On the the other hand, using test suite templates nicely solved the "test-the-tester" challenge. Running tests first against the delegates, i.e. the C++ standard library implementations, helped developing and verifying test suites. Finally, these were redirected to verify decorators are providing the same APIs as delegates do.

## How to use

Polymorphic decorators are a headers-only library. You may just copy the `include/Polymorphic` directory into a location found by your build system.

CMake is required to install headers in a location along with CMake export files (recommended), and to build and run the test suites.

### Linux

```
./configure [--prefix=/path/to/Polymorphic]
make
make check
make install
```

The default installation prefix is `/usr/local`. The step `make check`, building and running test suites, is optional.

### Windows

```
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=C:/path/to/Polymorphic
```

There is no default for `CMAKE_INSTALL_PREFIX` on Windows. Commands above will create a Visual Studio solution with an `INSTALL` and a `check` project.

**Note:** When using Visual Studio 2013 please configure the [Visual C++ Compiler November 2013 CTP](https://www.microsoft.com/en-us/download/details.aspx?id=41151) toolset in order to get support for `noexcept`. Adding the option `-TCTP_Nov2013` to the cmake command line will then select the appropriate compiler.

## License

Free Software, licensed under the [Boost Software License](https://spdx.org/licenses/BSL-1.0).
