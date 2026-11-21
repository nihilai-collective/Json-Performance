
----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 4533.96 | 0.435398 | 96.6724ms | 3808 | 40 | 486.487 | 800.975 | 1.2483 | 1(Win) | true |
| simdjson (ondemand) | 4185.34 | 0.188875 | 94.8921ms | 3808 | 160 | 429.736 | 867.694 | 0.359573 | 2(Loss) | true |
| Jsonifier (two-stage) | 4038.84 | 0.248349 | 96.6367ms | 3808 | 4890 | 24384.5 | 899.166 | 0.0816568 | 3(Loss) | true |
| Glaze | 2483.37 | 0.38027 | 159.385ms | 3808 | 640 | 19791.3 | 1462.36 | 0.655505 | 4(Loss) | true |
