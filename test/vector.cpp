
#include "tester.hpp"


Test(vector_init, is_empty_at_start)
{
	std::vector<int> v1;
	fd::vector<int> v2;

	cr_assert(v1.empty() == v2.empty(), "Your vector is not empty at start...");
	cr_assert(v1.size() == v2.size(), "Your vector has a size...");
	cr_assert(v1.capacity() == v2.capacity(), "Your vector has a capacity");
}

Test(vector_init, right_constructor)
{
	std::vector<int> v1 (10);
	fd::vector<int> v2 (10);

	cr_assert(equal(v1, v2), "Vector differ....!");
}

Test(vector_init, initialization_list)
{
	std::vector<int> v1 ({1, 2, 3, 4, 5, 6, 7});
	fd::vector<int> v2 ({1, 2, 3, 4, 5, 6, 7});

	cr_assert(equal(v1, v2), "Vector differ....!");
}

Test(vector_init, insert_on_filled_vector)
{
	std::vector<int> v1;
	fd::vector<int> v2;

	for(int i = 0; i < 100; i++)
	{
		v1.push_back(i);
		v2.push_back(i);
	}

	for (int i = 0; i < 100; i++)
	{
		v1.insert(v1.begin() + (v1.size() / 2), i);
		v2.insert(v2.begin() + (v2.size() / 2), i);
	}

	cr_assert(equal(v1, v2), "Vector differ....!");
}


Test(vector_init, insert_on_empty_vector)
{
	std::vector<int> v1;
	fd::vector<int> v2;

	for (int i = 0; i < 100; i++)
	{
		v1.insert(v1.begin() + (v1.size() / 2), i);
		v2.insert(v2.begin() + (v2.size() / 2), i);
	}

	cr_assert(equal(v1, v2), "Vector differ....!");
}


Test(vector_init, assign_empty_vector)
{
	std::vector<int> db;

	std::vector<int> v1;
	fd::vector<int> v2;
	std::vector<int> v3;
	fd::vector<int> v4;

	v1.assign(100, 34);
	v2.assign(100, 34);

	for (int i = 0; i < 100; i++)
	{
		v3.push_back(i);
		v4.push_back(i);
		db.push_back(i);
	}

	v3.assign(db.begin(), db.end());
	v4.assign(db.begin(), db.end());

	cr_assert(equal(v1, v2), "Vector differ....!");
}


Test(vector_init, assign_enable_if_vector)
{
	std::vector<std::string> db1 (10, "salut les gars");
	fd::vector<std::string> db2(10, "salut les gars");

	cr_assert(equal(db1, db2), "Vector differ....!");


	std::vector<std::string> v1;
	fd::vector<std::string> v2;

	v1.assign(db1.begin(), db1.end());
	v2.assign(db1.begin(), db1.end());

	cr_assert(equal(v1, v2), "Vector differ....!");

	v1.assign(db2.begin(), db2.end());
	v2.assign(db2.begin(), db2.end());

	cr_assert(equal(v1, v2), "Vector differ....!");

}