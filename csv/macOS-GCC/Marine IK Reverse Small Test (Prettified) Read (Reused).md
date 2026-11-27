
----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2213.52 | 0.130255 | 939.252ms | 18245 | 2560 | 268380 | 7860.7 | 0.151616 | 1(Win) | true |
| Jsonifier | 2085.91 | 0.321405 | 992.262ms | 18245 | 640 | 460028 | 8341.6 | 0.182552 | 2(Loss) | true |
| simdjson (reflection) | 2047.23 | 0.652733 | 1071.4ms | 18245 | 80 | 246216 | 8499.2 | 0.0752445 | 3(Loss) | true |
| simdjson (ondemand) | 1556.46 | 0.0835448 | 1258.64ms | 18245 | 4890 | 426540 | 11179.1 | 0.00702683 | 4(Loss) | true |
| Glaze | 1499.26 | 0.347761 | 1427.47ms | 18245 | 320 | 521252 | 11605.6 | 1.90019 | 5(Loss) | true |
