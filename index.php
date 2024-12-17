<?php
$board = [];
$n = 8;
for ($i = 1; $i <= $n; $i++) {
    $board[$i] = array_fill(1, $n, 0);
}

function isSafe($board, $row, $col) {
    for ($i = 1; $i < $row; $i++) {
        if ($board[$i][$col] == 1) return false;
    }
    for ($i = $row, $j = $col; $i > 0 && $j > 0; $i--, $j--) {
        if ($board[$i][$j] == 1) return false;
    }
    for ($i = $row, $j = $col; $i > 0 && $j <= count($board); $i--, $j++) {
        if ($board[$i][$j] == 1) return false;
    }
    return true;
}

function solveNQueens(&$board, $row, &$solutions) {
    if ($row > count($board)) {
        $solutions[] = $board;
        return;
    }
    for ($col = 1; $col <= count($board); $col++) {
        if (isSafe($board, $row, $col)) {
            $board[$row][$col] = 1;
            solveNQueens($board, $row + 1, $solutions);
            $board[$row][$col] = 0;
        }
    }
}

$solutions = [];
solveNQueens($board, 1, $solutions);

echo "Total Solutions: " . count($solutions) . PHP_EOL;
foreach ($solutions as $solution) {
    foreach ($solution as $row) {
        foreach ($row as $cell) {
            echo $cell . " ";
        }
        echo PHP_EOL;
    }
    echo str_repeat("-", 20) . PHP_EOL;
}
