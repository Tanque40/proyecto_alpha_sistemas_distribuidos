package lib;

/*
 * @author: Bruno Vitte @Tanque40 in github
 * @version: 1.0
 * @brief: Store a ConnectionType and User to send it to the server
 */

public class ConnectionObject {
    public ConnectionType connectionType;
    public User user;
    public int sendedPosition;
    public String userName;
    public int returnedId;

    public ConnectionObject(ConnectionType connectionType, User user, int sendedPosition, String userName,
            int returnedId) {
        this.connectionType = connectionType;
        this.user = user;
        this.sendedPosition = sendedPosition;
        this.userName = userName;
        this.returnedId = returnedId;
    }
}