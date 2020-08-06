const char MAIN_page[] PROGMEM = R"=====(
<!doctype html>
<html>
<head>
	<meta charset="UTF-8">
  <title>ĐỒ ÁN TỐT NGHIỆP</title><link rel="icon" href="http://icons.iconarchive.com/icons/bokehlicia/captiva/128/rocket-icon.png" type="image/x-icon" />
  <!--For offline ESP graphs see this tutorial https://circuits4you.com/2018/03/10/esp8266-jquery-and-ajax-web-server/  https://online.hcmute.edu.vn/Portlets/UIS_MySpace/Images/SPKT.jpg http://www.prodapt.com/wp-content/uploads/IoT-Banner.jpg-->
  <script src = "https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.7.3/Chart.min.js"></script>  
  <style>
  canvas{ 
    -moz-user-select: none;
    -webkit-user-select: none;
    -ms-user-select: none;
  }

  /* Data Table Styling */
  #dataTable {
    font-family: "Trebuchet MS", Arial, Helvetica, sans-serif;
    border-collapse: collapse;
    width: 100%;
  }

  #dataTable td, #dataTable th {
    border: 1px solid #ddd;
    padding: 8px;
  }

  #dataTable tr:nth-child(even){background-color: #f2f2f2;}

  #dataTable tr:hover {background-color: #ddd;}

  #dataTable th {
    padding-top: 12px;
    padding-bottom: 12px;
    text-align: left;
    background-color: #4CAF50;
    color: white;
  }
  </style>
</head>
<header class="container">
		<div class="row">
			<div class="col-md-6">
				<img src="https://online.hcmute.edu.vn/Portlets/UIS_MySpace/Images/SPKT.jpg" style="width: 100%" alt="">
			</div>
		</div>
	</header>
