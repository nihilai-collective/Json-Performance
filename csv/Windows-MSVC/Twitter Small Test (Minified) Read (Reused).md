
----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1886.7 | 0.197134 | 164.821ms | 2889 | 320 | 2651.94 | 1460.31 | 0.192226 | 1.28947 | 1(Win) | true |
| Jsonifier (two-stage) | 1546.83 | 0.302274 | 204.957ms | 2889 | 1280 | 37104.2 | 1781.17 | 0.258115 | 1.57666 | 2(Loss) | true |
| simdjson (ondemand) | 1535.18 | 0.120948 | 195.501ms | 2889 | 320 | 1507.74 | 1794.69 | 0.0174155 | 1.5869 | 3(Loss) | true |
| Glaze | 1522.85 | 0.340875 | 194.483ms | 2889 | 2560 | 97367.1 | 1809.22 | 0.262716 | 1.60126 | 4(Loss) | true |
