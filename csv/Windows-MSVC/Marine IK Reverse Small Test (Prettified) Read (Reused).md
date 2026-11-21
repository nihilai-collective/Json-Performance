
----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1910.12 | 0.174137 | 1073.92ms | 18245 | 4890 | 1.23043e+06 | 9109.28 | 0.0934316 | 1.29218 | 1(Win) | true |
| Jsonifier | 1578.58 | 0.38158 | 1350.91ms | 18245 | 1280 | 2.26431e+06 | 11022.4 | 0.836931 | 1.56459 | 2(Loss) | true |
| Glaze | 643.031 | 0.126851 | 2909.34ms | 18245 | 2560 | 3.01617e+06 | 27059 | 0.184297 | 3.84666 | 3(Loss) | true |
| simdjson (ondemand) | 421.973 | 0.429806 | 4328.26ms | 18245 | 160 | 5.02554e+06 | 41234.4 | 0.0925448 | 5.86362 | 4(Loss) | true |
