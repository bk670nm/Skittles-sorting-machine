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


        $angle = 120; // default

        if ($data["r"] > 10 and $data["r"] <= 15 and $data["g"] >=14 and $data["g"] <= 20  ){ // orange, yellow
            $angle = 30;
        }
        else if($data["r"] >= 17 and $data["r"] <= 23 and $data["g"] >= 18 and $data["g"] <= 23 ){ // red, purple
            $angle = 60;
        }
        else if($data["r"] >= 16 and $data["r"] <= 20 and $data["g"] >= 14 and $data["g"] <= 18){ // green
            $angle = 90;
        }

        echo $angle;
        exit;
    }

    echo '<h1>My page</h1>';

    if ($method == 'GET') {
        $values = read_from_file("db.txt");
        echo "r = " . $values[0] . " g = "  . $values[1] . " b = "  . $values[2] . " t = " . $values[3];
    //    var_dump($values); // array(4) { [0]=> int(10) [1]=> int(20) [2]=> int(30) [3]=> int(50) }
    }
    $page = $_SERVER['PHP_SELF'];
    $sec = "10";
?>

<html>
    <head>
        <meta http-equiv="refresh" content="<?php echo $sec?>;URL='<?php echo $page?>'">
    </head>
    <body>
        <p>reload</p>
    </body>
</html>