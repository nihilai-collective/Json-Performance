
----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 450.683 | 0.0376682 | 995.672ms | 4630 | 80 | 1089.58 | 9797.39 | 0.0164612 | 1(Win) | true |
| simdjson (ondemand) | 439.535 | 0.0415139 | 1027.99ms | 4630 | 40 | 695.702 | 10045.9 | 0.0276309 | 2(Loss) | true |
