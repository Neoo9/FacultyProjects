#include "pch.h"
#include "../Project1/TrenchCoat.h"
#include "../Project1/TrenchCoat.cpp"
#include "../Project1/DynamicVector.h"
#include "../Project1/Repository.h"
#include "../Project1/Repository.cpp"
#include "../Project1/Controller.h"
#include "../Project1/Controller.cpp"

TEST(TrenchCoatTest, Constructor) {
	TrenchCoat tc;
	TrenchCoat tc2("", "", "", 0, 0, "");
	EXPECT_EQ(tc.get_name(), tc2.get_name());
	EXPECT_EQ(tc.get_size(), tc2.get_size());
	EXPECT_EQ(tc.get_colour(), tc2.get_colour());
	EXPECT_EQ(tc.get_price(), tc2.get_price());
	EXPECT_EQ(tc.get_quantity(), tc2.get_quantity());
	EXPECT_EQ(tc.get_photograph(), tc2.get_photograph());
}

TEST(TrenchCoatTest, CopyConstructor) {
	TrenchCoat tc2("a", "a", "a", 1, 1, "a");
	TrenchCoat tc = tc2;
	EXPECT_EQ(tc.get_name(), tc2.get_name());
	EXPECT_EQ(tc.get_size(), tc2.get_size());
	EXPECT_EQ(tc.get_colour(), tc2.get_colour());
	EXPECT_EQ(tc.get_price(), tc2.get_price());
	EXPECT_EQ(tc.get_quantity(), tc2.get_quantity());
	EXPECT_EQ(tc.get_photograph(), tc2.get_photograph());
}

TEST(TrenchCoatTest, OpOverload1) {
	TrenchCoat tc2("a", "a", "a", 1, 1, "a");
	TrenchCoat tc("b", "b", "b", 2, 2, "b");
	tc = tc2;
	EXPECT_EQ(tc.get_name(), tc2.get_name());
	EXPECT_EQ(tc.get_size(), tc2.get_size());
	EXPECT_EQ(tc.get_colour(), tc2.get_colour());
	EXPECT_EQ(tc.get_price(), tc2.get_price());
	EXPECT_EQ(tc.get_quantity(), tc2.get_quantity());
	EXPECT_EQ(tc.get_photograph(), tc2.get_photograph());
}

TEST(TrenchCoatTest, OpOverload2) {
	TrenchCoat tc2("a", "a", "a", 1, 1, "a");
	TrenchCoat tc("b", "b", "b", 2, 2, "b");
	EXPECT_FALSE(tc == tc2);
	tc.set_name("a");
	EXPECT_FALSE(tc == tc2);
	tc.set_size("a");
	EXPECT_FALSE(tc == tc2);
	tc.set_colour("a");
	EXPECT_FALSE(tc == tc2);
	tc.set_price(1);
	EXPECT_FALSE(tc == tc2);
	tc.set_quantity(1);
	EXPECT_TRUE(tc == tc2);
}

TEST(TrenchCoatTest, ToString) {
	TrenchCoat tc("b", "b", "b", 2, 2, "b");
	EXPECT_EQ(tc.to_string(), "Name: b | Size: b | Colour: b | Price: 2.00 | Quantity: 2");
	EXPECT_EQ(tc.to_string_noq(), "Name: b | Size: b | Colour: b | Price: 2.00");
}

TEST(DynamicVectorTest, Constructor) {
	DynamicVector<TrenchCoat> dv;
	EXPECT_EQ(dv.get_capacity(), 10);
	EXPECT_EQ(dv.get_length(), 0);
}

