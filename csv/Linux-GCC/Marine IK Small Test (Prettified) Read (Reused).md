
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3135.51 | 0.0502622 | 1395.05ms | 18245 | 2560 | 19915.6 | 5549.26 | 0.0725495 | 1.64465 | 6.76881 | 1.17408 | 0.00125141 | 4.53463e-05 | 2.28873e-05 | 1(Win) | true |
| Jsonifier | 2621.95 | 0.0924497 | 1493.48ms | 18245 | 30 | 1129.2 | 6636.2 | 0.144452 | 1.94286 | 7.04768 | 1.61562 | 0.00169544 | 3.83667e-05 | 0 | 2(Loss) | true |
| simdjson (reflection) | 2547.54 | 0.155436 | 1512.04ms | 18245 | 160 | 18033.1 | 6830.04 | 0.0903079 | 1.99378 | 7.81058 | 1.29866 | 0.000859825 | 2.84324e-05 | 8.56399e-06 | 3(Loss) | true |
| Glaze | 2023.14 | 0.0570915 | 1682.21ms | 18245 | 1280 | 30859.4 | 8600.38 | 0.0165536 | 2.50876 | 10.7842 | 2.08375 | 0.00336098 | 1.99113e-05 | 8.52117e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1970.78 | 0.0319392 | 1724.6ms | 18245 | 2560 | 20356.4 | 8828.89 | 0.0228971 | 2.57704 | 9.64253 | 1.76174 | 0.00146249 | 5.08701e-05 | 2.92246e-05 | 5(Loss) | true |
