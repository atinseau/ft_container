#include "tester.hpp"
#include <criterion/criterion.h>

// CONSTRUCTOR

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

// METHODS

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

// ITERATOR

Test(vector_iterator, regular)
{
	std::vector<std::string> db1;
	std::vector<std::string> db2;

	std::vector<std::string> v1;
	fd::vector<std::string> v2;

	srand(time(NULL));

	for(int i = 0; i < 100; i++)
	{
		int r = rand() % 1000;
		v1.push_back(std::to_string(r));
		v2.push_back(std::to_string(r));
	}

	for(fd::vector<std::string>::const_iterator it = v2.begin(); it != v2.end(); it++)
		db1.push_back(*it);
	for(std::vector<std::string>::const_iterator it = v1.begin(); it != v1.end(); it++)
		db2.push_back(*it);

	db1.clear();
	db2.clear();

	for(fd::vector<std::string>::iterator it = v2.begin(); it != v2.end(); it++)
	{
		*it = "salut tout le monde";
		db1.push_back(*it);
	}
	for(std::vector<std::string>::iterator it = v1.begin(); it != v1.end(); it++)
	{
		*it = "salut tout le monde";
		db2.push_back(*it);
	}
	
	cr_assert(equal(db1, db2), "Vector differ....!");
}


// MEMORY

Test(vector_member, clear_on_empty)
{
	std::vector<foo<int> > v1;
	fd::vector<foo<int> > v2;

	srand(time(NULL));

	for(int i = 0; i < 100; i++)
	{
		int r = rand() % 1000;
		foo<int> e = foo<int>(r);
		v1.push_back(e);
		v2.push_back(e);
	}

	cr_assert(equal(v1, v2), "Vector differ....!");

	v1.clear();
	v2.clear();

	v1.reserve(200);
	v2.reserve(200);

	cr_assert(equal(v1, v2), "Vector differ....!");

	for(int i = 0; i < 100; i++)
	{
		int r = rand() % 1000;
		foo<int> e = foo<int>(r);
		v1.push_back(e);
		v2.push_back(e);
	}

	v1.clear();
	v2.clear();

	cr_assert(equal(v1, v2), "Vector differ....!");
}


Test(vector_memory, no_leak_when_heaped)
{
	std::vector<foo<int>* > v1;
	fd::vector<foo<int>* > v2;

	v1.reserve(100);
	v2.reserve(100);

	for(int i = 0; i < 10; i++)
	{
		foo<int>* a = new foo<int>(i);
		foo<int>* b = new foo<int>(i);

		v1.push_back(a);
		v2.push_back(b);
	}

	v1.clear();
	v2.clear();

	for(int i = 0; i < 10; i++)
	{
		foo<int>* a = new foo<int>(i);
		foo<int>* b = new foo<int>(i);

		v1.push_back(a);
		v2.push_back(b);
	}

	cr_assert(equal(v1, v2), "Vector differ....!");
}

Test(vector_memory, resize_container)
{
	std::vector<foo<int>* >v1;
	fd::vector<foo<int>* >v2;
	
	for(int i = 0; i < 10; i++)
	{
		foo<int>* a = new foo<int>(i);
		foo<int>* b = new foo<int>(i);

		v1.push_back(a);
		v2.push_back(b);
	}

	v1.reserve(100);
	v2.reserve(100);

	cr_assert(equal(v1, v2), "Vector differ....!");

	v1.resize(2);
	v2.resize(2);

	cr_assert(equal(v1, v2), "Vector differ....!");

	v1.clear();
	v2.clear();

	cr_assert(equal(v1, v2), "Vector differ....!");
}

Test(vector_memory, erase_all_iterator)
{
	std::vector<foo<int>* >v1;
	fd::vector<foo<int>* >v2;
	
	for(int i = 0; i < 10; i++)
	{
		foo<int>* a = new foo<int>(i);
		foo<int>* b = new foo<int>(i);

		v1.push_back(a);
		v2.push_back(b);
	}

	while(v1.size() != 0)
		v1.erase(v1.begin());
	while(v2.size() != 0)
		v2.erase(v2.begin());
	
	cr_assert(equal(v1, v2), "Vector differ....!");
}

Test(vector_memory, erase_specific_iterator)
{
	std::vector<foo<int>* >v1;
	fd::vector<foo<int>* >v2;
	
	for(int i = 0; i < 10; i++)
	{
		foo<int>* a = new foo<int>(i);
		foo<int>* b = new foo<int>(i);

		v1.push_back(a);
		v2.push_back(b);
	}

	while(v1.size() != 0 && v2.size() != 0)
	{
		std::vector<foo<int>* >::iterator res_it_1 = v1.erase(v1.begin());
		fd::vector<foo<int>* >::iterator res_it_2 = v2.erase(v2.begin());

		cr_assert(*res_it_1 != *res_it_2, "Vector iterator end differ....!");
		cr_assert(equal(v1, v2), "Vector differ....!");
	}
}

Test(vector_memory, erase_template)
{
	std::vector<foo<int>* >v1;
	fd::vector<foo<int>* >v2;
	
	for(int i = 0; i < 10; i++)
	{
		foo<int>* a = new foo<int>(i);
		foo<int>* b = new foo<int>(i);

		v1.push_back(a);
		v2.push_back(b);
	}

	std::vector<foo<int>* >::const_iterator it_const_1 = v1.begin() + (v1.size() / 2);
	fd::vector<foo<int>* >::const_iterator it_const_2 = v2.begin() + (v2.size() / 2);

	std::vector<foo<int>* >::iterator res_it_1 = v1.erase(v1.begin(), it_const_1);
	fd::vector<foo<int>* >::iterator res_it_2 = v2.erase(v2.begin(), it_const_2);

	cr_assert(*res_it_1 != *res_it_2, "Vector iterator end differ....!");

	cr_assert(equal(v1, v2), "Vector differ....!");

	res_it_1 = v1.erase(v1.begin(), v1.end());
	res_it_2 = v2.erase(v2.begin(), v2.end());

	cr_assert(*res_it_1 != *res_it_2, "Vector iterator end differ....!");
	cr_assert(equal(v1, v2), "Vector differ....!");
	
}