import tkinter as tk 
  
class PolygonCreator: 
    def init(self): 
        self.window = tk.Tk() 
        self.canvas = tk.Canvas(self.window, width=500, height=500) 
        self.canvas.pack() 
        self.points = [] 
        self.canvas.bind("<Button-1>", self.add_point) 
        self.canvas.bind("<Button-3>", self.finish_polygon) 
        self.window.mainloop() 
  
    def add_point(self, event): 
        self.points.append((event.x, event.y)) 
        self.canvas.create_oval(event.x-2, event.y-2, event.x+2, event.y+2, fill="black") 
  
    def finish_polygon(self, event): 
        if len(self.points) > 2: 
            self.canvas.create_polygon(self.points, fill="", outline="black") 
            f = open("input.txt", "w") 
            #write the points to a file 
            f.write(str(len(self.points))+" 0\n") 
            for point in self.points: 
                f.write(str(point[0])+" "+str(-point[1])+"\n") 
            f.close() 
  
        self.points = [] 
  
if name == "main": 
     app = PolygonCreator()