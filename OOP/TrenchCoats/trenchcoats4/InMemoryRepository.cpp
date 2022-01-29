#include "InMemoryRepository.h"

InMemoryRepository::InMemoryRepository(std::vector<TrenchCoat>* dv) :Repository(dv) {}

InMemoryRepository::~InMemoryRepository() = default;

void InMemoryRepository::load() {
	repo->push_back(TrenchCoat("Parpalac from The Matrix movies", "XL", "Black", 3000.00, 1, "https://i.ytimg.com/vi/xJPD_BH5dpU/hqdefault.jpg"));
	repo->push_back(TrenchCoat("Parpalac from The Matrix movies", "XXL", "Black", 3000.00, 1, "https://i.redd.it/a3jfg9lz26j61.jpg"));
	repo->push_back(TrenchCoat("Wool Cashmere M", "L", "Black", 750.00, 28, "https://assets.burberry.com/is/image/Burberryltd/87e6213f25ade7c13d4f777666133df350d7ce9f.jpg?$BBY_V2_ML_1x1$&wid=2800&hei=2800"));
	repo->push_back(TrenchCoat("Franklin Gingerbread F", "M", "Brown", 800.00, 6, "https://www.bodenimages.com/productimages/zoom/19wxms_t0512_cam_w01.jpg"));
	repo->push_back(TrenchCoat("Long Chocolate M", "L", "Beige", 400.00, 17, "https://dqp736wsu6w3m.cloudfront.net/hockerty/og/dimg/landing/man_trenchcoat/trenchcoats_1.png"));
	repo->push_back(TrenchCoat("Leather Cherry F", "S", "Red", 575.00, 10, "https://i1.adis.ws/i/boohooamplience/akk95612_red_xl?pdp.template"));
	repo->push_back(TrenchCoat("Floral Onslaught F", "L", "Black and Blue", 900.00, 5, "https://assets.burberry.com/is/image/Burberryltd/7184AA86-05F2-4AA1-A51B-C12C441E5AE6.jpg?$BBY_V2_ML_3x4$&wid=1278&hei=1700"));
	repo->push_back(TrenchCoat("Deep Mystery M", "S", "Green", 625.00, 16, "https://i.pinimg.com/originals/33/a2/fd/33a2fd2eac810d77dcd6ee1c4b0967b0.jpg"));
	repo->push_back(TrenchCoat("Natural and Fresh M", "L", "Brown", 1250.00, 4, "https://www.distressedjackets.com/image/cache/data/product/b7c06cfe8c05af409a773c7c3a637d39-700x700.jpg"));
	repo->push_back(TrenchCoat("Cute and Daring F", "M", "Pink", 550.00, 29, " https://i.pinimg.com/originals/98/c8/0d/98c80da9387d383ad6f54a51f5ea3b63.jpg"));

}

void InMemoryRepository::save() {}
