
----
### Apache Builds Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3284.21 | 0.080233 | 101.038ms | 3370 | 160 | 98.6338 | 978.587 | 0.224037 | 0.733501 | 1(Win) | true |
| Jsonifier (two-stage) | 2870.77 | 0.225042 | 114.198ms | 3370 | 4890 | 31038.4 | 1119.52 | 0.0185137 | 0.841494 | 2(Loss) | true |
| Glaze | 2307.5 | 0.0693728 | 142.343ms | 3370 | 40 | 37.3436 | 1392.8 | 0.0982201 | 1.05307 | 3(Loss) | true |
| simdjson (ondemand) | 1894.11 | 0.168613 | 173.972ms | 3370 | 40 | 327.41 | 1696.78 | 0.222965 | 1.28743 | 4(Loss) | true |
