<!DOCTYPE html>
<html lang="en">

<head>

    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="">
    <meta name="author" content="">

        <title>Controle Raspberry</title>

    <!-- Bootstrap Core CSS -->
    <link href="vendor/bootstrap/css/bootstrap.min.css" rel="stylesheet">

    <!-- Custom Fonts -->
    <link href="vendor/font-awesome/css/font-awesome.min.css" rel="stylesheet" type="text/css">
    <link href='https://fonts.googleapis.com/css?family=Open+Sans:300italic,400italic,600italic,700italic,800italic,400,300,600,700,800' rel='stylesheet' type='text/css'>
    <link href='https://fonts.googleapis.com/css?family=Merriweather:400,300,300italic,400italic,700,700italic,900,900italic' rel='stylesheet' type='text/css'>
    <link href="vendor/magnific-popup/magnific-popup.css" rel="stylesheet">
    <link href="css/creative.min.css" rel="stylesheet">
    <script type="text/javascript" src="jquery-3.1.0.min.js"></script>
    <script type="text/javascript">
	    $(document).ready(function() {
            var timer = setInterval( updateDiv, 1000);
            var counter = 0;  //only here so we can see that the div is being updated if the same error is thrown

            function updateDiv() {
                var messageDiv = $('#temperatura');
                $.ajax({
                        type: 'GET',
                        async: false,
                        url: "/home/pi/Desktop/read/file.txt",
                        cache: false,
                        success: function(result) {
                            counter++;
                            messageDiv.empty();
                            messageDiv.append(result);                        
                        
                        },
                        error: function(xhr, ajaxOptions, thrownError) {
                            counter++;
                            messageDiv.empty();
                            messageDiv.append("thrown error: " + thrownError);
                            messageDiv.append("<br />");
                            messageDiv.append("status text: " + xhr.statusText);
                            messageDiv.append("<br />");
                            messageDiv.append("counter = " + counter);
                        }
                });
            }   

        });
    </script>
</head>

<body id="page-top">

    <nav id="mainNav" class="navbar navbar-default navbar-fixed-top">
        <div class="container-fluid">
            <!-- Brand and toggle get grouped for better mobile display -->
            <div class="navbar-header">
                <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1">
                    <span class="sr-only">Toggle navigation</span> Menu <i class="fa fa-bars"></i>
                </button>
                <a class="navbar-brand page-scroll" href="#page-top">Início</a>
            </div>

            <!-- Collect the nav links, forms, and other content for toggling -->
            <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
                <ul class="nav navbar-nav navbar-right">
                    <li>
                        <a class="page-scroll" href="#about">Temperatura</a>
                    </li>
                    <li>
                        <a class="page-scroll" href="#services">Humidade</a>
                    </li>
                    <li>
                        <a class="page-scroll" href="#portfolio">Botões</a>
                    </li>
                    <li>
                        <a class="page-scroll" href="#contact">Contato</a>
                    </li>
                    </li>
                </ul>
            </div>
            <!-- /.navbar-collapse -->
        </div>
        <!-- /.container-fluid -->
    </nav>

    <header>
        <div class="header-content">
            <div class="header-content-inner">
                <h1 id="homeHeading">Manipulação de pinos da Raspberry Pi!!</h1>
                <hr>
                <p>Esse site é um protótipo de como podemos manipular os pinos da raspberry e também receber informações de sensores!</p>
                <a href="#about" class="btn btn-primary btn-xl page-scroll">Faça o teste!</a>
            </div>
        </div>
    </header>

    <section class="bg-primary" id="about">
        <div class="container">
            <div class="row">
                <div class="col-lg-8 col-lg-offset-2 text-center">
                    <h2 class="section-heading">Leitura da temperatura.</h2>
                    <hr class="light">
                    <p class="text-faded">Aqui temos um exemplo de como podemos fazer a leitura de sensores através dos pinos da rasp.</p>
                    <a href="#services" class="page-scroll btn btn-default btn-xl sr-button">Legal!</a>
                </div>
            </div>
        </div>
    </section>

    <section id="services">
        <div class="container">
            <div class="row">
                <div class="col-lg-12 text-center">
                    <h2 class="section-heading">Leitura da humidade</h2>
                    <hr class="primary">
                    <div id="temperatura"></div>
                    <a href="#portfolio" class="btn btn-primary btn-xl page-scroll">WOW</a>
                </div>
            </div>
        </div>
    </section>

    <section class="no-padding" id="portfolio">
	     <div class="container">
            <div class="row">

                                    
									<!-- On/Off button's picture -->
										<?php
										$val_array = array(0,0,0,0,0,0,0,0);
										//this php script generate the first page in function of the file
										for ( $i= 0; $i<8; $i++) {
											//set the pin's mode to output and read them
											system("gpio mode ".$i." out");
											exec ("gpio read ".$i, $val_array[$i], $return );
										}
										//for loop to read the value
										$i =0;
										for ($i = 0; $i < 8; $i++) {
											//if off
											if ($val_array[$i][0] == 0 ) {
												echo ("<img id='button_".$i."' src='data/img/red/red_".$i.".jpg' onclick='change_pin (".$i.");'/>");
											}
											//if on
											if ($val_array[$i][0] == 1 ) {
												echo ("<img id='button_".$i."' src='data/img/green/green_".$i.".jpg' onclick='change_pin (".$i.");'/>");
											}	 
										}
										?>
										 
										<!-- javascript -->
										<script src="script.js"></script>

            </div>
	     </div>
    </section>




    <aside class="bg-dark">
        <div class="container text-center">
            <div class="call-to-action">
                <h2>Faça o download no Github</h2>
                <a href="http://startbootstrap.com/template-overviews/creative/" class="btn btn-default btn-xl sr-button">Download!</a>
            </div>
        </div>
    </aside>

    <section id="contact">
        <div class="container">
            <div class="row">
                <div class="col-lg-8 col-lg-offset-2 text-center">
                    <h2 class="section-heading">Entre em contato!</h2>
                </div>
                <div class="col-lg-4 col-lg-offset-2 text-center">
                    <i 
                <div class="col-lg-4 text-center">
                    <i class="fa fa-envelope-o fa-3x sr-contact"></i>
                    <p><a href="mailto:arturgomesomatos@gmail.com">Artur Email</a></p>
                </div>
            </div>
        </div>
    </section>

    <!-- jQuery -->
    <script src="vendor/jquery/jquery.min.js"></script>

    <!-- Bootstrap Core JavaScript -->
    <script src="vendor/bootstrap/js/bootstrap.min.js"></script>

    <!-- Plugin JavaScript -->
    <script src="http://cdnjs.cloudflare.com/ajax/libs/jquery-easing/1.3/jquery.easing.min.js"></script>
    <script src="vendor/scrollreveal/scrollreveal.min.js"></script>
    <script src="vendor/magnific-popup/jquery.magnific-popup.min.js"></script>

    <!-- Theme JavaScript -->
    <script src="js/creative.min.js"></script>

</body>

</html>
