
----
### Apache Builds Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1711.38 | 0.0679444 | 923.143ms | 3370 | 1280 | 2083.94 | 1877.95 | 0.0056997 | 3.02658 | 12.0148 | 2.28368 | 0.00365032 | 2.7819e-05 | 3.47737e-06 | 1(Win) | true |
| simdjson (ondemand) | 989.989 | 0.0378537 | 1058.8ms | 3370 | 160 | 241.621 | 3246.38 | 0.0075078 | 5.27078 | 21.6792 | 4.29199 | 0.0084681 | 4.26558e-05 | 3.7092e-06 | 2(Loss) | true |
