package com.example.demo;

import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.multipart.MultipartFile;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Base64;

@Controller
public class ImageFormController {

    @GetMapping("/")
    public String showIndexPage() {
        return "index";
    }

//    // zad 8b
//    @PostMapping("/imageform/upload")
//    public String uploadImage(@RequestParam("image") MultipartFile file, Model model) {
//
//        try {
//            byte[] bytes = file.getBytes();
//
//            String base64Image = Base64.getEncoder().encodeToString(bytes);
//
//            model.addAttribute("image", base64Image);
//            return "image";
//        } catch (IOException e) {
//            throw new RuntimeException(e);
//        }
//    }

    // zad 9
    @PostMapping("/imageform/upload")
    public String uploadImage(@RequestParam("image") MultipartFile file, Model model,
                              @RequestParam("brightness") int brightness) {

        try {
            BufferedImage image = ImageIO.read(file.getInputStream());
            BufferedImage changedImage = changeBrightness(image, brightness);

            ByteArrayOutputStream bytes = new ByteArrayOutputStream();
            ImageIO.write(changedImage, "png", bytes);
            String base64Image = Base64.getEncoder().encodeToString(bytes.toByteArray());

            model.addAttribute("image", base64Image);
            return "image";
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public BufferedImage changeBrightness(BufferedImage image, int factor) {
        for(int x = 0; x < image.getWidth(); x++) {
            for(int y = 0; y < image.getHeight(); y++) {
                int pixel = image.getRGB(x, y);
                pixel = brightenPixel(pixel, factor);
                image.setRGB(x, y, pixel);
            }
        }
        return image;
    }

    private int brightenPixel(int pixel, int factor) {
        int mask = 255;
        int blue = pixel & mask;
        int green = (pixel >> 8) & mask;
        int red = (pixel >> 16) & mask;
        blue = brightenPixelPart(blue, factor);
        green = brightenPixelPart(green, factor);
        red = brightenPixelPart(red, factor);

        return blue + (green << 8) + (red << 16);
    }

    private int brightenPixelPart(int color, int factor){
        color += factor;
        if(color > 255) {
            return 255;
        } else{
            return color;
        }
    }
}