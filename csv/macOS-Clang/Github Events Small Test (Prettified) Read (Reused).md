
----
### Github Events Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2238.77 | 0.0838339 | 113.173ms | 2158 | 320 | 190.053 | 919.269 | 0.172308 | 1(Win) | true |
| Jsonifier (two-stage) | 2077.52 | 0.153198 | 115.744ms | 2158 | 4890 | 11262.3 | 990.617 | 0.447326 | 2(Loss) | true |
| Glaze | 1974.5 | 0.10641 | 121.798ms | 2158 | 640 | 787.291 | 1042.3 | 0.1354 | 3(Loss) | true |
| simdjson (ondemand) | 1575.52 | 0.283369 | 147.395ms | 2158 | 1280 | 17537.6 | 1306.26 | 0.628734 | 4(Loss) | true |
