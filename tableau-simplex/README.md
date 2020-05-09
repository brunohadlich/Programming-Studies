# tableau-simplex

This project implements the simplex method using tableau form and it requires Python 2.
The files tabela* have examples of the way the table must be built to make the script work.

Example:

File tabela1:

  VB x y f1 f2 f3 MD</br>
  f1 1 1 1 0 0 70</br>
  f2 1 1 0 1 0 40</br>
  f3 2 4 0 0 1 90</br>
  L -40 -60 0 0 0 0
    
  This table describes the following problem:
    
    Variables:
      x and y
    
    Restrictions:
      x + y + f1 = 70
      x + y + f2 = 40
      2x + 4y + f3 = 90
    
    Goal function:
      L -40x - 60y = 0

To execute the script run:

  python tableau_simplex.py table_file [output.csv]

Where table_file follows the models described in files tabela1, tabela2 ... and the second argument output.csv is optional and when provided will generate a csv file that can be opened with some spreadsheet tool.
