
----
### Marine IK Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1322.65 | 0.54862 | 1341.34ms | 18245 | 160 | 833410 | 13155.2 | 0.796332 | 1(Win) | true |
| simdjson (ondemand) | 1232.54 | 0.159066 | 1420.05ms | 18245 | 1280 | 645433 | 14117 | 0.097659 | 2(Loss) | true |
