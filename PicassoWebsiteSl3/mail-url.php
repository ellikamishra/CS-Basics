<html>
    <head>
      <title>PICASSO</title>
        <style>
          a{text-decoration:none;}
            * {
              box-sizing: border-box;    /*  dropdown text*/
            }
            .col1{
              float:left;                /* navbar spacing  */
              width: 15%; 
              
            }
            .column {
                                         /*gallery images css to fit 3 in one frame 
                                         in respective categories*/
              float: left;
              width: 50%;
              padding: 5%;
            }
            .row::after {
              border-style: dotted;

              content: "";
              clear: both;
              display: table;
            }
      #picasso{
      -webkit-animation: moving 5s infinite;
    animation: moving 5s infinite;
            }                                     /*heading animation  move in x direction 
                                                 from x=0px to 600px infinite times with 
                                                 interval of 5s      */
 @-webkit-keyframes moving {
        from {-webkit-transform: translateX(0px);}
    to {-webkit-transform: translateX(600px);}
}
@keyframes moving {
    from {transform: translateX(0px);}
    to {transform: translateX(600px);}
}
navbar a {
  float: left;
  font-size: 16px;
  color: white;
  text-align: center;                             /*navbar css*/
  padding: 14px 16px;
  text-decoration: none;
}
.dropdown {
  float: left;                                   /*dropdown properties*/
  overflow: hidden;
}
.dropdown .dropbtn {
  font-size: 20px;
  border: none;
  outline: none;
  color: white;
  padding: 14px 16px;
  background-color: inherit;                 /*dropdown content properties*/
  font-family: inherit; 
  margin: 2px; 
}
.dropdown-content {
  margin-top:5px;
  display: none;
  position: absolute;
  background-color: #f9f9f9;
  min-width: 160px;
  box-shadow: 0px 8px 16px 0px rgba(0,0,0,0.2);
  z-index: 1;
}
.dropdown-content a {
  float: none;
  color: black;
  padding: 12px 16px;
  font-family: 'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', sans-serif;
  text-decoration: none;
  display: block;
  text-align: left;
}
.dropdown-content a:hover {
                                                       /*on hover color change of dropdown*/
  background-color: #ddd;
}
.dropdown:hover .dropdown-content {
  display: block;
}
img{
                                                      /*image gallery border*/
border:solid 2px black;
border-radius: 8px;
}
.button{

  background-color:#fc3003; 
  color:floralwhite;                               /*register button*/
  margin-left: 45%;
  padding: 15px 32px;
}
.error {color: #FF0000;}
            </style>
    </head>
    <body > 
      <!-- header with color gradient from red to yellow and alert box of welcome -->
      <header style="display: inline-block;
      background-image:linear-gradient(180deg,#fc3003,#fca903)">
        <div class='navbar'>
      <div class="col1">
        <a href="/1.html">
        <img src="https://previews.123rf.com/images/alkal82/alkal821107/alkal82110700005/10100106-artists
        -palette-isolated-on-white-computer-generated-image-.jpg" alt="palete"
      style="height: 15%; width: 50%; margin-left:15%;margin-top: 1%;">
    </a>
      </div>
      <div class="col1">
        <div  class='dropdown'>
        <a href="1.html">
          <h3 class ='dropbtn'style="color:whitesmoke;font-family: 'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', sans-serif; 
            margin-left: 10%;font-size:20px">
             Home </h3>
            
        
        </a>
      
        <div class="dropdown-content">
          <a href="/ma.html">Modern</a>
          <a href="/ip.html">Indian</a>
          <a href="/ab.html">Abstract</a>
          <a href="/ph.html">Photography</a>
        </div>
      </div>
    </div>
        </div>
        <div class="col1">
          
          <a href="/ma.html">
          <h3 style="color:whitesmoke;font-family: 'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', 
          sans-serif; margin-left: 10%;font-size:20px">
           Modern</h3>
          </a>
        
          </div>
          <div class="col1">
            <a href='/ip.html'>
            <h3 style="color:whitesmoke;font-family: 'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS',
             sans-serif; margin-left: 10%;font-size:20px">
             Indian </h3>
            </a>
            </div>
            <div class="col1">
              <a href="/ab.html">
              <h3 style="color:whitesmoke;font-family: 'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', 
              sans-serif; margin-left: 10%;font-size:20px">
               Abstract</h3>
              </a>
              </div>
              <div class="col1">
                <a href="/ph.html">
                <h3 style="color:whitesmoke;font-family: 'Gill Sans', 'Gill Sans MT', Calibri, 
                'Trebuchet MS', sans-serif; margin-left: 40%;font-size:20px">
                 Photography </h3>
                </a>
                </div>
                
              </div>
      <h1 id="picasso"style="color:whitesmoke;font-family: 'Gill Sans', 'Gill Sans MT', 'Calibri', 'Trebuchet MS', sans-serif;
      font-size:50px;margin-top: 10%;">PICASSO
  
  </h1>
  
  </header>
<body>
  <?php
// define variables and set to empty values -->
$nameErr = $emailErr = $genderErr = $websiteErr = "";
$name = $email = $gender = $comment = $website = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
  
  
  if (empty($_POST["email"])) {
    $emailErr = "Email is required";
  } else {
    $email = test_input($_POST["email"]);
    // check if e-mail address is well-formed
    if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
      $emailErr = "Invalid email format";
    }
  }
    
  if (empty($_POST["website"])) {
    $website = "";
  } else {
    $website = test_input($_POST["website"]);
    // check if URL address syntax is valid
    if (!preg_match("/\b(?:(?:https?|ftp):\/\/|www\.)[-a-z0-9+&@#\/%?=~_|!:,.;]*[-a-z0-9+&@#\/%=~_|]/i",$website)) {
      $websiteErr = "Invalid URL";
    }    
  }

  if (empty($_POST["comment"])) {
    $comment = "";
  } else {
    $comment = test_input($_POST["comment"]);
  }

  
}

function test_input($data) {
  $data = trim($data);
  $data = stripslashes($data);
  $data = htmlspecialchars($data);
  return $data;
}
?>

<h2>PHP Form Validation</h2>
<!-- <p><span class="error">* required field</span></p> -->
<form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">  
 
  <br><br>
  E-mail: <input type="text" name="email"value="<?php echo $email;?>">
  <span class="error">* <?php echo $emailErr;?></span>
  <br><br>
  Website: <input type="text" name="website"value="<?php echo $website;?>">
  <span class="error">* <?php echo $websiteErr;?></span>
  <br><br>
  Comment: <textarea name="comment" rows="5" cols="40"></textarea>
  <br><br>
  
  <br><br>
  <input type="submit" name="submit" value="Submit">  
</form>



</body>
</html>