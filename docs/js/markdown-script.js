window.onload = function(){
jQuery.get("https://rawgit.com/jschmidtnj/MobileWeatherStation/master/", function(data) {
    var text = document.getElementById('sourceTA').value,
        target = document.getElementById('markdown'),
        converter = new showdown.Converter(),
        html = converter.makeHtml(text);

      target.innerHTML = html;
});
