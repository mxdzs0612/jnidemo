public class User {
    public int id;
    public String name;
    public UserSchool userSchool;

    public String getUserInfo() {
        return "User id is " + id + " , user name is " + name + "; user school is " + userSchool.getsName();
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