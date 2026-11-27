
----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3117.29 | 0.0780698 | 666.487ms | 18245 | 30 | 569.666 | 5581.7 | 0.0418208 | 0.790516 | 1(Win) | true |
| Jsonifier | 2896.99 | 0.209093 | 683.318ms | 18245 | 1280 | 201875 | 6006.17 | 0.010329 | 0.850952 | 2(Loss) | true |
| simdjson (reflection) | 2586.94 | 0.155291 | 754.517ms | 18245 | 80 | 8727.61 | 6726.01 | 0.314019 | 0.953262 | 3(Loss) | true |
| simdjson (ondemand) | 1977.27 | 0.177415 | 947.87ms | 18245 | 30 | 7312.37 | 8799.9 | 0.19698 | 1.24838 | 4(Loss) | true |
| Glaze | 1959.71 | 0.139914 | 977.757ms | 18245 | 4890 | 754628 | 8878.75 | 0.0626721 | 1.25967 | 5(Loss) | true |
