# from gen_answers import *
from gen import *


def assert_log_gen(expected_repr, gen, actual_repr="next(gen)"):
	expected_repr = str(expected_repr)
	actual_repr = str(actual_repr)
	act = eval(actual_repr)
	exp = eval(expected_repr)
	try:
		assert act == exp
	except AssertionError as e:
		print()
		print(f"Checking that\n    {actual_repr} == {expected_repr}")
		print(f"Expected {exp}, but actualy got {act}")
		raise e


def test_gen_2_8_9_1():
	gen = gen_2_8_9_1()
	assert_log_gen(2, gen)
	assert_log_gen(8, gen)
	assert_log_gen(9, gen)
	assert_log_gen(1, gen)
	try:
		next(gen)
		assert False
	except StopIteration as e:
		pass


def test_gen_odds():
	gen = gen_odds()
	assert_log_gen(1, gen)
	assert_log_gen(3, gen)
	assert_log_gen(5, gen)
	assert_log_gen(7, gen)
	assert_log_gen(9, gen)
	assert_log_gen(11, gen)
	assert_log_gen(13, gen)
	assert_log_gen(15, gen)
	assert_log_gen(17, gen)
	for i in range(19, 200, 2):
		assert_log_gen(i, gen)


def test_gen_evens():
	gen = gen_evens()
	assert_log_gen(0, gen)
	assert_log_gen(2, gen)
	assert_log_gen(4, gen)
	assert_log_gen(6, gen)
	assert_log_gen(8, gen)
	assert_log_gen(10, gen)
	assert_log_gen(12, gen)
	assert_log_gen(14, gen)
	assert_log_gen(16, gen)
	for i in range(18, 200, 2):
		assert_log_gen(i, gen)


def test_gen_numbers_odds():
	gen = gen_numbers("odd")
	assert_log_gen(1, gen)
	assert_log_gen(3, gen)
	assert_log_gen(5, gen)
	assert_log_gen(7, gen)
	assert_log_gen(9, gen)
	assert_log_gen(11, gen)
	assert_log_gen(13, gen)
	assert_log_gen(15, gen)
	assert_log_gen(17, gen)
	for i in range(19, 200, 2):
		assert_log_gen(i, gen)


def test_gen_numbers_evens():
	gen = gen_numbers("even")
	assert_log_gen(0, gen)
	assert_log_gen(2, gen)
	assert_log_gen(4, gen)
	assert_log_gen(6, gen)
	assert_log_gen(8, gen)
	assert_log_gen(10, gen)
	assert_log_gen(12, gen)
	assert_log_gen(14, gen)
	assert_log_gen(16, gen)
	for i in range(18, 200, 2):
		assert_log_gen(i, gen)


def test_gen_numbers_all():
	gen = gen_numbers()
	current = 0
	while current < 1000:
		assert_log_gen(current, gen)
		current += 1


def test_gen_names():
	for person in gen_names():
		names = person.split()
		first_name = names[0]
		family_name = names[1]
		assert first_name in FIRST_NAMES
		assert family_name in FAMILY_NAMES


def test_my_range():
	for i in range(200):
		assert list(my_range(i)) == list(range(i))

	for i in range(200):
		for j in range(200):
			assert list(my_range(i, j)) == list(range(i, j))

	for i in range(-40, 41, 1):
		for j in range(-40, 41, 1):
			for k in list(range(-20, 0, 1)) + list(range(1, 21, 1)):
				assert list(my_range(i, j, k)) == list(range(i, j, k))


prime_string = '''
		2	3	5	7	11	13	17	19	23	29
		31	37	41	43	47	53	59	61	67	71
		73	79	83	89	97	101	103	107	109	113
		127	131	137	139	149	151	157	163	167	173
		179	181	191	193	197	199	211	223	227	229
		233	239	241	251	257	263	269	271	277	281
		283	293	307	311	313	317	331	337	347	349
		353	359	367	373	379	383	389	397	401	409
		419	421	431	433	439	443	449	457	461	463
		467	479	487	491	499	503	509	521	523	541
		547	557	563	569	571	577	587	593	599	601
		607	613	617	619	631	641	643	647	653	659
		661	673	677	683	691	701	709	719	727	733
		739	743	751	757	761	769	773	787	797	809
		811	821	823	827	829	839	853	857	859	863
		877	881	883	887	907	911	919	929	937	941
		947	953	967	971	977	983	991	997	1009	1013
		1019	1021	1031	1033	1039	1049	1051	1061	1063	1069
		1087	1091	1093	1097	1103	1109	1117	1123	1129	1151
		1153	1163	1171	1181	1187	1193	1201	1213	1217	1223
	'''
PRIMES = list(map(int, prime_string.split()))

def test_is_prime():
	for number in range(2, max(PRIMES) + 1):
		if number in PRIMES:
			assert is_prime(number)
		else:
			assert not is_prime(number)


def test_primes():
	gen = gen_primes()
	for prime in PRIMES:
		assert_log_gen(prime, gen)


def test_password_policy_satisfied():
	assert password_policy_satisfied("anowin{OWIFN)(#!)$*(10924019")
	assert not password_policy_satisfied("aaaaaaaaassssssssssdddddddd")
	assert not password_policy_satisfied("124124125124")
	assert not password_policy_satisfied("*(!@U$@*$)(*@#")
	assert password_policy_satisfied("andrpqowdkw2323)(()(FJD")
	assert not password_policy_satisfied("asdlaowKAPWDOK123123amasd")
	assert not password_policy_satisfied("123234345456567678")


def test_gen_passwords():
	for n in range(1, 20):
		for l in range(10, 30):
			count = 0
			for password in gen_passwords(l, n):
				assert password_policy_satisfied(password)
				count += 1
			assert count == n
