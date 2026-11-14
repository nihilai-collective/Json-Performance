
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 441.539 | 0.101217 | 6925.77ms | 1834197 | 80 | 1.28632e+09 | 3.96166e+06 | 0.0209937 | 1(Win) | true |
| Jsonifier (generic) DID NOT CONVERGE | 390.094 | 1.15401 | 7078.22ms | 1834197 | 80 | 2.14223e+11 | 4.48412e+06 | 7.17571 | -(Loss) | false |
