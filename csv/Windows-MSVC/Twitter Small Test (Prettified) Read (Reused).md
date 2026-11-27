
----
### Twitter Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2280.43 | 0.17206 | 183.418ms | 3808 | 160 | 1201.26 | 1592.5 | 0.0785546 | 1.31962 | 1(Win) | true |
| Glaze | 2158.45 | 0.275205 | 196.621ms | 3808 | 80 | 1715.19 | 1682.5 | 0.296296 | 1.39109 | 2(Loss) | true |
| Jsonifier (two-stage) | 2072.6 | 0.112778 | 198.392ms | 3808 | 640 | 2499.12 | 1752.19 | 0.26824 | 1.44963 | 3(Loss) | true |
| simdjson (ondemand) | 2028.82 | 0.268371 | 196.846ms | 3808 | 40 | 923.077 | 1790 | 0.373832 | 1.47863 | 4(Loss) | true |
