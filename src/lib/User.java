package lib;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/*
 * @author: Bruno Vitte @Tanque40 in github
 * @version: 1.0
 * @brief: Create a user, store points, read if has a stored user
 */

public class User {
    private int id;
    private String name;
    private int points;

    public User(int id, String name, int points) {
        this.id = id;
        this.name = name;
        this.points = points;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getPoints() {
        return points;
    }

    public void setPoints(int points) {
        this.points = points;
    }

    public static User readUserFile(String givenUser) {
        int id, points;
        String name;
        try {
            File userFile = new File("user.me");
            Scanner userFileReader = new Scanner(userFile);
            if (userFileReader.hasNext()) {
                id = userFileReader.nextInt();
                name = userFileReader.nextLine();
                points = userFileReader.nextInt();
            } else {
                userFileReader.close();
                return null;
            }
            userFileReader.close();
            if (name.equals(givenUser)) {
                return new User(id, name, points);
            } else {
                System.err.println("Given username and stored user are not the same");
                return null;
            }
        } catch (FileNotFoundException fnfe) {
            System.err.println("File not founded, null user returned");
            System.out.println(System.getProperty("user.dir"));
            return null;
        }
    }
}