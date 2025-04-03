package com.example.demo;

import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.List;

@RestController
public class RectangleController {
    List<Rectangle> rectangles = new ArrayList<>();

    @GetMapping("rectangle")
    public Rectangle getRectangle() {
        Rectangle rectangle = new Rectangle(23, 65, 100, 213, "red");
        return rectangle;
    }

    @PostMapping("add")
    public int addRectangle(@RequestBody Rectangle rectangle){
        rectangles.add(rectangle);
        return rectangles.size();
    }

    @GetMapping("listRectangle")
    public List<Rectangle> getRectangles() {
        return rectangles;
    }

    @GetMapping("rectangle/{index}")
    public Rectangle getRectangle(@PathVariable Long index){
        return rectangles.get(index.intValue());
    }

    @GetMapping("toSvg")
    public String toSvg(){
        StringBuilder result = new StringBuilder();
        result.append("<svg width=\"320\" height=\"130\">");

        for(Rectangle rectangle : rectangles){
            result.append(String.format("<rect width=\"%d\" height=\"%d\" x=\"%d\" y=\"%d\" fill=\"%s\"/>",
                    rectangle.getWidth(), rectangle.getHeight(), rectangle.getX(), rectangle.getY(), rectangle.getColor()));
        }

        result.append("</svg>");
        return result.toString();
    }

    @PutMapping("modifyRec/{index}")
    public void modifyRectangle(@PathVariable Long index, @RequestBody Rectangle rectangle){
        rectangles.set(index.intValue(), rectangle);
    }

    @DeleteMapping("deleteRec/{index}")
    public void deleteRec(@PathVariable Long index){
        rectangles.remove(index.intValue());
    }
}