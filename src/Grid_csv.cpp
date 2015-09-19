#ifndef ANTF_GRID_CSV_H
#define ANTF_GRID_CSV_H

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "Grid.hpp"

using namespace jakway_antf;

namespace
{
    /**
     * SEE http://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c
     * CREDIT TO LOKI ASTARI (CODE POSTED AS AN ANSWER) -- http://stackoverflow.com/users/14065/loki-astari
     * see http://meta.stackexchange.com/questions/25956/what-is-up-with-the-source-code-license-on-stack-overflow regarding reuse of code on stackoverflow.com
     */
    class CSVRow
    {
        public:
            std::string const& operator[](std::size_t index) const
            {
                return m_data[index];
            }
            std::size_t size() const
            {
                return m_data.size();
            }
            void readNextRow(std::istream& str)
            {
                std::string         line;
                std::getline(str,line);

                std::stringstream   lineStream(line);
                std::string         cell;

                m_data.clear();
                while(std::getline(lineStream,cell,','))
                {
                    m_data.push_back(cell);
                }
            }
        private:
            std::vector<std::string>    m_data;
    };

    std::istream& operator>>(std::istream& str,CSVRow& data)
    {
        data.readNextRow(str);
        return str;
    }   
        class CSVIterator
    {   
        public:
            typedef std::input_iterator_tag     iterator_category;
            typedef CSVRow                      value_type;
            typedef std::size_t                 difference_type;
            typedef CSVRow*                     pointer;
            typedef CSVRow&                     reference;

            CSVIterator(std::istream& str)  :m_str(str.good()?&str:NULL) { ++(*this); }
            CSVIterator()                   :m_str(NULL) {}

            // Pre Increment
            CSVIterator& operator++()               {if (m_str) { (*m_str) >> m_row;m_str = m_str->good()?m_str:NULL;}return *this;}
            // Post increment
            CSVIterator operator++(int)             {CSVIterator    tmp(*this);++(*this);return tmp;}
            CSVRow const& operator*()   const       {return m_row;}
            CSVRow const* operator->()  const       {return &m_row;}

            bool operator==(CSVIterator const& rhs) {return ((this == &rhs) || ((this->m_str == NULL) && (rhs.m_str == NULL)));}
            bool operator!=(CSVIterator const& rhs) {return !((*this) == rhs);}
        private:
            std::istream*       m_str;
            CSVRow              m_row;
    };
}
/**
 * END OF REUSED CODE
 */


namespace
{
    /**
     * read a CSV file into a jagged 2D array where each bool represents whether that tile is alive
     * returns a shared_ptr to a 2D vector of bools representing tiles
     */
    std::shared_ptr< std::vector<std::vector<bool>>>  readCSVToMatrix(const std::string& filename)
    {
        std::shared_ptr< std::vector<std::vector<bool>>> matrix (new std::vector<std::vector<bool>>);
        
        std::ifstream file(filename);
        //enable exceptions in case of error
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        //loop through each row
        for(CSVIterator it(file); it != CSVIterator(); ++it)
        {
            //add a vector to hold the values for this row
            //since it'll be on the end, it can be accessed with back()
            matrix->emplace_back(std::vector<bool>());

            //loop through each tile in the matrix
            for(std::size_t i = 0; i < (*it).size(); i++)
            {
                //if the CSV cell is empty, the tile is considered dead
                //if it contains anything (even random strings/digits), it's considered alive
                bool cellIsEmpty = ((*it)[i].empty());

                if(cellIsEmpty)
                    matrix->back().push_back(TILE_DEAD);
                else
                    matrix->back().push_back(TILE_ALIVE);
            }
        }

        return matrix;
    }
}


/**
 * static method
 */
std::shared_ptr<Grid> Grid::readGridFromCSV(const std::string& filename)
{
    auto matrixPtr = readCSVToMatrix(filename);


    return nullptr;
}

#endif
