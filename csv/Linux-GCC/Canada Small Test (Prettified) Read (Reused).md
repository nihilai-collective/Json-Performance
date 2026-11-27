
----
### Canada Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2363.52 | 0.171652 | 557.602ms | 11579 | 80 | 5145.27 | 4672.09 | 0.291671 | 1.04149 | 1(Win) | true |
| Jsonifier (two-stage) | 2301.85 | 0.0456141 | 555.377ms | 11579 | 30 | 143.651 | 4797.27 | 0.146827 | 1.06971 | 2(Loss) | true |
| simdjson (ondemand) | 1895.97 | 0.0687437 | 681.58ms | 11579 | 40 | 641.218 | 5824.25 | 0.036901 | 1.30043 | 3(Loss) | true |
| simdjson (reflection) | 1872.27 | 0.0814026 | 658.434ms | 11579 | 40 | 922.025 | 5897.98 | 0.146023 | 1.31632 | 4(Loss) | true |
| Glaze | 1582.47 | 0.170025 | 774.881ms | 11579 | 2560 | 360361 | 6978.1 | 1.44171 | 1.55839 | 5(Loss) | true |
