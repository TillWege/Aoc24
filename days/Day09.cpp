#include "Day09.h"
#include "../common.h"
#include <fstream>
#include <string>
#include <vector>

void Day09::load() {
    // Load any necessary data here
}

void Day09::part1() {
    std::ifstream file("./Inputs/Day09.txt");
    std::string input;

    std::vector<int> data;

    std::getline(file, input);

    input = "2333133121414131402";

    bool isBlockMode = true;
    int idx = 0;

    for(int i = 0; i < input.length(); i++)
    {
        int num = std::stoi(input.substr(i, 1));

        if(isBlockMode)
        {
            auto vals = std::vector<int>(num, idx);
            data.insert(data.end(), vals.begin(), vals.end());

            idx++;
        } else {
            auto vals = std::vector<int>(num, -1);
            data.insert(data.end(), vals.begin(), vals.end());
        }

        isBlockMode = !isBlockMode;
    }

    printf("Shifting data\n");

    for (int i = 0; i < data.size(); ++i) {
        if (data[i] == -1) {
            for (int j = data.size() - 1; j > i; --j) {
                if (data[j] != -1) {
                    data[i] = data[j];
                    data[j] = -1;
                    break;
                }
            }
        }
    }

    printf("Done shifting data\n");
    printf("Calculating checksum\n");

    long long checksum = 0;
    for(int i = 0; i < data.size(); i++)
    {
        if(data[i] != -1)
        {
            checksum += data[i] * i;
        }
    }

    printf("Done calculating checksum: %lld \n", checksum);
}

enum BlockType{
    DATA,
    FREE,
};

struct Block
{
    BlockType type;
    int size;
    int id;
};

typedef std::vector<Block> fsData;

void printData(const fsData* data)
{
    for(auto & i : *data)
    {
        if(i.type == BlockType::FREE)
        {
            for(int j = 0; j < i.size; j++)
            {
                printf(".");
            }

        } else {
            for(int j = 0; j < i.size; j++)
            {
                printf("%d", i.id);
            }
        }
    }
    printf("\n");
}

void Day09::part2() {
    std::ifstream file("./Inputs/Day09.txt");
    std::string input;

    fsData data;

    std::getline(file, input);

    bool isBlockMode = true;
    int idx = 0;

    for(int i = 0; i < input.length(); i++)
    {
        int num = std::stoi(input.substr(i, 1));

        if(isBlockMode)
        {
            Block b = {
                BlockType::DATA,
                num,
                idx
            };
            data.push_back(b);

            idx++;
        } else {
            Block b = {
                BlockType::FREE,
                num,
                -1
            };
            data.push_back(b);
        }

        isBlockMode = !isBlockMode;
    }

    for(int maxId = data[data.size() - 1].id; maxId > 0; maxId--)
    {
        int id;
        for(id = 0; id < data.size(); id++)
        {
            if(data[id].id == maxId)
            {
                break;
            }
        }

        for(int i = 0; i < data.size(); i++)
        {
            if((data[i].type == BlockType::FREE) && (data[i].size >= data[id].size) && (i < id))
            {
                data[i].size -= data[id].size;
                data.insert(data.begin() + i, data[id]);

                data[id + 1].type = BlockType::FREE;
                data[id + 1].id = -1;
                break;
            }
        }
    }

    printf("Final Data:\n");
    printData(&data);

    long long checksum = 0;
    std::vector<int> nums;

    for(int i = 0; i < data.size(); i++)
    {
        if(data[i].type == BlockType::DATA)
        {
            for(int j = 0; j < data[i].size; j++)
            {
                nums.push_back(data[i].id);
            }
        } else {
            for(int j = 0; j < data[i].size; j++)
            {
                nums.push_back(-1);
            }
        }
    }

    for(int i = 0; i < nums.size(); i++)
        if(nums[i] != -1)
            checksum += nums[i] * i;

    printf("Final Checksum: %llu\n", checksum);
}
