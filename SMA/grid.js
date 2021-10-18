
class Cell{
    constructor(i, j, type){
        this.i = i;
        this.j = j;
        this.type = type;
    }

    drawCell(){
        var x = this.i*res;
        var y = this.j*res;
        stroke(0)
        switch (this.type) {
            case 0:
                fill(128,0,128);
                break;
            case 1:
                fill(0);
                break;
            case 2:
                fill(0,255,0);
                break;
        
            default:
                fill(255);
                break;
        }
        rect(x,y,res,res);

    }

}