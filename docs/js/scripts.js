$(document).ready(function(){
	$(window).on("scroll",function(){
  	var wn = $(window).scrollTop();
    if(wn > 120){
    	$(".navbar").css("background","rgba(255,255,255,.5)");
    }
    else{
    	$(".navbar").css("background","rgba(255,255,255,1)");
    }
  });
});

$(document).ready(function(){       
			var scroll_start = 0;
			var startchange = $('#startchange');
			var offset = startchange.offset();
			if (startchange.length){
				$(document).scroll(function() { 
					scroll_start = $(this).scrollTop();
					if(scroll_start > offset.top) {
						$(".navbar-default").css('background-color', '#f0f0f0');
					} else {
						$('.navbar-default').css('background-color', 'transparent');
					}
				});
			}
		});