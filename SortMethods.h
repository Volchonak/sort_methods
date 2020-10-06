#include <vector>
#include "ui_mainwindow.h"
#ifndef SORT_METHODS_H
#define SORT_METHODS_H


void SortByBubbleMethod(std::vector<double>& array, Ui::MainWindow* ui) noexcept;
void SortBySelectionMethod(std::vector<double>& array, Ui::MainWindow* ui) noexcept;
void SortByShellMethod(std::vector<double>& array, Ui::MainWindow* ui) noexcept;
void SortByCountingMethod(std::vector<int>& array, Ui::MainWindow* ui) noexcept;
template <class T>
inline void printArray(const std::vector<T>& array, Ui::MainWindow* ui) noexcept
{
    for(auto i : array)
    {
        ui->label_result->setText(ui->label_result->text()+" "+QString::number(i));
    }
     ui->label_result->setText(ui->label_result->text()+"\n");
}

inline void printArray(const std::vector<double>::iterator begin, const std::vector<double>::iterator end, Ui::MainWindow* ui)
{
    while (begin!=end)
    {
        ui->label_result->setText(ui->label_result->text()+" "+QString::number(*begin));
    }
    ui->label_result->setText(ui->label_result->text()+"\n");
}

template<typename T>
void SortByMergeMethod(typename std::vector<T>::iterator array, const std::size_t size) noexcept
{
    if (size > 1)
    {
        std::size_t const left_size = size / 2;
        std::size_t const right_size = size - left_size;

        SortByMergeMethod<T>(array, left_size);
        SortByMergeMethod<T>(array+left_size, right_size);

        std::size_t left_block_offset = 0, right_block_offset = left_size, index_to_move_data = 0;
        std::unique_ptr<T[]> tmp_array(new T[size]);

        while (left_block_offset < left_size || right_block_offset < size)
        {
            if (*(array+left_block_offset) > *(array+right_block_offset))
            {
                tmp_array[index_to_move_data++] = std::move(*(array+left_block_offset));
                ++left_block_offset;
            }
            else
            {
                tmp_array[index_to_move_data++] = std::move(*(array+right_block_offset));
                ++right_block_offset;
            }

            if (left_block_offset == left_size)
            {
                std::copy(std::make_move_iterator(array+right_block_offset),
                          std::make_move_iterator(array+size),
                          &tmp_array[index_to_move_data]);
                break;
            }
            if (right_block_offset == size)
            {
                std::copy(std::make_move_iterator(array+left_block_offset),
                          std::make_move_iterator(array+left_size),
                          &tmp_array[index_to_move_data]);
                break;
            }
        }
        std::copy(std::make_move_iterator(tmp_array.get()),
                  std::make_move_iterator(&tmp_array[size]),
                  array);
    }
}

template <class T>
void SortByQuickMethod(typename std::vector<T>::iterator array, const std::size_t size) noexcept
{
    std::size_t middle = (size-1)/2;
    T value_to_compare = *(array+middle);

    const decltype (array) end = array + size;
    decltype (array) offset_from_left = array;
    decltype (array) offset_from_right = end-1;

    do
    {
        while(*offset_from_left < value_to_compare)
            offset_from_left++;
        while(*offset_from_right > value_to_compare)
            offset_from_right--;
        if(offset_from_left <= offset_from_right)
        {
            std::swap(*offset_from_left,*offset_from_right);
            offset_from_left++;
            offset_from_right--;
        }
    }while(offset_from_left <= offset_from_right);

    if(offset_from_right > array)
        SortByQuickMethod<T>(array,size-(end-offset_from_right-1));
    if(offset_from_left < end-1)
        SortByQuickMethod<T>(offset_from_left, end-offset_from_left);

}

#endif // SORT_METHODS_H
