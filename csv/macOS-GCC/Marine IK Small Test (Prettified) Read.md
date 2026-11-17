
----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1950.09 | 0.0909104 | 904.823ms | 18245 | 4890 | 321748 | 8922.57 | 0.242316 | 1(Win) | true |
| Jsonifier | 1887.34 | 0.625286 | 935.358ms | 18245 | 160 | 531697 | 9219.2 | 0.0346981 | 2(Loss) | true |
| simdjson (reflection) | 1733.05 | 0.236857 | 998.924ms | 18245 | 1280 | 723855 | 10040 | 0.00398391 | 3(Loss) | true |
| simdjson (ondemand) | 1339.79 | 0.0901571 | 1313.23ms | 18245 | 2560 | 350960 | 12987 | 0.0738655 | 4(Loss) | true |
| Glaze | 1253.22 | 0.114332 | 1427.45ms | 18245 | 4890 | 1.2322e+06 | 13884.1 | 0.330964 | 5(Loss) | true |
