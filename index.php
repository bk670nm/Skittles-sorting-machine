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
    $angle = 120; // default

    if ($method == 'POST') {
        $data = json_decode(file_get_contents('php://input'), true);

        $values = write_to_file("db.txt", $data);

        if ($data["r"] > 10 and $data["r"] < 16 and $data["g"] >=13 and $data["g"] <= 20  ){ // orange, yellow
            $angle = 30;
        }
        else if($data["r"] >= 15 and $data["r"] <= 20 and $data["g"] >= 13 and $data["g"] <= 18){ // green
            $angle = 90;
        }
        else if($data["r"] >= 16 and $data["r"] <= 23 and $data["g"] >= 17 and $data["g"] <= 23 ){ // red, purple
            $angle = 60;
        }


        echo $angle;
        exit;
    }

    if ($method == 'GET') {
        $values = read_from_file("db.txt");
        $color = "No color";
        if($angle == 30) {
            $color = "Orange";
        }
        else if($angle == 60){
            $color = "Red";
        }
        else if($angle == 90){
            $color = "Green";
        }

    }

    $page = $_SERVER['PHP_SELF'];
    $sec = "3";
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
            <?php
                echo '<p>RGB: '.$values[0].'   '. $values[1] .'   '. $values[2] .'</p>';
                echo '<p>Actual color: '.$color.'</p>';
                echo '<p>Temperature: '. $values[3].'</p>';
            ?>
        </div>
    </body>
</html>