
----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1071.11 | 0.0731291 | 451.84ms | 4926 | 80 | 822.977 | 4385.9 | 0.0842901 | 1(Win) | true |
| simdjson (ondemand) | 811.332 | 0.0806778 | 586.207ms | 4926 | 30 | 654.668 | 5790.23 | 0.0742079 | 2(Loss) | true |
