#include "SortMethods.h"

void SortByBubbleMethod(std::vector<double>& array, Ui::MainWindow* ui) noexcept
{
    if(!array.size())
        return;
    printArray(array,ui);
    bool had_swap = false;

    for(std::size_t i=0; i<array.size(); ++i)
    {
        for(std::size_t j=0; j<array.size()-1; ++j)
        {
            if(array.at(j)<array.at(j+1))
            {
                std::swap(array[j],array[j+1]);
                had_swap = true;
                printArray(array,ui);
            }
        }
        if(!had_swap)
            break;
    }
}

void SortBySelectionMethod(std::vector<double>& array, Ui::MainWindow* ui) noexcept
{
    if(!array.size())
        return;
    printArray(array,ui);
    double max;
    std::size_t max_index;
    for(std::size_t i=0; i<array.size(); ++i)
    {
        max=array[i];
        max_index=i;
        for(std::size_t j = i+1; j<array.size(); ++j)
        {
            if(array[j]>max)
            {
                max = array[j];
                max_index = j;
            }
        }
        if(max_index!=i)
        {
            std::swap(array[i],array[max_index]);
            printArray(array,ui);
        }
    }
}

void SortByShellMethod(std::vector<double>& array, Ui::MainWindow* ui) noexcept
{
    if(!array.size())
        return;
    printArray(array,ui);
    const auto size = array.size();
    for(auto step = size/2; step>0; step/=2)
    {
        for(auto i = step; i<size; ++i)
        {
            for(long long j = i - step; j>=0; j-=step)
            {
                if(array[j]<array[j+step])
                {
                    std::swap(array[j],array[j+step]);
                }
            }
        }
        printArray(array,ui);
    }
}

void SortByCountingMethod(std::vector<int>& array, Ui::MainWindow* ui) noexcept
{
    int min = array[0], max = array[0];

    for(auto i : array)
    {
        if(i < min)
        {
            min = i;
        }
        else if( i> max)
        {
            max = i;
        }
    }

    auto count_array = new std::vector<int>(max-min+1);

    for(auto i : array)
    {
        count_array->at(i-min) = count_array->at(i-min)+1;
    }
    std::size_t index = 0;
    for(auto i = min; i<=max; ++i)
    {
        for(auto j = 0; j < count_array->at(i-min); ++j)
            array[index++] = i;
    }
    printArray(array,ui);
}





