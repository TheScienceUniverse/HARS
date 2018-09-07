import java.io.*;
import java.util.Scanner;
import javax.imageio.*;
import java.awt.image.BufferedImage;

public class filter {
	filter() {
		
	}
	public static boolean check(int r, int g, int b){
		if((r<128 && g<128 && b<128) && (Math.abs(r-g))<64 && Math.abs(r-b)<64 && Math.abs(g-b)<64)
			return true;
		return false;
	}
	public static void main(String[] args) {
		BufferedImage img = null;
		try {
			File fi = new File(args[0]);
			img = ImageIO.read(fi);
			int w = img.getWidth();
			int h = img.getHeight();
			int col, r, g, b;
			for(int i=0; i<w; i++){
				for(int j=0; j<h; j++){
					col = img.getRGB(i,j);
					r = (col>>16) & 0xff;
					g = (col>>8) & 0xff;
					b = col & 0xff;
					if(check(r,g,b)){
						img.setRGB(i,j,0);
					}else{
						img.setRGB(i,j,0xffffff);
					}
				}
			}
			ImageIO.write(img,"JPEG",new File("./ip.jpeg"));
		} catch(Exception e) {
			System.out.println("Error: " + e);
		}
	}
}
