static const char PROGMEM INDEX_HTML[] = R"rawliteral(
<html>
<title>SOLO2</title>

<head>

    <style>
        @import url(https://fonts.googleapis.com/css?family=Montserrat);
        @import url(https://fonts.googleapis.com/icon?family=Material+Icons);

        .button {
            background-color: whitesmoke;
            font-family: Montserrat;
            color: black;
            padding: 10px;
            margin: 10px;
            width: 20vw;
            border: 1px solid black;
            border-radius: 12px;
            font-weight: 800;
            font-size: 30px;
        }

        .button:hover {
            background-color: skyblue;
            /* Green */
            color: white;
        }

        .body {
            font-family: Montserrat;
            text-align: center;
            margin: 0px auto;
            padding-top: 30px;
        }

        .container {
            margin: 0%;
            padding: 0%;
            display: flex;
            flex-direction: column;
            text-align: center;
            line-height: 5px;

        }

        .text-block-Background {
            font-family: Montserrat;
            position: absolute;
            text-align: center;
            font-size: 40px;
            width: 200px;
            height: 150px;
            bottom: 20px;
            right: 20px;
            background-color: white;
            opacity: 0.4;
            color: black;
            padding-left: 20px;
            padding-right: 20px;
            border-radius: 10px;
            border: 1px solid white;
        }

        .liveData {
            color: black;
        }

        .divTitle {
            padding: 10px;
            font-family: Montserrat;
            background-color: black;
            color: white;
            text-align: center;
        }

        .divControls {
            background-color: white;
            display: flex;
            flex-direction: row;
            align-items: center;
            margin: 2rem;
        }

        .live {
            position: relative;
        }

        .divCamera {
            width: 100%;
            height: auto;
            transform: rotate(180deg);
        }

        .ctrlLED {
            border-radius: 20px;
        }

        .battery {
            font-family: Montserrat;
            position: absolute;
            text-align: center;
            font-size: 40px;
            width: 30;
            height: 130px;
            top: 20px;
            left: 20px;
            background-color: white;
            opacity: 0.6;
            color: black;
            padding-left: 20px;
            padding-right: 20px;
            border-radius: 10px;
            border: 1px solid white;
        }

        .batteryIND-FULL {
            position: relative;

            display: flex;
            flex-direction: column;
            width: 100%;
            height: 20px;
            padding: 5px;
            background-color: greenyellow;
        }

        .batteryIND-EMPTY {
            position: relative;

            display: flex;
            flex-direction: column;
            width: 100%;
            height: 20px;
            padding: 5px;
            background-color: white;
        }

        .batteryText {
            font-size: 15px;
            font-weight: 800;
        }

        .moveCTRL {
            width: 70vw;
        }

        .gearCTRL {
            margin-right: 0;
            margin-left: auto;
        }

        .gearText {
            font-family: Montserrat;
            font-weight: 800;
            color: grey;

        }

        .icon {
            width: 100%;
        }



        .buttonRED {
            background-color: whitesmoke;
            font-family: Montserrat;
            color: black;
            padding: 10px;
            margin: 10px;
            border: 1px solid black;
            border-radius: 12px;
            font-weight: 800;
            font-size: 50px;
        }

        .buttonRED:hover {
            background-color: red;
            /* Green */
            color: white;
        }

        .buttonGREEN {
            background-color: whitesmoke;
            font-family: Montserrat;
            color: black;
            padding: 10px;
            margin: 10px;
            border: 1px solid black;
            border-radius: 12px;
            font-weight: 800;
            font-size: 50px;
        }

        .buttonGREEN:hover {
            background-color: greenyellow;
            /* Green */
            color: white;
        }

        .gearNO {
            position: absolute;
            color: white;
            bottom: 140px;
            right: 10px;
            z-index: 1;

        }

        .in {
            position: absolute;
            font-family: Montserrat;
            color: red;
            font-weight: bolder;
            font-size: 30px;

            padding: 0px 22px;


        }
    </style>
</head>

<body>
    <div class="container">
        <div class="divTitle">
            <h2>SOLO2</h2>
            <p>Firmware v.1.0</p>

        </div>
        <div class="live">
            <div class="gearNO">
                <p class="in" id="gear">
                    0
                </p>
                <i class="material-icons" style="font-size:60px">brightness_1</i>

            </div>

            <img src="" class="divCamera" id="photo">

            <div class="text-block-Background">
                <p class="liveData" id="dr"></p>
                <p class="liveData" id="dl"></p>
            </div>
            <div class="battery">
                <p class="batteryText" id="battLVL">100%</p>
                <button class="batteryIND-EMPTY" id="b4"></button>
                <button class="batteryIND-EMPTY" id="b3"></button>
                <button class="batteryIND-EMPTY" id="b2"></button>
                <button class="batteryIND-EMPTY" id="b1"></button>
            </div>
        </div>
        <div class="divControls">
            <div class="moveCTRL">
                <div class="top">
                    <button class="button" onmousedown="toggleCheckbox('forward');"
                        ontouchstart="toggleCheckbox('forward');" onmouseup="toggleCheckbox('stop');"
                        ontouchend="toggleCheckbox('stop');"><i class="material-icons"
                            style="font-size:60px">keyboard_double_arrow_up</i></button>
                </div>
                <div class="mid">
                    <button class="button" onmousedown="toggleCheckbox('left');" ontouchstart="toggleCheckbox('left');"
                        onmouseup="toggleCheckbox('stop');" ontouchend="toggleCheckbox('stop');"><i
                            class="material-icons" style="font-size:60px">keyboard_double_arrow_left</i></button>
                    <button class="buttonRED" onmousedown="toggleCheckbox('stop');"
                        ontouchstart="toggleCheckbox('stop');"><i class="material-icons"
                            style="font-size:60px">pan_tool</i></button>
                    <button class="button" onmousedown="toggleCheckbox('right');"
                        ontouchstart="toggleCheckbox('right');" onmouseup="toggleCheckbox('stop');"
                        ontouchend="toggleCheckbox('stop');"><i class="material-icons"
                            style="font-size:60px">keyboard_double_arrow_right</i></button>
                </div>
                <div class="bot">
                    <button class="button" onmousedown="toggleCheckbox('backward');"
                        ontouchstart="toggleCheckbox('backward');" onmouseup="toggleCheckbox('stop');"
                        ontouchend="toggleCheckbox('stop');"><i class="material-icons"
                            style="font-size:60px">keyboard_double_arrow_down</i></button>
                </div>
            </div>
            <div class="gearCTRL">


                <div class="gearUP">
                    <button class="buttonRED" onmousedown="toggleGear('gearUP');" ><i class="material-icons"
                            style="font-size:40px">exposure_plus_1</i>
                    </button>
                </div>
                <div class="gearText">
                    <div class="icon"> <i class="material-icons" style="font-size:40px">settings</i></div>
                </div>
                <div class="gearDOWN">
                    <button class="buttonGREEN" onmousedown="toggleGear('gearDOWN');"
                    ><i class="material-icons"
                            style="font-size:40px">exposure_neg_1</i></button>
                </div>
                <div class="ctrlLED">
                    <button class="buttonGREEN" onmousedown="toggleCheckbox('LED_ON');"
                         onmouseup="toggleCheckbox('LED_OFF');"
                        ><i class="material-icons"
                            style="font-size:40px">light_mode</i></button>
                </div>
            </div>

        </div>
    </div>
    <script>
        function toggleCheckbox(x) {
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "/action?go=" + x, true);
            xhr.send();
        }
        function toggleGear(x) {
            console.log(window.location.href.slice(0, -1) + ":82/live?get=" + x);
            var xhr = new XMLHttpRequest();
            xhr.open("GET", window.location.href.slice(0, -1) + ":82/live?get=" + x, true);
            xhr.send();
        }
        window.onload = document.getElementById("photo").src = window.location.href.slice(0, -1) + ":81/stream";
        setInterval(function () {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("dr").innerHTML = this.responseText;
                }
            };
            xhttp.open("GET", window.location.href.slice(0, -1) + ":82/live?get=distanceRight", true);

            xhttp.send();
        }, 1000)
        setInterval(function () {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("dl").innerHTML = this.responseText;
                }
            };
            xhttp.open("GET", window.location.href.slice(0, -1) + ":82/live?get=distanceLeft", true);
            xhttp.send();
        }, 1000)
        setInterval(function () {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("gear").innerHTML = this.responseText;
                }
            };
            xhttp.open("GET", window.location.href.slice(0, -1) + ":82/live?get=gear", true);
            xhttp.send();
        }, 1000)
        setInterval(function () {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    console.log("responseText");
                    console.log(this.responseText);
                    if (this.responseText == "4") {
                        document.getElementById("battLVL").innerHTML = "100%";

                        document.getElementById("b4").classList.remove('batteryIND-EMPTY');
                        document.getElementById("b4").classList.add('batteryIND-FULL');
                        document.getElementById("b3").classList.remove('batteryIND-EMPTY');
                        document.getElementById("b3").classList.add('batteryIND-FULL');
                        document.getElementById("b2").classList.remove('batteryIND-EMPTY');
                        document.getElementById("b2").classList.add('batteryIND-FULL');
                        document.getElementById("b1").classList.remove('batteryIND-EMPTY');
                        document.getElementById("b1").classList.add('batteryIND-FULL');
                    } else if (this.responseText == "3") {
                        document.getElementById("battLVL").innerHTML = "75%";
                        document.getElementById("b4").classList.remove('batteryIND-FULL');
                        document.getElementById("b4").classList.add('batteryIND-EMPTY');
                        document.getElementById("b3").classList.remove('batteryIND-EMPTY');
                        document.getElementById("b3").classList.add('batteryIND-FULL');
                        document.getElementById("b2").classList.remove('batteryIND-EMPTY');
                        document.getElementById("b2").classList.add('batteryIND-FULL');
                        document.getElementById("b1").classList.remove('batteryIND-EMPTY');
                        document.getElementById("b1").classList.add('batteryIND-FULL');
                    } else if (this.responseText == "2") {
                        document.getElementById("battLVL").innerHTML = "50%";

                        document.getElementById("b4").classList.remove('batteryIND-FULL');
                        document.getElementById("b4").classList.add('batteryIND-EMPTY');
                        document.getElementById("b3").classList.remove('batteryIND-FULL');
                        document.getElementById("b3").classList.add('batteryIND-EMPTY');
                        document.getElementById("b2").classList.remove('batteryIND-EMPTY');
                        document.getElementById("b2").classList.add('batteryIND-FULL');
                        document.getElementById("b1").classList.remove('batteryIND-EMPTY');
                        document.getElementById("b1").classList.add('batteryIND-FULL');
                    } else if (this.responseText == "1") {
                        document.getElementById("battLVL").innerHTML = "25%";

                        document.getElementById("b4").classList.remove('batteryIND-FULL');
                        document.getElementById("b4").classList.add('batteryIND-EMPTY');
                        document.getElementById("b3").classList.remove('batteryIND-FULL');
                        document.getElementById("b3").classList.add('batteryIND-EMPTY');
                        document.getElementById("b2").classList.remove('batteryIND-FULL');
                        document.getElementById("b2").classList.add('batteryIND-EMPTY');
                        document.getElementById("b1").classList.remove('batteryIND-EMPTY');
                        document.getElementById("b1").classList.add('batteryIND-FULL');
                    } else if (this.responseText == "0") {
                        document.getElementById("battLVL").innerHTML = "LOW";
                        document.getElementById("b4").classList.remove('batteryIND-FULL');
                        document.getElementById("b4").classList.add('batteryIND-EMPTY');
                        document.getElementById("b3").classList.remove('batteryIND-FULL');
                        document.getElementById("b3").classList.add('batteryIND-EMPTY');
                        document.getElementById("b2").classList.remove('batteryIND-FULL');
                        document.getElementById("b2").classList.add('batteryIND-EMPTY');
                        document.getElementById("b1").classList.remove('batteryIND-FULL');
                        document.getElementById("b1").classList.add('batteryIND-EMPTY');
                    }
                }


            };
            xhttp.open("GET", window.location.href.slice(0, -1) + ":82/live?get=battery", true);
            xhttp.send();
        }, 50000)
    </script>
</body>

</html>
)rawliteral";
