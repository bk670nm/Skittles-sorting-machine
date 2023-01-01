<?php

function read_from_file($path)
{
    $data = array();
    if ($file = fopen($path, "r")) {
        $data = file($path, FILE_IGNORE_NEW_LINES);

        fclose($file);
    }
    return array_map('intval', $data);
}

function write_to_file($path, $data)
{
    $file = fopen($path, "w") or die("Unable to open file!");

    fwrite($file, $data["r"] . "\n" . $data["g"] . "\n" . $data["b"] . "\n" . $data["t"]);

    fclose($file);

    return $data;
}

$method = $_SERVER['REQUEST_METHOD'];

if ($method == 'POST') {
    $data = json_decode(file_get_contents('php://input'), true);

    $values = write_to_file("db.txt", $data);

    // TODO: algoritmus

    $angle = 30;

    echo $angle;
    exit;
}

echo '<h1>Baska page</h1>';

if ($method == 'GET') {
    $values = read_from_file("db.txt");
    echo "r = " . $values["r"] . " g = "  . $values["g"] . " b = "  . $values["b"] . " t = " . $values["t"];
    var_dump($values); // array(4) { [0]=> int(10) [1]=> int(20) [2]=> int(30) [3]=> int(50) }
}

// TODO: html in php
?>
<!-- TODO: html in html -->