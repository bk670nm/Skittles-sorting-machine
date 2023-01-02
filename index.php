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

        if ($data["r"] > 10 and $data["r"] <= 12 and $data["g"] >=14 and $data["g"] <= 20  ){ // orange, yellow
            $angle = 30;
        }
        else if($data["r"] >= 16 and $data["r"] <= 23 and $data["g"] >= 17 and $data["g"] <= 23 ){ // red, purple
            $angle = 60;
        }
        else if($data["r"] >= 15 and $data["r"] <= 20 and $data["g"] >= 13 and $data["g"] <= 18){ // green
            $angle = 90;
        }

        echo $angle;
        exit;
    }

    if ($method == 'GET') {
        $values = read_from_file("db.txt");
        echo '<p>'.$values[0].'   '. $values[1] .'   '. $values[2] .'   '. $values[3].'</p>';
    }
    $page = $_SERVER['PHP_SELF'];
    $sec = "2";
?>



<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta http-equiv="refresh" content="<?php echo $sec?>;URL='<?php echo $page?>'">
        <title>Skittles</title>
        <link rel="stylesheet" href="style.css">
    </head>

    <body>
        <div class="bg-image"></div>

        <div class="bg-text">
            <h1>Skittles sorting machine</h1>
            <p>And I'm a Photographer</p>
        </div>
    </body>
</html>