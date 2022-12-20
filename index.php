    <?php
        echo '<h1>Baska page</h1>';
        
        $r = $_GET["r"];
        $g = $_GET["g"];
        $b = $_GET["b"];
        $t = $_GET["t"];
        
        $text = "r=" . $r . " g=" . $g . " b=" . $b . " t=" . $t;
        // $sum = $sn1 + $sn2;
        echo $text;
        echo "<div class='background-color: rgb($r,$g,$b);'></div>";
    ?>