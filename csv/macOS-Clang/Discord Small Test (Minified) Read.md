
----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2166.51 | 0.0648165 | 216.849ms | 4857 | 320 | 614.52 | 2138 | 0.194191 | 1(Win) | true |
| Glaze | 1363.31 | 0.435377 | 342.676ms | 4857 | 1280 | 280086 | 3397.62 | 0.419532 | 2(Loss) | true |
| Jsonifier (two-stage) | 1268.78 | 0.0580135 | 372.546ms | 4857 | 160 | 717.698 | 3650.75 | 0.00684744 | 3(Loss) | true |
| simdjson (ondemand) | 639.614 | 0.0700042 | 782.783ms | 4857 | 160 | 4112.14 | 7241.86 | 0.212239 | 4(Loss) | true |
