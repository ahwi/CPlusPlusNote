#pragma once


namespace Logic {
	template <typename Cond, typename T>
	bool any(Cond cond, T v)
	{
		return cond(v);
	}

	template <typename Cond, typename T, typename... Args>
	bool any(Cond cond, T v, Args... arg)
	{
		return cond(v) || any(cond, T, arg...);
	}



}

template<class F>
class Finally {
public:
	Finally(F f) :clean{ f } {}

	~Finally() { clean(); }
private:
	F clean;
};


template<class F>
Finally<F> finally(F f) {
	return Finally<F>{f};
}