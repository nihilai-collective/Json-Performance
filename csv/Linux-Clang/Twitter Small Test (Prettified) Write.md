
----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9502.63 | 0.23543 | 780.114ms | 4300 | 160 | 165.155 | 431.544 | 0.449533 | 0.582314 | 1.38465 | 0.23907 | 0.000238372 | 2.32558e-05 | 1.16279e-05 | 1(Win) | true |
| Glaze | 3157.35 | 0.26905 | 866.765ms | 4300 | 2560 | 31260.7 | 1298.81 | 0.43209 | 1.65227 | 3.75209 | 0.629768 | 0.000349291 | 2.73438e-05 | 2.72529e-06 | 2(Loss) | true |
