#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <filesystem>
#include <nlohmann/json.hpp>
#include "main.h"

struct TargetState
{
	int id = 0;						// 靶标 id
	bool enable = true;				// 是否启用这个靶标, 默认为 false, 用来判断这个靶标是否读取
	double ratio = 0.0;				// 缩放比例
	std::vector<int> box = {};		// box 位置
	std::vector<double> standard_center = {};		// 标准靶标中心坐标
	std::vector<double> standard_radii = {};	// 标准靶标圆环半径
	double standard_distance = 0.0;	// 标准靶标距离
	std::vector<double> standard_offset = {};	// 标准靶标圆环半径

};

std::map<int, TargetState> id2target_states;

void save_main_data_to_json(const std::string filename = "main_data.json") {
	try {
		nlohmann::json j;

		for (auto& [id, target_state] : id2target_states) {
			std::string str_id = std::to_string(id);
			j[str_id]["enable"] = target_state.enable;
			j[str_id]["ratio"] = target_state.ratio;
			j[str_id]["box"] = target_state.box;
			j[str_id]["standard_center"] = target_state.standard_center;
			j[str_id]["standard_radii"] = target_state.standard_radii;
			j[str_id]["standard_distance"] = target_state.standard_distance;
			j[str_id]["standard_offset"] = target_state.standard_offset;
		}

		std::ofstream ofs(filename);
		ofs << j.dump(4);
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}

bool is_directory(const std::string& path) {
	namespace fs = std::filesystem;
	return fs::exists(path) && fs::is_directory(path);
}

bool is_file(const std::string& path) {
	namespace fs = std::filesystem;
	return fs::exists(path) && fs::is_regular_file(path);
}

void load_main_data_from_json(const std::string filename = "main_data.json") {
	try {
		if (!is_file(filename)) {
			std::cout << "file not exist: " << filename << std::endl;
			return;
		}

		nlohmann::json j;
		std::ifstream ifs(filename);
		ifs >> j;

		for (auto& [key, value] : j.items()) {
			int id = std::stoi(key);

			TargetState target_state;
			target_state.id = id;
			target_state.enable = value["enable"].get<bool>();
			target_state.ratio = value["ratio"].get<double>();
			target_state.box = value["box"].get<std::vector<int>>();
			target_state.standard_center = value["standard_center"].get<std::vector<double>>();
			target_state.standard_radii = value["standard_radii"].get<std::vector<double>>();
			target_state.standard_distance = value["standard_distance"].get<double>();
			target_state.standard_offset = value["standard_offset"].get<std::vector<double>>();

			id2target_states[id] = target_state;
		}
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}

int main() {
	id2target_states[0] = TargetState{ 0, true, 1.0, {100, 100, 200, 200}, {100.0, 100.0}, {50.0, 50.0}, 100.0, {1.0, 1.0} };
	id2target_states[2] = TargetState{ 1, true, 1.0, {200, 200, 300, 300}, {200.0, 200.0}, {150.0, 150.0}, 200.0, {2.0, 2.0} };
	id2target_states[3] = TargetState{ 2, true, 1.0, {300, 300, 400, 400}, {300.0, 300.0}, {250.0, 250.0}, 300.0, {3.0, 3.0} };

	save_main_data_to_json();

	id2target_states = {};
	std::cout << "id2target_states size: " << id2target_states.size() << std::endl;

	load_main_data_from_json();
	std::cout << "id2target_states size: " << id2target_states.size() << std::endl;

	for (auto& [id, target_state] : id2target_states) {
		std::cout << "id: " << id << std::endl;
		std::cout << "enable: " << target_state.enable << std::endl;
		std::cout << "ratio: " << target_state.ratio << std::endl;
		std::cout << "box: [ ";
		for (int i : target_state.box) {
			std::cout << i << ", ";
		}
		std::cout << "]" << std::endl;
		std::cout << "standard_center: [ ";
		for (double i : target_state.standard_center) {
			std::cout << i << ", ";
		}
		std::cout << "]" << std::endl;
		std::cout << "standard_radii: [ ";
		for (double i : target_state.standard_radii) {
			std::cout << i << ", ";
		}
		std::cout << "]" << std::endl;
		std::cout << "standard_distance: " << target_state.standard_distance << std::endl;
		std::cout << "standard_offset: [ ";
		for (double i : target_state.standard_offset) {
			std::cout << i << ", ";
		}
		std::cout << "]" << std::endl;
	}

	return 0;
}
