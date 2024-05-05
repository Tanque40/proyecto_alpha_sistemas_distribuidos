package lib;

/*
 * @author: Bruno Vitte @Tanque40 in github
 * @version: 1.0
 * @brief: Create a user, store points
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
}