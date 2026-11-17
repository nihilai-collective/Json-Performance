
----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2494.27 | 0.0826876 | 288.058ms | 6701 | 40 | 179.528 | 2562.1 | 0.0247254 | 0.981921 | 1(Win) | true |
| Glaze | 2442.94 | 0.116713 | 288.652ms | 6701 | 30 | 279.651 | 2615.93 | 0.0624769 | 1.00297 | 2(Loss) | true |
| Jsonifier (two-stage) | 2338.22 | 0.071834 | 301.632ms | 6701 | 80 | 308.359 | 2733.09 | 0.155716 | 1.04866 | 3(Loss) | true |
| Jsonifier | 2020.11 | 0.0604289 | 349.951ms | 6701 | 80 | 292.354 | 3163.47 | 0.184473 | 1.21521 | 4(Loss) | true |
| simdjson (ondemand) | 1958.11 | 0.0953004 | 342.789ms | 6701 | 40 | 386.951 | 3263.65 | 0.128016 | 1.25353 | 5(Loss) | true |
