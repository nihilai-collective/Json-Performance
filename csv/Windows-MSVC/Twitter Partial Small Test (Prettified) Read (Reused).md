
----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7009.1 | 0.294123 | 64.2265ms | 3808 | 640 | 1486.31 | 518.125 | 0 | 0.334843 | 1(Win) | true |
| Jsonifier (two-stage) | 6953.53 | 0.22274 | 56.587ms | 3808 | 1280 | 1732.16 | 522.266 | 0.0149566 | 0.338126 | 2(Loss) | true |
| simdjson (ondemand) | 3710.44 | 0.234012 | 109.835ms | 3808 | 320 | 1678.68 | 978.75 | 0.191939 | 0.649094 | 3(Loss) | true |
| Glaze | 3520.48 | 0.252256 | 106.982ms | 3808 | 320 | 2166.83 | 1031.56 | 0.27339 | 0.683092 | 4(Loss) | true |
