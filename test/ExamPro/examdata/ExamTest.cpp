import java.io.*;
import java.util.Random;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;
import javafx.stage.Modality;
import javafx.stage.Screen;
import javafx.scene.control.Label;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.RadioButton;
import javafx.scene.control.ToggleGroup;
import javafx.scene.paint.Color;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.Background;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;

public class ExamTest extends Application
{   public static final int WIDTH = 700;
	public static final int HEIGHT = 200;  	
	private Button beginBtn = new Button(" 开始测试 ");
    private BorderPane centerPane = new BorderPane();
    private TextArea ta = new TextArea("  题目区域");
    private ToggleGroup tg = new ToggleGroup();
    private RadioButton rba = new RadioButton("A");
    private RadioButton rbb = new RadioButton("B");
    private RadioButton rbc = new RadioButton("C");
    private RadioButton rbd = new RadioButton("D");
    private Question myques = null;
    private int []topic;
    private int quesCount = 0, scoreFS = 0;
    private StringBuffer scoreMessage = new StringBuffer();
    
    public static void main(String[] args) 
    {   launch(args);
    }

    public void start(Stage stage) 
    {   ta.setEditable(false);
        rba.setToggleGroup(tg);  
        rbb.setToggleGroup(tg);
        rbc.setToggleGroup(tg);
        rbd.setToggleGroup(tg);
        HBox bottomHB = new HBox();
	    bottomHB.setSpacing(10);
	    bottomHB.getChildren().addAll(rba, rbb, rbc, rbd);
	    bottomHB.setAlignment(Pos.CENTER);
        
        centerPane.setCenter(ta);
        centerPane.setBottom(bottomHB);
        centerPane.setMargin(bottomHB, new Insets(10, 0, 5, 0));
        
        
        BorderPane bp = new BorderPane();
        bp.setCenter(centerPane);
        bp.setBottom(beginBtn);
        bp.setMargin(beginBtn, new Insets(5, 0, 10, 0));
        bp.setAlignment(beginBtn, Pos.CENTER);
        
        beginBtn.setOnAction(new ButtonHandler());        
            
        getRandomTopic();
	            
        Scene scene = new Scene(bp, WIDTH, HEIGHT);
        stage.setTitle(" 诗词大会");
        stage.setScene(scene);
        stage.show();
  
    }      

    private class ButtonHandler implements EventHandler<ActionEvent>
	{	public void handle(ActionEvent e) 
	    {	Button b = (Button) e.getSource();
            if(b.equals(beginBtn))
            {   beginBtn.setText("下一题");
                getOneQuestion();
            }
		}
	}

    public void getOneQuestion()
    {   FileInputStream fi = null;
        ObjectInputStream si = null;
               
        if(quesCount >= 1)
            makeScoreMessage();
        
        myques = null;
                        
        try 
        {   fi = new FileInputStream("examdata.ser");
            si = new ObjectInputStream(fi);
            quesCount ++;
            System.out.println(""+quesCount);
            if(quesCount == 11)
            {   scoreMessage.append("  ------------------------------------------------------------------------------------------------\n");
                scoreMessage.append("       最终成绩："+scoreFS);
                showFinnallyScore();
                myques = null;
                scoreMessage = new StringBuffer();
                scoreFS = 0;
                quesCount = 0;
                getRandomTopic();
                ta.setText("  题目区域");
                rba.setText("A ");
                rbb.setText("B ");
                rbc.setText("C ");
                rbd.setText("D ");
                beginBtn.setText("重新开始");
                rba.setSelected(false); rbb.setSelected(false); 
                rbc.setSelected(false); rbd.setSelected(false);
                return;
            }
            for(int i = 0; i < topic[quesCount-1]; i++)
                myques = (Question) si.readObject();
           
                
            ta.setText("\n  "+quesCount+".  "+myques.ques);
            rba.setText("A "+myques.ans[0]);
            rbb.setText("B "+myques.ans[1]);
            rbc.setText("C "+myques.ans[2]);
            rbd.setText("D "+myques.ans[3]);
            rba.setSelected(false); rbb.setSelected(false); 
            rbc.setSelected(false); rbd.setSelected(false);
        } 
        catch(Exception e) 
        { System.out.println(e); } 
        
        try
        {   si.close();
            fi.close(); 
        } 
        catch(Exception e) 
        { System.out.println(e); } 
    }
    
