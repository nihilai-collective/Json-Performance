
----
### Twitter Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14085.4 | 0.131989 | 745.845ms | 4300 | 640 | 94.5049 | 291.139 | 0.504331 | 0.416028 | 1.02674 | 0.133721 | 0.000232922 | 4.36047e-05 | 1.70785e-05 | 1(Win) | true |
| Glaze | 4436.82 | 0.397931 | 812.335ms | 4300 | 2560 | 34629.7 | 924.266 | 0.591547 | 1.21382 | 3.03163 | 0.47721 | 0.00023492 | 4.95094e-05 | 1.40807e-05 | 2(Loss) | true |
| simdjson (reflection) | 561.862 | 0.102007 | 1459.91ms | 4300 | 2560 | 141898 | 7298.59 | 0.393232 | 9.25553 | 33.5984 | 7.42861 | 0.00926517 | 9.22057e-05 | 3.50654e-05 | 3(Loss) | true |
