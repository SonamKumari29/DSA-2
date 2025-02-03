import java.util.*;

public class SonamKumari29_SocialNetworkFriendRecommendationSys {
    private Map<Integer, Set<Integer>> network;

    public SonamKumari29_SocialNetworkFriendRecommendationSys() {
        this.network = new HashMap<>();
    }

    // Add a new user
    public void addUser(int userId) {
        if (!network.containsKey(userId)) {
            network.put(userId, new HashSet<>());
            System.out.println("User " + userId + " added.");
        } else {
            System.out.println("User " + userId + " already exists.");
        }
    }

    // Establish a friendship
    public void addFriendship(int userId1, int userId2) {
        if (network.containsKey(userId1) && network.containsKey(userId2)) {
            network.get(userId1).add(userId2);
            network.get(userId2).add(userId1);
            System.out.println("Friendship established between " + userId1 + " and " + userId2 + ".");
        } else {
            System.out.println("Both users must exist before adding a friendship.");
        }
    }

    // Get friend recommendations
    public void getFriendRecommendations(int userId) {
        if (!network.containsKey(userId)) {
            System.out.println("User does not exist.");
            return;
        }
        
        Set<Integer> directFriends = network.get(userId);
        Map<Integer, Integer> recommendationCount = new HashMap<>();
        
        for (int friend : directFriends) {
            for (int friendOfFriend : network.get(friend)) {
                if (friendOfFriend != userId && !directFriends.contains(friendOfFriend)) {
                    recommendationCount.put(friendOfFriend, recommendationCount.getOrDefault(friendOfFriend, 0) + 1);
                }
            }
        }
        
        List<Integer> recommendations = new ArrayList<>(recommendationCount.keySet());
        recommendations.sort((a, b) -> recommendationCount.get(b) - recommendationCount.get(a));
        
        System.out.println("Friend Recommendations for " + userId + ": " + recommendations);
    }

    // View direct friends of a user
    public void viewFriends(int userId) {
        if (!network.containsKey(userId)) {
            System.out.println("User does not exist.");
            return;
        }
        System.out.println("Friends of " + userId + ": " + network.get(userId));
    }

    public static void main(String[] args) {
        SonamKumari29_SocialNetworkFriendRecommendationSys socialNetwork = new SonamKumari29_SocialNetworkFriendRecommendationSys();
        
        socialNetwork.addUser(1);
        socialNetwork.addUser(2);
        socialNetwork.addUser(3);
        
        socialNetwork.addFriendship(1, 2);
        socialNetwork.addFriendship(2, 3);
        
        socialNetwork.getFriendRecommendations(1);
        socialNetwork.viewFriends(1);
    }
}
