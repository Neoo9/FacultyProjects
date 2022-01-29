#include <QtWidgets/QApplication>
#include "StartUpGUI.h"
#include "GUIAdmin.h"
#include "GUIUser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::vector<TrenchCoat> dv, bask_dv;
    std::unique_ptr<FileRepository> repo(std::make_unique<FileRepository>(&dv, "input.txt"));
    Validator valid;
	int o1 = 0, o2 = 0;
    StartUpGUI setup(&o1, &o2);
    a.exec();
	if (o1 == 0) {
		std::unique_ptr<CSVRepository> bask_repo(std::make_unique<CSVRepository>(&bask_dv, "basket.csv"));
		Controller cont(repo.get(), bask_repo.get(), &valid);
		if (o2 == 0) {
			GUIAdmin admin(&cont);
			return a.exec();
		}
		else {
			std::vector<TrenchCoat> temp_v;
			InMemoryRepository tempp(&temp_v);
			ModelViewTable model(&cont);
			GUIUser user(&cont, &tempp, &model);
			user.add_observer(&model);
			return a.exec();
		}
	}
	else {
		std::unique_ptr<HTMLRepository> bask_repo(std::make_unique<HTMLRepository>(&bask_dv, "basket.html"));
		Controller cont(repo.get(), bask_repo.get(), &valid);
		if (o2 == 0) {
			GUIAdmin admin(&cont);
			return a.exec();
		}
		else {
			std::vector<TrenchCoat> temp_v;
			InMemoryRepository tempp(&temp_v);
			ModelViewTable model(&cont);
			GUIUser user(&cont, &tempp, &model);
			user.add_observer(&model);
			return a.exec();
		}
	}

}
