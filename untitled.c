
	return (pf_strchr("dDioOuUxXeEfFgGaAcCsSpn%", c) != NULL);

	return (pf_strchr("hljz", c) != NULL);

	return (pf_strchr("#0-+' ", c) != NULL);

	return (pf_strchr("$*.", c) != NULL);




	________________________________________


	while (str[i])
	{
		start = i;
		valid = 0;
		if (str[i] == '%')
		{
			i++;
			check();
		}
		else
			while (str[i] && str[i] != '%')
				i++;
		count += ft_putnstr(str + start, i - start);
	}
	return (count);
