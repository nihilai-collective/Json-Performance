
----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1972.77 | 0.287647 | 953.421ms | 18245 | 640 | 411943 | 8820 | 0.37327 | 1(Win) | true |
| Jsonifier (two-stage) | 1832.02 | 1.13833 | 949.58ms | 18245 | 80 | 935091 | 9497.6 | 1.0211 | 2(Loss) | true |
| simdjson (reflection) | 1649.28 | 0.317836 | 1095.92ms | 18245 | 2560 | 2.87835e+06 | 10549.9 | 0.410211 | 3(Loss) | true |
| Glaze | 1243.32 | 0.16013 | 1441.41ms | 18245 | 30 | 15065.7 | 13994.7 | 0 | 4(Loss) | true |
| simdjson (ondemand) | 1233.08 | 0.309806 | 1432.12ms | 18245 | 640 | 1.22311e+06 | 14110.8 | 0.929566 | 5(Loss) | true |
