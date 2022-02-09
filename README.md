# example source code
	int fac(int:a)
		if(a)
			return a * fac(a-1)
		else
			return 1
	f()
		int:x = 4
		fac(x)
	sum(int:a)
		return a +1
	main()
		f() + fac(5)
