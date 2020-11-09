#if !defined(MODULE_H_)
#define MODULE_H_

#include <tuple>
#include <type_traits>
#include <concepts>

template<typename T>
concept Addressable = requires (T x) { { x() } -> std::convertible_to<uint32_t>; };

template<typename T>
concept MultipleAddressable = std::is_enum<T>::value;

template <typename Address, class ... Regs>
class Module {
    using RegisterMap = std::tuple<Regs...>;
    template <size_t Index>
    using RegType = typename std::tuple_element<Index, RegisterMap>::type;

    template <std::size_t... I>
    static constexpr size_t SumSize(std::index_sequence<I...>) {
      return (sizeof(RegType<I>) + ... + 0u);
    }
    static constexpr size_t kSize = SumSize(std::index_sequence_for<Regs...>{});

    template <size_t Index>
    static constexpr size_t kOffsetFor = SumSize(std::make_index_sequence<Index>());

  public:
    size_t size() const { return kSize; }

    template <size_t I>
    RegType<I>& get() {
      auto &reg = *reinterpret_cast<RegType<I>*>(this + kOffsetFor<I>);
      return reg;
    }

    template <size_t I, typename ValueType>
    ValueType And(ValueType mask) {
      return mask & get<I>();
    }

    template <size_t I, typename ValueType>
    void set(ValueType value) {
      auto &reg = *reinterpret_cast<RegType<I>*>(this + kOffsetFor<I>);
      reg = value;
    }

    void *operator new(size_t) requires Addressable<Address> {
      return reinterpret_cast<void *>(static_cast<uint32_t>(Address()));
    }

    void *operator new(size_t, Address mod) requires MultipleAddressable<Address> {
      return reinterpret_cast<void *>(static_cast<uint32_t>(mod));
    }
};


#endif
