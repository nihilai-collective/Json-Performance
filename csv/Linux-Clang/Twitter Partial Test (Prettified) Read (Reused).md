
----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9674.16 | 0.111017 | 7101.86ms | 631514 | 80 | 382130 | 62254.3 | 0.00526095 | 0.522707 | 2.68037 | 0.298201 | 0.000787374 | 4.43379e-06 | 2.17731e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 9641.59 | 0.0371113 | 7081.66ms | 631514 | 4890 | 2.62779e+06 | 62464.7 | 0.0149879 | 0.523307 | 2.67948 | 0.29797 | 0.000783458 | 1.13953e-05 | 7.56484e-06 | 2(Loss) | true |
| simdjson (ondemand) | 8294.65 | 0.097502 | 8127.35ms | 631514 | 320 | 1.60379e+06 | 72608.1 | 0.0057676 | 0.608404 | 2.87775 | 0.29091 | 0.000573963 | 3.86967e-06 | 1.04907e-06 | 3(Loss) | true |
| Glaze | 4040.92 | 0.0764143 | 8045.74ms | 631514 | 160 | 2.07527e+06 | 149040 | 0.0464132 | 1.25336 | 5.31461 | 0.9373 | 0.0011691 | 3.4639e-06 | 1.15793e-06 | 4(Loss) | true |
