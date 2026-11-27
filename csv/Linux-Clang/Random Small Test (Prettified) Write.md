
----
### Random Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14205.4 | 0.132792 | 792.988ms | 9255 | 4890 | 3328.9 | 621.33 | 0.0496417 | 0.380791 | 1.50319 | 0.261697 | 0.000285061 | 2.74875e-05 | 7.07074e-06 | 1(Win) | true |
| Glaze | 3472.82 | 0.12942 | 994.173ms | 9255 | 2560 | 27697 | 2541.52 | 0.100634 | 1.481 | 4.95181 | 0.855538 | 0.000281014 | 4.96775e-05 | 1.94152e-05 | 2(Loss) | true |
