
----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7668.28 | 0.0928243 | 38.8638ms | 2889 | 320 | 35.5937 | 359.294 | 0.123659 | 0.299595 | 1(Win) | true |
| Jsonifier (two-stage) | 7644.38 | 0.0414804 | 39.0071ms | 2889 | 1280 | 28.6092 | 360.417 | 0.103286 | 0.300358 | 2(Loss) | true |
| simdjson (ondemand) | 7095.2 | 0.067758 | 41.6621ms | 2889 | 640 | 44.3065 | 388.314 | 0.0567035 | 0.324665 | 3(Loss) | true |
| Glaze | 3411.06 | 0.320309 | 83.1557ms | 2889 | 4890 | 32731.5 | 807.716 | 0.127274 | 0.702757 | 4(Loss) | true |
