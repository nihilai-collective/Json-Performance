
----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1710.57 | 0.249066 | 149.929ms | 2158 | 160 | 1436.71 | 1203.12 | 0.0519211 | 1.41608 | 1(Win) | true |
| Jsonifier (two-stage) | 1438.55 | 0.290677 | 174.414ms | 2158 | 160 | 2766.9 | 1430.62 | 0.13089 | 1.68393 | 2(Loss) | true |
| Jsonifier | 1272.84 | 0.258506 | 194.822ms | 2158 | 160 | 2795.2 | 1616.88 | 0.0386698 | 1.92011 | 3(Loss) | true |
| simdjson (ondemand) | 876.048 | 0.406531 | 262.798ms | 2158 | 1280 | 116747 | 2349.22 | 0.0133005 | 2.7918 | 4(Loss) | true |
