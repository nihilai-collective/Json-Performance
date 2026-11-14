
----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 755.463 | 0.169195 | 594.042ms | 4630 | 40 | 3911.77 | 5844.77 | 0.0676785 | 1(Win) | true |
| Jsonifier (two-stage) | 687.467 | 0.140474 | 652.631ms | 4630 | 40 | 3256.21 | 6422.88 | 0.0548519 | 2(Loss) | true |
| Glaze | 486.558 | 0.303795 | 919.989ms | 4630 | 320 | 243222 | 9075 | 0.0974434 | 3(Loss) | true |
| simdjson (ondemand) | 453.016 | 0.0331798 | 989.53ms | 4630 | 160 | 1673.41 | 9746.93 | 0.0488212 | 4(Loss) | true |