    public void makeScoreMessage()
    {   if(myques != null)
        {   String ss = "\n  "+quesCount+".  "+myques.ques+"\n";
            scoreMessage.append(ss);
                        
            String okorno = "×";
            String astr = "    A ";
            String bstr = "    B ";
            String cstr = "    C ";
            String dstr = "    D ";
            if(rba.isSelected() && myques.ansok == 0)
            {   scoreFS += 10;
                okorno =  "√";
            }
            if(rbb.isSelected() && myques.ansok == 1)
            {   scoreFS += 10;
                okorno =  "√";
            }
            if(rbc.isSelected() && myques.ansok == 2)
            {   scoreFS += 10;
                okorno =  "√";
            }
            if(rbd.isSelected() && myques.ansok == 3)
            {   scoreFS += 10;
                okorno =  "√";
            }
            
            if(rba.isSelected())  astr = "   (A)";
            if(rbb.isSelected())  bstr = "   (B)";
            if(rbc.isSelected())  cstr = "   (C)";
            if(rbd.isSelected())  dstr = "   (D)";
                
            String ssans = "  "+okorno+astr+myques.ans[0]+bstr+myques.ans[1]+cstr+myques.ans[2]+dstr+myques.ans[3]+"\n";
            scoreMessage.append(ssans);
        } 
    }

    public void getRandomTopic()
    {   topic = new int[10];
        boolean flag;
        for(int i = 0; i < topic.length; i ++)  
        {   flag = true;
            while(flag)   
            {   flag = false;
                topic[i] = (int)(Math.random()*20)+1;
                for(int j = 0; j < i; j ++) 
                {   if(topic[i] == topic[j])
                    {   flag = true;
                        break;
                    }
                }
            }
         }
    }
    
    public boolean selectTopic(int uid)
    {   for(int i=0; i< topic.length; i++)
            if(uid == topic[i])
                return true;
        return false;
    }
    
    public void showFinnallyScore()
    {   
        ScoreShowDialog scoreD = new ScoreShowDialog(scoreMessage.toString(), true);
    }
}

class Question implements Serializable  
{   int id;
    String ques; 
    String []ans;
    int ansok;
        
    public Question(int uid, String uq, String ua0, String ua1, String ua2, String ua3, int uaok)  
    {   id = uid;  
        ques = uq;
        ans = new String[4];
        ans[0] = new String(ua0);
        ans[1] = new String(ua1);
        ans[2] = new String(ua2);
        ans[3] = new String(ua3);
        ansok = uaok;
    }
}

class ScoreShowDialog extends Stage
{   public static final int WIDTH = 700;
    public static final int HEIGHT = 750;

    private Button closeBtn;
    private TextArea viewArea;
        
    public ScoreShowDialog(String viewText, boolean modal)
    {   viewArea = new TextArea(viewText);
	    viewArea.setStyle("-fx-font-family:KaiTi;-fx-font-size:16");
	    closeBtn = new Button(" 关闭 ");
	    closeBtn.setOnAction(e->{
	    	close();
	    });
	    	        			
        BorderPane scoreBP = new BorderPane();
        scoreBP.setCenter(viewArea);
        scoreBP.setBottom(closeBtn);
        scoreBP.setMargin(closeBtn, new Insets(10, 0, 10, 0));
        scoreBP.setAlignment(closeBtn, Pos.CENTER);
                        
        Scene scene = new Scene(scoreBP, WIDTH, HEIGHT);
        setTitle(" 成绩显示");
        setScene(scene);
        initModality(Modality.APPLICATION_MODAL);
        showAndWait();
    }
}
