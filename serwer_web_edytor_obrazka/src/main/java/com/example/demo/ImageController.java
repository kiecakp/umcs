package com.example.demo;

import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Base64;

@RestController
public class ImageController {

    @GetMapping("modifyBrightnessBase64")
    public String modifyBrightnessBase64(@RequestParam int brightness){
        // sciezka do pliku png
        String imagePath = "C:\\Users\\patek\\Documents\\GitHub\\serwer_web\\src\\main\\imageFolder\\image.png";

        File file = new File(imagePath);
        try {
            BufferedImage image = ImageIO.read(file);
            BufferedImage changedImage = changeBrightness(image, brightness);

            ByteArrayOutputStream bytes = new ByteArrayOutputStream();
            ImageIO.write(changedImage, "png", bytes);

            String base64Image = Base64.getEncoder().encodeToString(bytes.toByteArray());
            return base64Image;
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    @GetMapping("modifyBrightnessPhoto")
    public ResponseEntity<byte[]> modifyBrightnessPhoto(@RequestParam int brightness){
        // sciezka do pliku png
        String imagePath = "C:\\Users\\patek\\Documents\\GitHub\\serwer_web\\src\\main\\imageFolder\\image.png";

        File file = new File(imagePath);
        try {
            BufferedImage image = ImageIO.read(file);
            BufferedImage changedImage = changeBrightness(image, brightness);

            ByteArrayOutputStream bytes = new ByteArrayOutputStream();
            ImageIO.write(changedImage, "png", bytes);

            return ResponseEntity.ok().contentType(MediaType.IMAGE_JPEG).body(bytes.toByteArray());
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

// pomocnicze kody testowe

//    // testowy kod do dekodowania napisu z linku
//    @GetMapping("testBase64")
//    public String base64Test(@RequestParam String base64Text){
//        /* kod base64 do testow:
//            YWxhIG1hIGtvdGEgemJ5c3prYQ==
//         */
//        byte[] decoded = Base64.getDecoder().decode(base64Text);
//        String result = new String(decoded);
//        return result;
//    }
//
//    // testowy kod wyswietlajacy kod base64 na serwerze
//    @GetMapping("testBase64Photo")
//    public String base64Photo(){
//        String imagePath = "C:\Users\patek\Documents\GitHub\serwer_web\src\main\imageFolder\image.png";
//
//        try {
//            byte[] imageBytes = Files.readAllBytes(Path.of(imagePath));
//            String base64Image = Base64.getEncoder().encodeToString(imageBytes);
//
//            return base64Image;
//        } catch (IOException e) {
//            throw new RuntimeException(e);
//        }
//    }
//
//    // testowy kod wyswietlajacy zdj na serwerze
//    @GetMapping("testPhoto")
//    public ResponseEntity<byte[]> photo() throws IOException {
//        String imagePath = "C:\Users\patek\Documents\GitHub\serwer_web\src\main\imageFolder\image.png";
//
//        try {
//            byte[] imageBytes = Files.readAllBytes(Path.of(imagePath));
//            return ResponseEntity.ok().contentType(MediaType.IMAGE_JPEG).body(imageBytes);
//
//        } catch (IOException e) {
//            throw new RuntimeException(e);
//        }
//    }

}