<h2><div style="text-align:center;"><b>KIỂM TRA NHỊP TIM VÀ HUYẾT ÁP HẰNG NGÀY</b></div></h2>
 <table border="1px" cellspacing="0px" width="100%">
                <tr>
                    <td>Chỉ số nhịp tim bình thường là dao động trong khoảng 60 nhịp đến 100 nhịp.<br>
                    Nhịp tim càng thấp thì chứng tỏ tim hoạt động càng hiệu quả và chức năng tim khỏe mạnh.<br>
                    Nhịp tim của vận động viên dao động trong khoảng 40 nhịp/ phút.<br>
                    Chỉ số huyết áp bình thường là dao động trong khoảng 90/60mmHg đến 140/90mmHg.<br>
                    Chỉ số huyết áp thấp là khi huyết áp tối đa < 90 hoặc huyết áp tối thiểu < 60.<br>
                    Chỉ số huyết áp là cao khi huyết áp tối đa > 140 hoặc huyết áp tối thiểu > 90.
                </td>
                    
                </tr>
                 </table>
                 <br>
             </br>
               

  <table border="1px" cellspacing="0px" width="100%">
    
                <tr bgcolor="yellow">
                    <td style="color:#cd201f">Bảng chỉ số nhịp tim và huyết áp chuẩn được tính theo tiêu chuẩn của Tổ chức y tế thế giới - WTO như sau :
                </td>
                    
                </tr>

               </table>
               <br>
           </br>
           

    <table border="1px" cellspacing="0px" width="100%">
    <tr> 
        <th rowspan="2" bgcolor="blue" style="color:#fffa37">Độ tuổi</th>
        <th colspan="2" bgcolor="blue" style="color:#fffa37">Nam</th>
        <th colspan="2" bgcolor="blue" style="color:#fffa37">Nữ</th>
    </tr>
    <tr> 
        
        <th style="color:#FF3333">Nhịp tim tối thiểu</th>
        <th style="color:#FF3333">Nhịp tim tối đa</th>
        <th style="color:#FF3333">Nhịp tim tối thiểu</th>
        <th style="color:#FF3333">Nhịp tim tối đa</th>
    </tr>
    <tr>
        <td bgcolor="blue" style="color:#fffa37"> < 1 </td>
        <td >102</td>
        <td>155</td>
        <td>104</td>
        <td>156</td>
       
    </tr>
     <tr>
        <td bgcolor="blue" style="color:#fffa37">1</td>
        <td>95</td>
        <td>137</td>
        <td>95</td>
        <td>139</td>
       
    </tr>
     <tr>
        <td bgcolor="blue" style="color:#fffa37">2-3</td>
        <td>85</td>
        <td>124</td>
        <td>88</td>
        <td>125</td>
       
    </tr>
     <tr>
        <td bgcolor="blue" style="color:#fffa37">4-5</td>
        <td>74</td>
        <td>112</td>
        <td>76</td>
        <td>117</td>
       
    </tr>
     <tr>
        <td bgcolor="blue" style="color:#fffa37">6-8</td>
        <td>66</td>
        <td>105</td>
        <td>69</td>
        <td>106</td>
       
    </tr>
     <tr>
        <td bgcolor="blue" style="color:#fffa37">9-11</td>
        <td>61</td>
        <td>97</td>
        <td>66</td>
        <td>103</td>
       
    </tr>
     <tr>
        <td bgcolor="blue" style="color:#fffa37">12-15</td>
        <td>57</td>
        <td>97</td>
        <td>60</td>
        <td>99</td>
       
    </tr>
	<tr>
        <td bgcolor="blue" style="color:#fffa37">16-19</td>
        <td >52</td>
        <td>92</td>
        <td>58</td>
        <td>99</td>
       
    </tr>
     <tr>
        <td bgcolor="blue" style="color:#fffa37">20-39</td>
        <td>52</td>
        <td>89</td>
        <td>57</td>
        <td>95</td>
       
    </tr>
     <tr>
        <td bgcolor="blue" style="color:#fffa37">40-59</td>
        <td>52</td>
        <td>90</td>
        <td>56</td>
        <td>92</td>
       
    </tr>
     <tr>
        <td bgcolor="blue" style="color:#fffa37">60-79</td>
        <td>50</td>
        <td>91</td>
        <td>56</td>
        <td>92</td>
       
    </tr>
     <tr>
        <td bgcolor="blue" style="color:#fffa37"> 80 < </td>
        <td>51</td>
        <td>94</td>
        <td>56</td>
        <td>93</td>
       
    </tr>
</table>
 <br>
           </br>
<table border="1px" cellspacing="0px" width="100%">
    <tr> 
        <th rowspan="2" bgcolor="blue" style="color:#fffa37">Độ tuổi</th>
        <th colspan="2" bgcolor="blue" style="color:#fffa37">Nam</th>
        <th colspan="2" bgcolor="blue" style="color:#fffa37">Nữ</th>
    </tr>
    <tr> 
        
        <th style="color:#FF3333">Huyết áp tối thiểu</th>
        <th style="color:#FF3333">Huyết áp tối đa</th>
        <th style="color:#FF3333">Huyết áp tối thiểu</th>
        <th style="color:#FF3333">Huyết áp tối đa</th>
    </tr>
    <tr>
        <td bgcolor="blue" style="color:#fffa37">15-19</td>
        <td >120</td>
        <td>70</td>
        <td>111</td>
        <td>67</td>
       
    </tr>
     <tr>
        <td bgcolor="blue" style="color:#fffa37">20-29</td>
        <td>124</td>
        <td>75</td>
        <td>114</td>
        <td>69</td>
       
    </tr>
     <tr>
        <td bgcolor="blue" style="color:#fffa37">30-39</td>
        <td>126</td>
        <td>79</td>
        <td>118</td>
        <td>73</td>
       
    </tr>
     <tr>
        <td bgcolor="blue" style="color:#fffa37">40-49</td>
        <td>130</td>
        <td>83</td>
        <td>126</td>
        <td>78</td>
       
    </tr>
     <tr>
        <td bgcolor="blue" style="color:#fffa37">50-59</td>
        <td>137</td>
        <td>85</td>
        <td>134</td>
        <td>81</td>
       
    </tr>
     <tr>
        <td bgcolor="blue" style="color:#fffa37">60-69</td>
        <td>143</td>
        <td>84</td>
        <td>139</td>
        <td>81</td>
       
    </tr>
     <tr>
        <td bgcolor="blue" style="color:#fffa37">70-79</td>
        <td>145</td>
        <td>82</td>
        <td>146</td>
        <td>79</td>
       
    </tr>
