    <?php
        echo '<h1>Baska page</h1>';
        
        $data = json_decode(file_get_contents('https://skittlessorting.azurewebsites.net/'), true);
        
        $r = $data["r"]
        $g = $data["g"]
        $b = $data["b"]
        $t = $data["t"]

        $db = fopen("db.txt", "w") or die("Unable to open file!");
        fwrite($db, $data);
        fclose($db);
        
        $text = "r=" . $r . " g=" . $g . " b=" . $b . " t=" . $t;
        // $sum = $sn1 + $sn2;
        echo $text;
        echo "<div class='background-color: rgb($r,$g,$b);'></div>";
    ?>

   