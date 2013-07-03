// Table cell object

#pragma once

class ICellChangesNotifier;

class CTableCell
{
public:
    friend class CAutomatedTests;

    CTableCell();
    CTableCell(int nMarker);
    ~CTableCell(void);

    int                     GetMarker       () const { return m_nMarker; }
    void                    SetMarker       (int nMarker) { m_nMarker = nMarker; }
    void                    ResetMarker     ();
    bool                    IsEmpty         () const { return m_nMarker == 0; }

    void                    SetNotifier     (ICellChangesNotifier* pNotifier) { m_pNotifier = pNotifier; }
    ICellChangesNotifier*   GetNotifier   () { return m_pNotifier; }

    CTableCell*             GetCellUp       () {return m_pCellUp;}
    void                    SetCellUp       (CTableCell* pCell) { m_pCellUp = pCell; }
    CTableCell*             GetCellDown     () {return m_pCellDown;}
    void                    SetCellDown     (CTableCell* pCell) { m_pCellDown = pCell; }
    CTableCell*             GetCellLeft     () {return m_pCellLeft;}
    void                    SetCellLeft     (CTableCell* pCell) { m_pCellLeft = pCell; }
    CTableCell*             GetCellRight    () {return m_pCellRight;}
    void                    SetCellRight    (CTableCell* pCell) { m_pCellRight = pCell; }

    bool                    Swap            (CTableCell* pCell);
    bool                    IsNeighbour     (CTableCell* pCell);

private:

    ICellChangesNotifier*   m_pNotifier;    //notification object
    CTableCell*             m_pCellUp;      //neighbors
    CTableCell*             m_pCellDown;
    CTableCell*             m_pCellLeft;
    CTableCell*             m_pCellRight;
    int                     m_nMarker;      //value of the cell
};
