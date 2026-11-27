
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3020.22 | 0.0771286 | 839.267ms | 3370 | 4890 | 3293.98 | 1064.12 | 0.00835425 | 1.75481 | 6.99288 | 1.16706 | 0.000760833 | 5.07303e-05 | 1.71124e-05 | 1(Win) | true |
| simdjson (ondemand) | 2284.89 | 0.0802716 | 874.554ms | 3370 | 4890 | 6233.92 | 1406.58 | 0.115834 | 2.29839 | 8.05282 | 1.3724 | 0.002199 | 5.6131e-05 | 1.89935e-05 | 2(Loss) | true |
