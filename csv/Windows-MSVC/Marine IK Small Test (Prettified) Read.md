
----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1683.21 | 0.148445 | 1062.39ms | 18245 | 4890 | 1.15147e+06 | 10337.3 | 0.105681 | 1.46691 | 1(Win) | true |
| Jsonifier | 1521.85 | 0.19818 | 1182.5ms | 18245 | 30 | 15402.3 | 11433.3 | 0 | 1.62298 | 2(Loss) | true |
| simdjson (ondemand) | 731.891 | 0.379705 | 2444.66ms | 18245 | 320 | 2.60758e+06 | 23773.8 | 0.0367918 | 3.37924 | 3(Loss) | true |
| Glaze | 586.367 | 0.180197 | 3001.55ms | 18245 | 1280 | 3.65977e+06 | 29673.9 | 0.457556 | 4.21816 | 4(Loss) | true |
