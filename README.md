# Polymorphic - Safely derive from C++ standard containers

## Problem

C++ containers like `std::vector`, `std::list`, `std::map`, `std::unordered_map` are non-polymorphic by design, first of all by relying on template member functions. These can't be virtual and therefore not overridden in a polymorphic way.

This first limitation wouldn't necessarily stop us from adding new behaviour (i.e. new member functions) to container subclasses in a polymorphic way, while still exposing the well known non-polymorphic container interfaces. Just refrain from overriding the non-virtuals!

Another limitation, their lack of virtual destructors, is a show stopper. We can easily subclass C++ containers directly. When such an object is deleted via a base class pointer, however, bad things happen, ranging from memory leaks to heap corruption.

## The idea behind Polymorphic decorators

is very simple but effective. They

 * compose C++ container class template delegates with the same set of template parameters,
 * provide 1-by-1 forwarding non-virtual inline members and member templates, reference type conversions, constructors, assignment operators, and
 * add a virtual destructor!

## Modern C++ features

 * Can be used almost interchangeably with C++11 standard containers.
 * Implicit conversions allow transparent substitution of one for the other alomst everywhere, except as pointer targets.
 * Move semantics, rvalue references.

Decorator pattern is cool and old school. Typing hundrets of forwarding members is neither cool nor fun, but a one time task. Fortunately, C++ library standards, while evolving, do not alter signatures of existing public container members.

## Performance impact

### Read and update

None, assuming compilers manage to collapse inline decorator members into the delegate container operations.

### Create and delete

Adds the cost for setting the hidden vtable pointer per decorator instance on creation, and the check for subclass destructors on deletion.

### Memory footprint

Adds one hidden vtable pointer per decorator instance, compared to the raw container.

## License

Free Software, licensed under the [Boost Software License](https://spdx.org/licenses/BSL-1.0).
