#ifndef _NEW_FUNCTIONAL_HPP_
#define _NEW_FUNCTIONAL_HPP_

template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Result>
struct fun_4arg {
	virtual Result operator () (Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4) const = 0;
	virtual ~fun_4arg (void) { }
};

template <typename T, typename Arg1, typename Arg2, typename Arg3, typename Result>
class mem_fun3_t : public fun_4arg <T *, Arg1, Arg2, Arg3, Result> {
	Result (T::* method) (Arg1, Arg2, Arg3);

public:
	explicit mem_fun3_t (Result (T::* method) (Arg1, Arg2, Arg3))
		: method (method) { }

	virtual Result operator () (T * obj, Arg1 arg1, Arg2 arg2, Arg3 arg3) const {
		return (obj->*method) (arg1, arg2, arg3);
	}
};

template <typename T, typename Arg1, typename Arg2, typename Arg3, typename Result>
mem_fun3_t <T, Arg1, Arg2, Arg3, Result> * ptr_mem_fun3 (Result (T::* f) (Arg1, Arg2, Arg3)) {
	return new mem_fun3_t <T, Arg1, Arg2, Arg3, Result> (f);
}

#endif

