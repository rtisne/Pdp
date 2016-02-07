// Constructeur de la classe ProcessingImage
function ProcessingImage(src) {

    this.img = new Image();
    this.img.src = src;

    var that = this;

    this.img.onload = function() {
        that.w = this.width;
        that.h = this.height;

        var canvas = document.getElementById('canvas');

        that.x = canvas.width/2 - this.width/2;
        that.y = canvas.height/2 - this.height/2;
    }
}

//Dessine l'image
ProcessingImage.prototype.draw = function(ctx) {
    var locx = this.x;
    var locy = this.y;
    ctx.drawImage(this.img,locx,locy);
}

// Determine si un point est dans l'image
ProcessingImage.prototype.contains = function(mx, my) {

  return  (this.x <= mx) && (this.x + this.w >= mx) &&
          (this.y <= my) && (this.y + this.h >= my);
}

function CanvasState(canvas, image) {
  
    this.canvas = canvas;
    this.width = canvas.width;
    this.height = canvas.height;
    this.ctx = canvas.getContext('2d');

    this.image = image;

    this.dragging = false;

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
        
        if (image.contains(mx, my)) {
        
            myState.dragoffx = mx - image.x;
            myState.dragoffy = my - image.y;
            myState.dragging = true;
            return;
          }
    }, true);

    canvas.addEventListener('mousemove', function(e) {
        if (myState.dragging){
            var mouse = myState.getMouse(e);
            image.x = mouse.x - myState.dragoffx;
            image.y = mouse.y - myState.dragoffy; 
        }
    }, true);

    canvas.addEventListener('mouseup', function(e) {
        myState.dragging = false;
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

    this.clear();
    
    this.image.draw(ctx);
  }
}

// Retourne les coordonnées de la souris
CanvasState.prototype.getMouse = function(e) {
    var rect = this.canvas.getBoundingClientRect();
    mx = Math.floor((e.clientX-rect.left)/(rect.right-rect.left)*this.canvas.width);
    my = Math.floor((e.clientY-rect.top)/(rect.bottom-rect.top)*this.canvas.height);
    return {x: mx, y: my};
}

function init(src) {
    var image = new ProcessingImage(src);
    var s = new CanvasState(document.getElementById('canvas'), image);
}