TEST(DynamicVectorTest, Add){
	DynamicVector<TrenchCoat> dv;
	dv.add(TrenchCoat("a", "a", "a", 1, 1, "a"));
	EXPECT_EQ(dv.get_elements()[0].get_name(), "a");
	dv.add(TrenchCoat("b", "b", "b", 1, 1, "a"));
	EXPECT_EQ(dv.get_elements()[1].get_name(), "b");
	dv.add(TrenchCoat("b", "a", "a", 1, 1, "a"));
	dv.add(TrenchCoat("c", "a", "a", 1, 1, "a"));
	dv.add(TrenchCoat("d", "a", "a", 1, 1, "a"));
	dv.add(TrenchCoat("e", "a", "a", 1, 1, "a"));
	dv.add(TrenchCoat("f", "a", "a", 1, 1, "a"));
	dv.add(TrenchCoat("g", "a", "a", 1, 1, "a"));
	dv.add(TrenchCoat("h", "a", "a", 1, 1, "a"));
	dv.add(TrenchCoat("i", "a", "a", 1, 1, "a"));
	dv.add(TrenchCoat("j", "a", "a", 1, 1, "a"));
	EXPECT_NO_THROW(dv.add(TrenchCoat("a", "a", "a", 1, 1, "a")));
}

TEST(DynamicVectorTest, Remove) {
	DynamicVector<TrenchCoat> dv;
	dv.add(TrenchCoat("a", "a", "a", 1, 2, "a"));
	EXPECT_TRUE(dv.remove(TrenchCoat("a", "a", "a", 1, 2, "a")));
	EXPECT_TRUE(dv.remove(TrenchCoat("a", "a", "a", 1, 1, "a")));
	EXPECT_FALSE(dv.remove(TrenchCoat("a", "a", "a", 1, 0, "a")));
}

TEST(DynamicVectorTest, Update) {
	DynamicVector<TrenchCoat> dv;
	dv.add(TrenchCoat("a", "a", "a", 1, 2, "a"));
	EXPECT_TRUE(dv.update(TrenchCoat("a", "a", "a", 1, 2, "a"), TrenchCoat("b", "b", "b", 2, 3, "b")));
	EXPECT_FALSE(dv.update(TrenchCoat("a", "a", "a", 1, 0, "a"), TrenchCoat("b", "b", "b", 2, 3, "b")));
	EXPECT_EQ(dv.get_elements()[0].get_name(), "b");
}

TEST(DynamicVectorTest, Search) {
	DynamicVector<TrenchCoat> dv;
	dv.add(TrenchCoat("a", "a", "a", 1, 2, "a"));
	EXPECT_TRUE(dv.search(TrenchCoat("a", "a", "a", 1, 2, "a")));
	EXPECT_FALSE(dv.search(TrenchCoat("b", "a", "a", 1, 2, "a")));
}

TEST(RepositoryTest, AddRepo) {
	DynamicVector<TrenchCoat> dv;
	Repository repo(dv);
	EXPECT_EQ(repo.add_repo(TrenchCoat("a", "a", "a", 1, 1, "a")), 0);
	EXPECT_EQ(repo.add_repo(TrenchCoat("a", "a", "a", 1, 1, "a")), 1);
}

TEST(RepositoryTest, RemoveRepo) {
	DynamicVector<TrenchCoat> dv;
	Repository repo(dv);
	EXPECT_EQ(repo.remove_repo(TrenchCoat("a", "a", "a", 1, 1, "a")), 1);
	repo.add_repo(TrenchCoat("a", "a", "a", 1, 1, "a"));
	EXPECT_EQ(repo.remove_repo(TrenchCoat("a", "a", "a", 1, 1, "a")), 0);
}

TEST(RepositoryTest, UpdateRepo) {
	DynamicVector<TrenchCoat> dv;
	Repository repo(dv);
	EXPECT_EQ(repo.update_repo(TrenchCoat("a", "a", "a", 1, 1, "a"), TrenchCoat("b", "b", "b", 2, 2, "b")), 1);
	repo.add_repo(TrenchCoat("a", "a", "a", 1, 1, "a"));
	EXPECT_EQ(repo.update_repo(TrenchCoat("a", "a", "a", 1, 1, "a"), TrenchCoat("b", "b", "b", 2, 2, "b")), 0);
}

