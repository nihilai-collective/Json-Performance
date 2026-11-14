
----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14819.3 | 0.210309 | 791.63ms | 9255 | 2560 | 4016.57 | 595.594 | 0.380793 | 0.366103 | 1.46321 | 0.279525 | 0.000354918 | 8.39918e-06 | 1.43504e-06 | 1(Win) | true |
| Glaze | 3987.99 | 0.0851483 | 960.087ms | 9255 | 4890 | 17366.3 | 2213.21 | 0.00893631 | 1.29209 | 4.949 | 0.854889 | 0.000382063 | 4.75728e-05 | 2.05714e-05 | 2(Loss) | true |
