
----
### Apache Builds Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1393.7 | 0.811451 | 244.256ms | 3370 | 640 | 224090 | 2306 | 0.155871 | 1(Win) | true |
| simdjson (ondemand) | 1058.38 | 0.247634 | 311.052ms | 3370 | 1280 | 72377.8 | 3036.6 | 0.308601 | 2(Loss) | true |
