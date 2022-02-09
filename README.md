# example source code
	int fac(int:a)
		if(a)
			return a * fac(a-1)
		else
			return 1
	int f()
		int:x = 4 
		fac(x)
	int sum(int:a)
		return a +1
	void main()
		f() + fac(5)
