import java.util.Map;

public class User {
    public int id;
    public String name;
    public UserSchool userSchool;
    public Map<String, Integer> score;

    public String getUserInfo() {
        StringBuilder res = new StringBuilder("User id is " + id + " , user name is " + name + "; user school is " + userSchool.getsName());
        res.append(", user exam score is ");
        for (Map.Entry<String, Integer> entry : score.entrySet()) {
            res.append(entry.getKey()).append("-").append(entry.getValue()).append(";");
        }
        return res.toString();
    }

    private class UserSchool {
        private int sId;
        private String sName;

        public int getsId() {
            return sId;
        }

        public void setsId(int sId) {
            this.sId = sId;
        }

        public String getsName() {
            return sName;
        }

        public void setsName(String sName) {
            this.sName = sName;
        }
    }
}