
----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2036.74 | 0.0836311 | 235.054ms | 4857 | 160 | 578.792 | 2274.22 | 0.149278 | 1(Win) | true |
| Glaze | 1294.18 | 0.148167 | 370.821ms | 4857 | 2560 | 71992.6 | 3579.08 | 0.337706 | 2(Loss) | true |
| Jsonifier (two-stage) | 1149.4 | 0.264237 | 405.728ms | 4857 | 4890 | 554483 | 4029.92 | 1.19352 | 3(Loss) | true |
| simdjson (ondemand) | 581.387 | 0.174141 | 816.076ms | 4857 | 2560 | 492772 | 7967.15 | 0.409721 | 4(Loss) | true |
