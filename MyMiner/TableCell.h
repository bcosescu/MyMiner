#pragma once

#define MAX_CELL_MARKER 5
class CTableCell
{
public:
    friend bool ExecuteTests();

    CTableCell(int nMarker);
    ~CTableCell(void);
    

private:
    int m_nMarker;
};
