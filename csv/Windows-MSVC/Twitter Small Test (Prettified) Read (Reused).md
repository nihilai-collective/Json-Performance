
----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2010.11 | 0.256387 | 207.296ms | 3808 | 30 | 643.678 | 1806.67 | 0 | 1.20713 | 1(Win) | true |
| Glaze | 1794.76 | 0.121228 | 222.823ms | 3808 | 320 | 1925.45 | 2023.44 | 0.263239 | 1.36054 | 2(Loss) | true |
| simdjson (ondemand) | 1716.3 | 0.246853 | 230.639ms | 3808 | 640 | 17460.8 | 2115.94 | 0.445038 | 1.42504 | 3(Loss) | true |
| Jsonifier | 1694.27 | 0.243529 | 232.594ms | 3808 | 4890 | 133241 | 2143.46 | 0.0355709 | 1.44213 | 4(Loss) | true |