TEST(RepositoryTest, SaveLoad) {
	DynamicVector<TrenchCoat> dv;
	Repository repo(dv);
	repo.add_repo(TrenchCoat("a", "a", "a", 1, 1, "a"));
	repo.add_repo(TrenchCoat("b", "b", "b", 2, 2, "b"));
	repo.save("test_input.txt");
	DynamicVector<TrenchCoat> dv2;
	Repository repo2(dv2);
	repo2.load("test_input.txt");
	EXPECT_EQ(repo2.remove_repo(TrenchCoat("c", "c", "c", 1, 1, "a")), 1);
	EXPECT_EQ(repo2.remove_repo(TrenchCoat("b", "b", "b", 2, 2, "b")), 0);
}

TEST(ControllerTest, Validator) {
	DynamicVector<TrenchCoat> dv, bask;
	Repository repo(dv), bask_repo(bask);
	Controller cont(repo, bask_repo);
	EXPECT_THROW(cont.validator("", "", "", -100, 0), std::invalid_argument);
	EXPECT_THROW(cont.validator("", "", "", 100, 0), std::invalid_argument);
	EXPECT_THROW(cont.validator("", "af33w", "", 100, 100), std::invalid_argument);
	EXPECT_THROW(cont.validator("", "", "3445ds", 100, 20), std::invalid_argument);
}

TEST(ControllerTest, AddCont) {
	DynamicVector<TrenchCoat> dv, bask;
	Repository repo(dv), bask_repo(bask);
	Controller cont(repo, bask_repo);
	EXPECT_EQ(cont.add_cont("a", "a", "a", 1, 1, "a"), 0);
	EXPECT_EQ(cont.add_cont("a", "a", "a", 1, 1, "a"), 1);
}

TEST(ControllerTest, RemoveCont) {
	DynamicVector<TrenchCoat> dv, bask;
	Repository repo(dv), bask_repo(bask);
	Controller cont(repo, bask_repo);
	cont.add_cont("a", "a", "a", 1, 1, "a");
	EXPECT_EQ(cont.remove_cont("a", "b", "a", 1, 1), 1);
	EXPECT_EQ(cont.remove_cont("a", "a", "a", 1, 1), 0);
}

TEST(ControllerTest, UpdateCont) {
	DynamicVector<TrenchCoat> dv, bask;
	Repository repo(dv), bask_repo(bask);
	Controller cont(repo, bask_repo);
	cont.add_cont("a", "a", "a", 1, 1, "a");
	EXPECT_EQ(cont.update_cont("a", "a", "a", 1, 1, "b", "b", "b", 2, 2, "b"), 0);
	EXPECT_EQ(cont.update_cont("a", "a", "a", 1, 1, "b", "b", "b", 2, 2, "b"), 1);
}

TEST(ControllerTest, UserSearchCoats) {
	DynamicVector<TrenchCoat> dv, bask, temp_v;
	Repository repo(dv), bask_repo(bask), temp(temp_v);
	Controller cont(repo, bask_repo);
	cont.add_cont("a", "a", "a", 1, 1, "a");
	cont.add_cont("b", "a", "a", 1, 1, "a");
	cont.add_cont("c", "a", "a", 1, 1, "a");
	cont.add_cont("d", "b", "a", 1, 1, "a");
	cont.add_cont("e", "b", "a", 1, 1, "a");
	cont.add_cont("f", "c", "a", 1, 1, "a");
	cont.user_search_coats_cont("a", temp);
	EXPECT_EQ(temp.get_repo().get_length(), 3);
	EXPECT_THROW(cont.user_search_coats_cont("taa", temp), std::invalid_argument);
}

TEST(ControllerTest, AddBasket) {
	DynamicVector<TrenchCoat> dv, bask, temp_v;
	Repository repo(dv), bask_repo(bask), temp(temp_v);
	Controller cont(repo, bask_repo);
	double total;
	TrenchCoat tc("a", "a", "a", 1, 1, "");
	EXPECT_EQ(cont.add_basket(tc, temp, total), 0);
	EXPECT_EQ(cont.add_basket(tc, temp, total), 1);
	tc.set_quantity(0);
	EXPECT_EQ(cont.add_basket(tc, temp, total), 2);
}

int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
