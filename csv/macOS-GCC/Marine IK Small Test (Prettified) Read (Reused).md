
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2402.46 | 0.119311 | 863.335ms | 18245 | 4890 | 365132 | 7242.5 | 0.873267 | 1(Win) | true |
| Jsonifier (two-stage) | 2339.59 | 0.187629 | 885.251ms | 18245 | 2560 | 498481 | 7437.1 | 0.127901 | 2(Loss) | true |
| simdjson (reflection) | 2011.61 | 0.253461 | 1026.21ms | 18245 | 2560 | 1.23045e+06 | 8649.7 | 1.08977 | 3(Loss) | true |
| Glaze | 1507.13 | 0.0957987 | 1297.69ms | 18245 | 4890 | 598155 | 11545 | 0.107535 | 4(Loss) | true |
| simdjson (ondemand) | 1490.83 | 0.179383 | 1359.37ms | 18245 | 1280 | 561052 | 11671.2 | 0.178535 | 5(Loss) | true |
