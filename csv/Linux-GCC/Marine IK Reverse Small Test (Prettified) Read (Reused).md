
----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2933.47 | 0.0259748 | 1433.85ms | 18245 | 640 | 1519.17 | 5931.46 | 0.0706272 | 1.73714 | 6.95911 | 1.22324 | 0.00134232 | 2.2352e-05 | 5.30967e-06 | 1(Win) | true |
| simdjson (reflection) | 2537.37 | 0.103214 | 1521.62ms | 18245 | 30 | 1502.87 | 6857.4 | 0.128981 | 2.00524 | 7.82028 | 1.3066 | 0.000692427 | 2.00968e-05 | 7.30794e-06 | 2(Loss) | true |
| Jsonifier | 2457.08 | 0.0818148 | 1539.41ms | 18245 | 640 | 21483 | 7081.5 | 0.129307 | 2.06406 | 7.21677 | 1.66912 | 0.0018231 | 5.77213e-05 | 3.50267e-05 | 3(Loss) | true |
| Glaze | 2000.94 | 0.0874782 | 1691.89ms | 18245 | 320 | 18517 | 8695.82 | 0.0690823 | 2.53797 | 11.0264 | 2.13571 | 0.00356348 | 8.39271e-06 | 1.37024e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1981.34 | 0.218831 | 1715.95ms | 18245 | 80 | 29544.5 | 8781.81 | 0.00270453 | 2.56178 | 9.58425 | 1.74743 | 0.00201973 | 8.08441e-05 | 3.08304e-05 | 5(Loss) | true |
