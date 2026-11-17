
----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2073.38 | 0.329224 | 1026.89ms | 18245 | 640 | 488533 | 8392 | 1.09372 | 1(Win) | true |
| Jsonifier | 1930.91 | 0.394777 | 1139.53ms | 18245 | 30 | 37965.7 | 9011.2 | 0.471254 | 2(Loss) | true |
| simdjson (reflection) | 1837.17 | 0.195382 | 1084.98ms | 18245 | 4890 | 1.67442e+06 | 9470.95 | 0.182826 | 3(Loss) | true |
| simdjson (ondemand) | 1477.36 | 0.522297 | 1433.13ms | 18245 | 320 | 1.21087e+06 | 11777.6 | 1.99707 | 4(Loss) | true |
| Glaze | 1276.24 | 0.738797 | 1533.57ms | 18245 | 640 | 6.49309e+06 | 13633.6 | 0.21664 | 5(Loss) | true |
