#pragma once

#define MAX_CELL_MARKER 5
class CTableCell
{
public:
    friend bool ExecuteTests();

    CTableCell();
    CTableCell(int nMarker);
    ~CTableCell(void);

    int                 GetMarker     () const { return m_nMarker; }
    void                SetMarker     (int nMarker) { m_nMarker = nMarker; }

    CTableCell*         GetCellUp     () {return m_pCellUp;}
    void                SetCellUp     (CTableCell* pCell) { m_pCellUp = pCell; }
    CTableCell*         GetCellDown   () {return m_pCellDown;}
    void                SetCellDown   (CTableCell* pCell) { m_pCellDown = pCell; }
    CTableCell*         GetCellLeft   () {return m_pCellLeft;}
    void                SetCellLeft   (CTableCell* pCell) { m_pCellLeft = pCell; }
    CTableCell*         GetCellRight  () {return m_pCellRight;}
    void                SetCellRight  (CTableCell* pCell) { m_pCellRight = pCell; }

private:

    CTableCell*         m_pCellUp;
    CTableCell*         m_pCellDown;
    CTableCell*         m_pCellLeft;
    CTableCell*         m_pCellRight;
    int                 m_nMarker;
};
