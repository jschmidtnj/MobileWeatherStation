window.onload = function() {
        var dataPoints = [];
	 
        function getDataPointsFromCSV(csv, column) {
            var dataPoints = csvLines = points = [];
            csvLines = csv.split(/[\r?\n|\r|\n]+/);
            for (var i = 0; i < csvLines.length; i++)
                if (csvLines[i].length > 0) {
                    points = csvLines[i].split(",");
                    var y_axis_data = (points[column]);
                    if (y_axis_data == "NaN"){
                    	y_axis_data = "0"
                    }
                    dataPoints.push({
                        y_axis: parseFloat((y_axis_data).slice(1, (points[1]).length - 1)),
                        x_axis: parseFloat(i)
                    });
                }
            return dataPoints;
        }
	
	jQuery.get("https://rawgit.com/jschmidtnj/MobileWeatherStation/master/data/current_data_file.csv?xstart=5&ystart=10&length=10&type=csv", function(data) {
		var column = 0;
		var windspeed_chart = new tauCharts.Chart({
			data: getDataPointsFromCSV(data, column),           
            y: 'y_axis',
            x: 'x_axis',
            type: 'line',
            guide:{
              padding:{l:70, t:10, b:70,r:10},
              showGridLines:'xy',
              y:{
                label:{
                  text:'WindSpeed (mph)',
                  padding:-15
                }
              },
              x:{
                label:'Count',
              }
            },
            plugins: [
		        tauCharts.api.plugins.get('tooltip')()
		    ]
        });
        windspeed_chart.renderTo('#windspeed');
	});

  jQuery.get("https://rawgit.com/jschmidtnj/MobileWeatherStation/master/data/current_data_file.csv?xstart=5&ystart=10&length=10&type=csv", function(data) {
    var column = 1;
    var humidity_chart = new tauCharts.Chart({
      data: getDataPointsFromCSV(data, column),           
            y: 'y_axis',
            x: 'x_axis',
            type: 'line',
            guide:{
              padding:{l:70, t:10, b:70,r:10},
              showGridLines:'xy',
              y:{
                label:{
                  text:'humidity',
                  padding:-15
                }
              },
              x:{
                label:'Count',
              }
            },
            plugins: [
            tauCharts.api.plugins.get('tooltip')()
        ]
        });
        humidity_chart.renderTo('#humidity');
  });

  jQuery.get("https://rawgit.com/jschmidtnj/MobileWeatherStation/master/data/current_data_file.csv?xstart=5&ystart=10&length=10&type=csv", function(data) {
    var column = 2;
    var temp_1_chart = new tauCharts.Chart({
      data: getDataPointsFromCSV(data, column),           
            y: 'y_axis',
            x: 'x_axis',
            type: 'line',
            guide:{
              padding:{l:70, t:10, b:70,r:10},
              showGridLines:'xy',
              y:{
                label:{
                  text:'temp_1 (F)',
                  padding:-15
                }
              },
              x:{
                label:'Count',
              }
            },
            plugins: [
            tauCharts.api.plugins.get('tooltip')()
        ]
        });
        temp_1_chart.renderTo('#temp_1');
  });

  jQuery.get("https://rawgit.com/jschmidtnj/MobileWeatherStation/master/data/current_data_file.csv?xstart=5&ystart=10&length=10&type=csv", function(data) {
    var column = 3;
    var temp_2_chart = new tauCharts.Chart({
      data: getDataPointsFromCSV(data, column),           
            y: 'y_axis',
            x: 'x_axis',
            type: 'line',
            guide:{
              padding:{l:70, t:10, b:70,r:10},
              showGridLines:'xy',
              y:{
                label:{
                  text:'Temp 2 (F)',
                  padding:-15
                }
              },
              x:{
                label:'Count',
              }
            },
            plugins: [
            tauCharts.api.plugins.get('tooltip')()
        ]
        });
        temp_2_chart.renderTo('#temp_2');
  });

  jQuery.get("https://rawgit.com/jschmidtnj/MobileWeatherStation/master/data/current_data_file.csv?xstart=5&ystart=10&length=10&type=csv", function(data) {
    var column = 4;
    var avg_temp_chart = new tauCharts.Chart({
      data: getDataPointsFromCSV(data, column),           
            y: 'y_axis',
            x: 'x_axis',
            type: 'line',
            guide:{
              padding:{l:70, t:10, b:70,r:10},
              showGridLines:'xy',
              y:{
                label:{
                  text:'avg_temp (F)',
                  padding:-15
                }
              },
              x:{
                label:'Count',
              }
            },
            plugins: [
            tauCharts.api.plugins.get('tooltip')()
        ]
        });
        avg_temp_chart.renderTo('#avg_temp');
  });

  jQuery.get("https://rawgit.com/jschmidtnj/MobileWeatherStation/master/data/current_data_file.csv?xstart=5&ystart=10&length=10&type=csv", function(data) {
    var column = 5;
    var altitude_chart = new tauCharts.Chart({
      data: getDataPointsFromCSV(data, column),           
            y: 'y_axis',
            x: 'x_axis',
            type: 'line',
            guide:{
              padding:{l:70, t:10, b:70,r:10},
              showGridLines:'xy',
              y:{
                label:{
                  text:'altitude (m)',
                  padding:-15
                }
              },
              x:{
                label:'Count',
              }
            },
            plugins: [
            tauCharts.api.plugins.get('tooltip')()
        ]
        });
        altitude_chart.renderTo('#altitude');
  });

  jQuery.get("https://rawgit.com/jschmidtnj/MobileWeatherStation/master/data/current_data_file.csv?xstart=5&ystart=10&length=10&type=csv", function(data) {
    var column = 5;
    var pressure_chart = new tauCharts.Chart({
      data: getDataPointsFromCSV(data, column),           
            y: 'y_axis',
            x: 'x_axis',
            type: 'line',
            guide:{
              padding:{l:70, t:10, b:70,r:10},
              showGridLines:'xy',
              y:{
                label:{
                  text:'pressure (Pa)',
                  padding:-15
                }
              },
              x:{
                label:'Count',
              }
            },
            plugins: [
            tauCharts.api.plugins.get('tooltip')()
        ]
        });
        pressure_chart.renderTo('#pressure');
    });
  }

$(document).ready(function(){
	$(window).on("scroll",function(){
  	var wn = $(window).scrollTop();
    if(wn > 1000){
    	$(".navbar").css("background","rgba(255,255,255,.5)");
    }
    else{
    	$(".navbar").css("background","rgba(255,255,255,1)");
    }
  });
});

const scriptURL = 'https://script.google.com/macros/s/AKfycbxt5aLzoW9YpmBfTYdsXPsBn3kaAtLz996laDlNEiSxl-P8-NI/exec'
  const form = document.forms["submit-to-google-sheet"]

  form.addEventListener('submit', e => {
    e.preventDefault()
    fetch(scriptURL, { method: 'POST', body: new FormData(form)})
      .then(response => console.log('Success!', response))
      .catch(error => console.error('Error!', error.message))
  })