</table>
<body>
    <div style="text-align:center;"><b> </b><br>Đồ Thị Nhịp Tim & Huyết Áp </div>
    <div class="chart-container" position: relative; height:350px; width:100%">
        <canvas id="Chart" width="400" height="400"></canvas>
    </div>
<div>
  <table id="dataTable">
    <tr><th>Time</th><th>Nhịp Tim</th><th>Tâm Thu</th><th>Tâm Trương</th></tr>
  </table>
</div>
<br>
<br>  

<script>
//Graphs visit: https://www.chartjs.org
var ADCvalues = [];
var Tvalues = [];
var Hvalues = [];
var timeStamp = [];
function showGraph()
{
    var ctx = document.getElementById("Chart").getContext('2d');
    var Chart2 = new Chart(ctx, {
        type: 'line',
        data: {
            labels: timeStamp,  //Bottom Labeling
            datasets: [{
                label: "nhịp tim",
                fill: false,  //Try with true
                backgroundColor: 'rgba( 243,18, 156 , 1)', //Dot marker color
                borderColor: 'rgba( 243, 18, 156 , 1)', //Graph Line Color
                data: ADCvalues,
            },{
                label: "tâm trương",
                fill: false,  //Try with true
                backgroundColor: 'rgba( 243, 156, 18 , 1)', //Dot marker color
                borderColor: 'rgba( 243, 156, 18 , 1)', //Graph Line Color
                data: Tvalues,
            },
            {
                label: "tâm thu",
                fill: false,  //Try with true
                backgroundColor: 'rgba(156, 18, 243 , 1)', //Dot marker color
                borderColor: 'rgba(156, 18, 243 , 1)', //Graph Line Color
                data: Hvalues,
            }],
        },
        options: {
            title: {
                    display: true,
                    text: ""
                },
            maintainAspectRatio: false,
            elements: {
            line: {
                    tension: 0.5 //Smoothening (Curved) of data lines
                }
            },
            scales: {
                    yAxes: [{
                        ticks: {
                            beginAtZero:true
                        }
                    }]
            }
        }
    });

}

//On Page load show graphs
window.onload = function() {
  console.log(new Date().toLocaleTimeString());
};

//Ajax script to get ADC voltage at every 5 Seconds 
//Read This tutorial https://circuits4you.com/2018/02/04/esp8266-ajax-update-part-of-web-page-without-refreshing/

setInterval(function() {
  // Call a function repetatively with 5 Second interval
  getData();
}, 5000); //5000mSeconds update rate
 
function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
     //Push the data in array
  var time = new Date().toLocaleTimeString();
  var txt = this.responseText;
  var obj = JSON.parse(txt); //Ref: https://www.w3schools.com/js/js_json_parse.asp
      ADCvalues.push(obj.ADC);
      Tvalues.push(obj.Temperature);
      Hvalues.push(obj.Humidity);
      timeStamp.push(time);
      showGraph();  //Update Graphs
  //Update Data Table
    var table = document.getElementById("dataTable");
    var row = table.insertRow(1); //Add after headings
    var cell1 = row.insertCell(0);
    var cell2 = row.insertCell(1);
    var cell3 = row.insertCell(2);
    var cell4 = row.insertCell(3);
    cell1.innerHTML = time;
    cell2.innerHTML = obj.ADC;
    cell3.innerHTML = obj.Temperature;
    cell4.innerHTML = obj.Humidity;
    }
  };
  xhttp.open("GET", "readADC", true); //Handle readADC server on ESP8266
  xhttp.send();
}
    
</script>
</body>

</html>

)=====";
