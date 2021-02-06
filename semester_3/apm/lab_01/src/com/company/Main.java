package com.company;

public class Main {
    public static void main(String[] args) {
        int sum = 0;

        for (int i = 1; i < args.length; i++) {
            int number = Integer.parseInt(args[i]);

            sum += number;
        }

        float average = (float)sum / (args.length - 1);
        System.out.println(average);
    }
}
