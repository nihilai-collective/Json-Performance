
----
### Github Events Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1633.36 | 0.622591 | 153.645ms | 2158 | 40 | 2461.54 | 1260 | 0 | 1.49695 | 1(Win) | true |
| Jsonifier | 1593.06 | 0.106748 | 166.014ms | 2158 | 640 | 1217.14 | 1291.88 | 0.433526 | 1.52331 | 2(Loss) | true |
| Jsonifier (two-stage) | 1562.44 | 0.119364 | 158.591ms | 2158 | 640 | 1582.06 | 1317.19 | 0.307474 | 1.55028 | 3(Loss) | true |
| simdjson (ondemand) | 896.135 | 0.0889749 | 254.749ms | 2158 | 320 | 1336.11 | 2296.56 | 0.177208 | 2.72877 | 4(Loss) | true |
