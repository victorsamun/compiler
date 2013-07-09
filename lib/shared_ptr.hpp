#ifndef _SHARED_PTR_HPP_
#define _SHARED_PTR_HPP_

template <typename T>
class shared_ptr {
	class counter {
		T * obj;
		int refs;

	public:
		counter (T * obj) : obj (obj), refs (1) { }

		void add_ref (void) { ++ refs; }

		void release_ref (void) { -- refs; }

		bool is_shared (void) const { return refs; }

		T * get (void) { return obj; }

		~counter (void) { if (! refs) delete obj; }
	};

	counter * c;

public:
	shared_ptr (T * obj) { c = new counter (obj); }

	shared_ptr (const shared_ptr <T> & rhs) { (c = rhs.c)->add_ref (); }

	shared_ptr <T> & operator = (const shared_ptr <T> & rhs) {
		if (& rhs == this)
			return * this;

		c->release_ref ();
		if (! c->is_shared ())
			delete c;

		(c = rhs.c)->add_ref ();
		return * this;
	}

	T & operator * (void) const { return * c->get (); }

	T * operator -> (void) const { return & * * this; }

	operator T * (void) const { return c->get (); }

	bool operator == (const shared_ptr <T> & rhs) const { return c == rhs.c; }

	bool operator != (const shared_ptr <T> & rhs) const { return ! (* this == rhs); }

	~shared_ptr (void) {
		c->release_ref ();
		if (! c->is_shared ())
			delete c;
	}
};

#endif

