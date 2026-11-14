
----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12430.7 | 0.556516 | 745.006ms | 1996 | 1280 | 929.593 | 153.131 | 0.130437 | 0.516725 | 1.35671 | 0.20992 | 0.000501393 | 2.70071e-05 | 2.34845e-06 | 1(Win) | true |
| Glaze | 4363.5 | 0.512906 | 775.994ms | 1996 | 320 | 1602.06 | 436.241 | 1.07642 | 1.26688 | 3.25601 | 0.480461 | 0.000502568 | 2.50501e-05 | 0 | 2(Loss) | true |
