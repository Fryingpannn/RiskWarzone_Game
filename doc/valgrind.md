Checking for memory leaks with valgrind.
1. Use the command below.
valgrind --leak-check=full \
         --leak-resolution=med \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./RiskWarzone_Game

2. Run the program as normal, with a normal exit.
3. Check valgrind-out.txt for the summary