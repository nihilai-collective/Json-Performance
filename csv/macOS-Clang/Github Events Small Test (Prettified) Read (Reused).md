
----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2093.98 | 0.939128 | 112.772ms | 2158 | 160 | 13631 | 982.831 | 0.216042 | 1(Win) | true |
| Jsonifier (two-stage) | 1982.07 | 0.100211 | 132.474ms | 2158 | 1280 | 1385.82 | 1038.32 | 0.754357 | 2(Loss) | true |
| Glaze | 1839.68 | 0.58182 | 143.922ms | 2158 | 80 | 3389.1 | 1118.69 | 0.642121 | 3(Loss) | true |
| simdjson (ondemand) | 1306.35 | 0.755712 | 160.048ms | 2158 | 640 | 90714.4 | 1575.4 | 0.683635 | 4(Loss) | true |
