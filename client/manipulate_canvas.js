// Constructeur de la classe ProcessingImage
function ProcessingImage(src) {

    this.img = new Image();
    this.img.src = src;

    var myImage = this;

    this.img.onload = function() {
        myImage.w = this.width;
        myImage.h = this.height;

        var canvas = document.getElementById('canvas');

        myImage.initialx = canvas.width/2 - this.width/2;
        myImage.initialy = canvas.height/2 - this.height/2;
        myImage.x = myImage.initialx;
        myImage.y = myImage.initialy;
    }
}

//Dessine l'image
ProcessingImage.prototype.draw = function(ctx) {
    var locx = this.x;
    var locy = this.y;
    ctx.drawImage(this.img,locx,locy);
}

// Determine si un point est dans l'image
ProcessingImage.prototype.contains = function(mx, my, scale) {

  return  (this.x <= mx) && (this.x + (this.w) >= mx) &&
          (this.y <= my) && (this.y + (this.h) >= my);
}


//Constructeur de la baseline
function Baseline(lines) {
    this.lines = lines;
    this.visible = false;

}

Baseline.prototype.draw = function(ctx, image){  
    if(this.visible)
    {
        for (index = 0; index < this.lines.length; index++) {
            ctx.beginPath();
            ctx.moveTo(image.x,image.y + this.lines[index]);
            ctx.lineTo(image.x + image.w,image.y + this.lines[index]);
            ctx.strokeStyle = '#2ecc71';
            ctx.stroke();
        }   
    }
    
}

function CanvasState(canvas, image, baseline) {
  
    this.canvas = canvas;
    this.width = canvas.width;
    this.height = canvas.height;
    this.ctx = canvas.getContext('2d');

    this.image = image;
    this.baseline = baseline;

    this.dragging = false;

    this.scale = 1.0;

    this.panX = 0;
    this.panY = 0;

    //Coordonnées de la selection sur l'image
    this.dragoffx = 0;
    this.dragoffy = 0;

    var myState = this;

    canvas.addEventListener('selectstart', function(e) { e.preventDefault(); return false; }, false);
  
    canvas.addEventListener('mousedown', function(e) {

        var mouse = myState.getMouse(e);
        var mx = mouse.x;
        var my = mouse.y;

        var image = myState.image;

        
        if (image.contains(mx, my, myState.scale)) {
        
            myState.dragoffx = mx - image.x;
            myState.dragoffy = my - image.y;             
            myState.dragging = true;
            return;
          }
    }, true);

    canvas.addEventListener('mousemove', function(e) {
        if (myState.dragging){
            var mouse = myState.getMouse(e);
            image.x = (mouse.x) - myState.dragoffx;
            image.y = (mouse.y) - myState.dragoffy; 
        }
    }, true);

    canvas.addEventListener('mouseup', function(e) {
        myState.dragging = false;
    }, true);

    document.getElementById('zoom-in').addEventListener('click', function(e){
        myState.scale += 0.1;
    }, true);

    document.getElementById('zoom-out').addEventListener('click', function(e){
        myState.scale -= 0.1;
    }, true);
    
    document.getElementById('zoom-reset').addEventListener('click', function(e){
        myState.scale = 1;
        myState.image.x = myState.image.initialx;
        myState.image.y = myState.image.initialy;
    }, true);

    document.getElementById('baseline').addEventListener('change', function(e){
        if(this.checked){
            myState.baseline.visible = true;
        }
        else{
            myState.baseline.visible = false;
        }     
    }, true);
  
    this.interval = 30;
    setInterval(function() { myState.draw(); }, myState.interval);
}


// Efface le canvas pour redessiner
CanvasState.prototype.clear = function() {
  this.ctx.clearRect(0, 0, this.width, this.height);
}

// Dessine le canvas avec ces éléments
CanvasState.prototype.draw = function() {
  if (!this.valid) {
    var ctx = this.ctx;

    var newWidth = this.width * this.scale;
    var newHeight = this.height * this.scale;
    this.panX = -((newWidth-this.width)/2);
    this.panY = -((newHeight-this.height)/2);
    
    this.clear();

    ctx.save();

    ctx.translate(this.panX, this.panY);


    ctx.scale(this.scale, this.scale);
    
    this.image.draw(ctx);

    this.baseline.draw(ctx, this.image);
    ctx.restore();

  }
}

// Retourne les coordonnées de la souris
CanvasState.prototype.getMouse = function(e) {
    var rect = this.canvas.getBoundingClientRect();
    var mx = Math.floor((e.clientX-rect.left)/(rect.right-rect.left)*this.canvas.width);
    var my = Math.floor((e.clientY-rect.top)/(rect.bottom-rect.top)*this.canvas.height);

    var mouseXT = parseInt((mx - this.panX) / this.scale);
    var mouseYT = parseInt((my - this.panY) / this.scale);

    return {x: mouseXT, y: mouseYT};
}

function init(src) {
    var image = new ProcessingImage(src);
    var baseline = new Baseline([33, 94, 155]);
    var s = new CanvasState(document.getElementById('canvas'), image, baseline);
}