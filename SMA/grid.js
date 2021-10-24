
class Cell{
    constructor(i, j, type){
        this.i = i;
        this.j = j;
        this.type = type;
        this.g = 0;
        this.f = 0;
        this.h = 0;
        this.neighbors = [];
        this.previous = undefined;
    }

    addNeighbors(){
        var x = this.i;
        var y = this.j;
        if(x < col -1)
            this.neighbors.push(getCell(x+1, y));
        if(x > 0)
            this.neighbors.push(getCell(x-1, y));
        if(y < row -1)
            this.neighbors.push(getCell(x, y+1));
        if(y > 0)
            this.neighbors.push(getCell(x, y-1));
    }

    drawCell(){
        var x = this.i*res;
        var y = this.j*res;
        stroke(0)
        switch (this.type) {
            case 0:
                fill(80,80,80);
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