/*
	Author: Dung Harry
	Date created: 6th, September 2015
	JDK version 1.8 update 60

	Description: this is an example about how to get text in Swing with Java programming language

	Compile and run:
		javac GetTextTest.java
		java GetTextTest
*/

import java.awt.Button;
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;

public class GetTextTest {
	private JTextField text;
	private JPasswordField password;
	private JButton button;
	private JPanel mainPanel;
	private JPanel firstTextPanel;
	private JPanel secondTextPanel;
	private JPanel buttonPanel;
	private JPanel labelPanel;
	private JFrame frame;
	private JLabel label;
	
	public GetTextTest() {
		this.frame = new JFrame("Copyright © BE Studio 2015 - Get text example");
		this.mainPanel = new JPanel();
		
		this.frame.setSize(500, 300);
		this.frame.setResizable(false);
		this.frame.setLocationRelativeTo(null);
		this.frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		this.text = new JTextField("");
		this.text.setColumns(20);
		this.text.setEditable(true);
		this.text.setFont(new Font("Times New Roman", Font.PLAIN, 20));
		
		this.password = new JPasswordField("");
		this.password.setColumns(20);
		this.password.setEditable(true);
		this.password.setFont(new Font("Times New Roman", Font.PLAIN, 20));
		
		this.button = new JButton("Click here");
		
		this.label = new JLabel("Information form");
		this.label.setFont(new Font("Times New Roman", Font.BOLD, 40));
		
		this.button.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				System.out.println("text: " + text.getText());
				System.out.println("password: " + password.getText() + "\n");
			}
			
		});
		
		this.mainPanel.setLayout(new GridLayout(4, 1));
		this.mainPanel.setSize(500, 300);
		
		this.firstTextPanel = new JPanel();
		this.firstTextPanel.setLayout(new FlowLayout(FlowLayout.LEFT));
		
		this.firstTextPanel.add(this.text);
		
		this.secondTextPanel = new JPanel();
		this.secondTextPanel.setLayout(new FlowLayout(FlowLayout.LEFT));
		
		this.secondTextPanel.add(this.password);
		
		this.buttonPanel = new JPanel();
		this.buttonPanel.setLayout(new FlowLayout(FlowLayout.CENTER));
		
		this.buttonPanel.add(this.button);
		
		this.labelPanel = new JPanel();
		this.labelPanel.setLayout(new FlowLayout(FlowLayout.CENTER));
		
		this.labelPanel.add(this.label);
				
		this.mainPanel.add(this.labelPanel);
		this.mainPanel.add(this.firstTextPanel);
		this.mainPanel.add(this.secondTextPanel);
		this.mainPanel.add(this.buttonPanel);
		
		this.frame.add(this.mainPanel);
		this.frame.setVisible(true);
	}
	
	public static void main(String args[]) {
		GetTextTest obj = new GetTextTest();
	}
}
