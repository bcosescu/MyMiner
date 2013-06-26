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

    const CTableCell*   GetCellUp     () const {return m_pCellUp;}
    void                SetCellUp     (CTableCell* pCell) { m_pCellUp = pCell; }
    const CTableCell*   GetCellDown   () const {return m_pCellDown;}
    void                SetCellDown   (CTableCell* pCell) { m_pCellDown = pCell; }
    const CTableCell*   GetCellLeft   () const {return m_pCellLeft;}
    void                SetCellLeft   (CTableCell* pCell) { m_pCellLeft = pCell; }
    const CTableCell*   GetCellRight  () const {return m_pCellRight;}
    void                SetCellRight  (CTableCell* pCell) { m_pCellRight = pCell; }

private:

    CTableCell*         m_pCellUp;
    CTableCell*         m_pCellDown;
    CTableCell*         m_pCellLeft;
    CTableCell*         m_pCellRight;
    int                 m_nMarker;
};
