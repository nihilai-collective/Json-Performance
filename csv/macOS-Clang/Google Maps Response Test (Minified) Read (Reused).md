
----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2339.28 | 0.0289436 | 508.4ms | 11812 | 320 | 621.636 | 4815.5 | 0.0508383 | 1(Win) | true |
| Jsonifier (two-stage) | 1426.16 | 0.0699838 | 910.386ms | 11812 | 30 | 916.7 | 7898.7 | 0.0021101 | 2(Loss) | true |
| Glaze | 1125.09 | 0.13423 | 1132.57ms | 11812 | 40 | 7224.91 | 10012.4 | 0.0820491 | 3(Loss) | true |
| simdjson (ondemand) | 865.548 | 0.0956518 | 1357.23ms | 11812 | 40 | 6198.85 | 13014.6 | 0.0160102 | 4(Loss) | true |
