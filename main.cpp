#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>
#include "main.h"

struct TargetState
{
    double ratio = 0.0;                       // 缩放比例
    std::vector<int> box = {};                // box 位置
    std::vector<double> standard_center = {}; // 标准靶标中心坐标
};

void parse_vector(const int indent = 4)
{
    std::cout << "==================== parse_vector ====================" << std::endl;

    std::vector<TargetState> target_states = {
        TargetState{1.0, {100, 100, 200, 200}, {100.0, 100.0}},
        TargetState{2.0, {200, 200, 300, 300}, {200.0, 200.0}},
        TargetState{3.0, {300, 300, 400, 400}, {300.0, 300.0}},
        TargetState{4.0, {400, 400, 500, 500}, {400.0, 400.0}}};

    auto print_target_states = [&target_states]() -> void
    {
        std::cout << "****************************************" << std::endl;
        for (const auto &target_state : target_states)
        {
            std::cout << "ratio: " << target_state.ratio << "; ";
            std::cout << "box: [ ";
            for (int i : target_state.box)
            {
                std::cout << i << ", ";
            }
            std::cout << "]" << "; ";
            std::cout << "standard_center: [ ";
            for (double i : target_state.standard_center)
            {
                std::cout << i << ", ";
            }
            std::cout << "]" << std::endl;
        }
        std::cout << "****************************************" << std::endl
                  << std::endl;
    };
    print_target_states();

    // -------------------- json 序列化 -------------------- //
    nlohmann::json j;
    for (const auto &target_state : target_states)
    {
        nlohmann::json j1;
        j1["ratio"] = target_state.ratio;
        j1["box"] = target_state.box;
        j1["standard_center"] = target_state.standard_center;
        // 使用 push_back 方式添加到 json 数组中
        j.push_back(j1);
    }

    std::string json_str = j.dump(indent);
    std::cout << json_str << std::endl;
    // -------------------- json 序列化 -------------------- //

    // -------------------- json 反序列化 -------------------- //
    nlohmann::json j1 = nlohmann::json::parse(json_str);

    target_states.clear();
    for (const auto &value : j1)
    {
        TargetState target_state;
        target_state.ratio = value["ratio"].get<double>();
        target_state.box = value["box"].get<std::vector<int>>();
        target_state.standard_center = value["standard_center"].get<std::vector<double>>();

        target_states.push_back(target_state);
    }
    print_target_states();
    // -------------------- json 反序列化 -------------------- //
    std::cout << "==================== parse_vector ====================" << std::endl
              << std::endl;
}

void parse_map(const int indent = 4)
{
    std::cout << "==================== parse_map ====================" << std::endl;
    std::map<int, TargetState> id2target_states;
    id2target_states[0] = TargetState{1.0, {100, 100, 200, 200}, {100.0, 100.0}};
    id2target_states[2] = TargetState{2.0, {200, 200, 300, 300}, {200.0, 200.0}};
    id2target_states[3] = TargetState{3.0, {300, 300, 400, 400}, {300.0, 300.0}};
    id2target_states[4] = TargetState{4.0, {400, 400, 500, 500}, {400.0, 400.0}};

    auto print_id2target_states = [&id2target_states]() -> void
    {
        std::cout << "****************************************" << std::endl;
        for (const auto &[id, target_state] : id2target_states)
        {
            std::cout << "id: " << id << "; ";
            std::cout << "ratio: " << target_state.ratio << "; ";
            std::cout << "box: [ ";
            for (int i : target_state.box)
            {
                std::cout << i << ", ";
            }
            std::cout << "]" << "; ";
            std::cout << "standard_center: [ ";
            for (double i : target_state.standard_center)
            {
                std::cout << i << ", ";
            }
            std::cout << "]" << std::endl;
        }
        std::cout << "****************************************" << std::endl
                  << std::endl;
    };
    print_id2target_states();

    // -------------------- json 序列化 -------------------- //
    nlohmann::json j;
    for (const auto &[id, target_state] : id2target_states)
    {
        std::string str_id = std::to_string(id);
        nlohmann::json j1;
        j1["ratio"] = target_state.ratio;
        j1["box"] = target_state.box;
        j1["standard_center"] = target_state.standard_center;
        j[str_id] = j1;
    }

    std::string json_str = j.dump(indent);
    std::cout << json_str << std::endl;
    // -------------------- json 序列化 -------------------- //

    // -------------------- json 反序列化 -------------------- //
    nlohmann::json j1 = nlohmann::json::parse(json_str);

    id2target_states.clear();
    for (const auto &[key, value] : j1.items())
    {
        int id = std::stoi(key);

        TargetState target_state;
        target_state.ratio = value["ratio"].get<double>();
        target_state.box = value["box"].get<std::vector<int>>();
        target_state.standard_center = value["standard_center"].get<std::vector<double>>();

        id2target_states[id] = target_state;
    }
    print_id2target_states();
    // -------------------- json 反序列化 -------------------- //
    std::cout << "==================== parse_map ====================" << std::endl
              << std::endl;
}

int main()
{
    parse_vector();
    parse_map();
    return 0;
}
