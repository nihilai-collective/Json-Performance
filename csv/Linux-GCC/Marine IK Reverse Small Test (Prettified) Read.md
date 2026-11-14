
----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2611.39 | 0.0821679 | 1399.21ms | 18245 | 640 | 19183.6 | 6663.04 | 0.0446223 | 1.98257 | 7.75314 | 1.39414 | 0.00154863 | 3.14298e-05 | 1.69567e-05 | 1(Win) | true |
| Jsonifier | 2349.18 | 0.0897713 | 1468.24ms | 18245 | 640 | 28295.1 | 7406.75 | 0.237918 | 2.20277 | 8.01315 | 1.8148 | 0.00186669 | 0.000179073 | 0.000131885 | 2(Loss) | true |
| simdjson (reflection) | 2312.4 | 0.0633014 | 1482.89ms | 18245 | 1280 | 29040.2 | 7524.57 | 0.0982644 | 2.22235 | 8.33927 | 1.43261 | 0.00146979 | 5.01422e-05 | 2.57776e-05 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1840.1 | 0.0453811 | 1679.37ms | 18245 | 2560 | 47140.8 | 9455.92 | 0.0406491 | 2.79472 | 10.2286 | 1.89784 | 0.00199498 | 8.28352e-05 | 5.07631e-05 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 1839.76 | 0.0530222 | 1682.63ms | 18245 | 1280 | 32187.7 | 9457.62 | 0.0761701 | 2.80818 | 12.0684 | 2.37534 | 0.0034912 | 6.3502e-05 | 3.79813e-05 | 4(Tie) | true |
