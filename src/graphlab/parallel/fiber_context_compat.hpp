/**
 * Compatibility shim for Boost.Context API changes between Boost 1.53 and
 * modern Boost (1.65+). The old API used fcontext_t* pointers and explicit
 * from/to parameters in jump_fcontext. The new API uses fcontext_t values
 * and returns transfer_t.
 */
#ifndef GRAPHLAB_FIBER_CONTEXT_COMPAT_HPP
#define GRAPHLAB_FIBER_CONTEXT_COMPAT_HPP

#include <boost/context/detail/fcontext.hpp>
#include <cstdint>

namespace graphlab {
namespace fiber_compat {

using fcontext_t = boost::context::detail::fcontext_t;
using transfer_t = boost::context::detail::transfer_t;

inline fcontext_t make_fcontext(void* sp, std::size_t size,
                                void (*fn)(transfer_t)) {
  return boost::context::detail::make_fcontext(sp, size, fn);
}

/**
 * Thin wrapper over the modern jump_fcontext. Returns transfer_t so
 * the caller can save the source context in the right place.
 */
inline transfer_t jump_fcontext(fcontext_t to_ctx, intptr_t arg) {
  return boost::context::detail::jump_fcontext(
      to_ctx, reinterpret_cast<void*>(arg));
}

} // namespace fiber_compat
} // namespace graphlab

#endif // GRAPHLAB_FIBER_CONTEXT_COMPAT_HPP
