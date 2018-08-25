import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.Scanner;
import javax.swing.*;
import javax.swing.JFileChooser;
import javax.imageio.*;
import java.awt.image.BufferedImage;

public class hars extends JFrame implements ActionListener{
	private Container c;
	private JButton fBtn, mBtn;
	private JTextField ftf;
	private JLabel sl;
	private File fi, fo;
	private JFileChooser fc;
	private int result;
	private String fip, btn;
	private Cursor cur=new Cursor(Cursor.HAND_CURSOR);
	private BufferedImage img;
	private FileWriter fw;

	hars(){
		setTitle("HARS");
		setBounds(100, 100, 500, 500);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setVisible(true);

		c = this.getContentPane();
		c.setLayout(null);
		c.setBackground(Color.GREEN);

		fBtn = new JButton("Get");
		fBtn.setBounds(10, 100, 100, 30);
		fBtn.setCursor(cur);
		fBtn.addActionListener(this);
		add(fBtn);

		ftf = new JTextField();
		ftf.setBounds(10, 150, 300, 20);
		ftf.setEditable(false);
		add(ftf);

		mBtn = new JButton("Make");
		mBtn.setBounds(10, 200, 100, 30);
		mBtn.setCursor(cur);
		mBtn.addActionListener(this);
		mBtn.setEnabled(false);
		add(mBtn);

		sl = new JLabel();
		sl.setBounds(150, 200, 300, 50);
		add(sl);
	}
	public static void main(String[] args){
		new hars();
	}
	private void delay(int ms){
		try{
			Thread.sleep(ms);
		}catch(Exception ex){}
	}
	public static boolean check(int r, int g, int b){
		if((r<128 && g<128 && b<128) && (Math.abs(r-g))<64 && Math.abs(r-b)<64 && Math.abs(g-b)<64)
			return true;
		return false;
	}

	private void printFile(int x, int y, int r, int g, int b){
		try{
			BufferedWriter writer = new BufferedWriter(new FileWriter("col.txt", true));
			String str = x + " " + y + " " + r + " " + g + " " + b + " ";
			writer.append(str);
			writer.close();
		}catch(Exception ex){
			System.out.println("printFile Error");
		}
	}

	@Override
	public void actionPerformed(ActionEvent e){
		btn = e.getActionCommand();
		if(btn.equals("Get")){
			fc = new JFileChooser();
			fc.setCurrentDirectory(new File(System.getProperty("user.dir")));
			result = fc.showOpenDialog(this);
			if(result == JFileChooser.APPROVE_OPTION){
				fi = new File(fc.getSelectedFile().getAbsolutePath());
				ftf.setText(fi.toString());
				mBtn.setEnabled(true);
			}
		}
		if(btn.equals("Make")){
			System.out.println("GOTCHA!");
			try{
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

//						printFile(i, j, r, g , b);

						if(check(r,g,b)){
							img.setRGB(i,j,0);
						}else{
							img.setRGB(i,j,0xffffff);
						}
					}
				}
				ImageIO.write(img,"jpeg",new File("./op.jpeg"));

			}catch(Exception ex) {
				System.out.println("ERROR!");
			}

		}
	}
}
