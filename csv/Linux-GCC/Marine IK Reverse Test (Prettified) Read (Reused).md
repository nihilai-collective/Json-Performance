
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2800.85 | 0.340237 | 8503.25ms | 7351818 | 40 | 2.90157e+09 | 2.50325e+06 | 0.0453487 | 0.883926 | 1(Win) | true |
| Jsonifier | 2780.14 | 0.141458 | 8482.13ms | 7351818 | 160 | 2.03625e+09 | 2.52191e+06 | 1.49439 | 0.89052 | 2(Loss) | true |
| simdjson (reflection) | 2539.09 | 0.165502 | 9122.84ms | 7351818 | 30 | 6.26557e+08 | 2.76132e+06 | 1.13039 | 0.975058 | 3(Loss) | true |
| simdjson (ondemand) | 2179.14 | 0.200384 | 5229.84ms | 7351818 | 80 | 3.32532e+09 | 3.21743e+06 | 1.784 | 1.13611 | 4(Loss) | true |
| Glaze | 2055.14 | 0.148364 | 5470.02ms | 7351818 | 30 | 7.68576e+08 | 3.41157e+06 | 0.93477 | 1.20467 | 5(Loss) | true |
