
----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2420.99 | 0.0580894 | 86.9414ms | 1691 | 1280 | 191.649 | 666.118 | 0.0750007 | 1(Win) | true |
| Glaze | 1795.01 | 0.317755 | 108.015ms | 1691 | 80 | 651.967 | 898.413 | 0.171429 | 2(Loss) | true |
| Jsonifier (two-stage) | 1781.63 | 0.14815 | 113.957ms | 1691 | 4890 | 8793.52 | 905.162 | 0.149046 | 3(Loss) | true |
| simdjson (ondemand) | 1282.69 | 0.0875988 | 142.417ms | 1691 | 4890 | 5931.33 | 1257.26 | 0.21902 | 4(Loss) | true |
