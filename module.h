#if !defined(MODULE_H_)
#define MODULE_H_

#include <tuple>
#include <type_traits>

template <uint32_t Address, class ... Regs>
class Module {
    using RegisterMap = std::tuple<Regs...>;
    template <size_t Index>
    using RegType = typename std::tuple_element<Index, RegisterMap>::type;

    template <std::size_t... I>
    static constexpr size_t SumSize(std::index_sequence<I...>) {
      return (sizeof(RegType<I>) + ...);
    }
    static constexpr size_t kSize = SumSize(std::index_sequence_for<Regs...>{});

    template <size_t Index>
    static constexpr size_t GetOffsetFor() {
      if constexpr (Index > 0u) {
        return SumSize(std::index_sequence<Index - 1u>{});
      }
      return 0u;
    }

  public:
    size_t size() const { return kSize; }

    template <size_t I>
    RegType<I>& get() {
      auto &reg = *reinterpret_cast<RegType<I>*>(this + GetOffsetFor<I>());
      return reg;
    }

    template <size_t I, typename ValueType>
    ValueType And(ValueType mask) {
      return mask & get<I>();
    }

    template <size_t I, typename ValueType>
    void set(ValueType value) {
      auto &reg = *reinterpret_cast<RegType<I>*>(this + GetOffsetFor<I>());
      reg = value;
    }

    void *operator new(size_t) {
      return reinterpret_cast<void *>(Address);
    }
};


#endif
