
----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2508.18 | 0.0879004 | 280.61ms | 6701 | 80 | 401.266 | 2547.89 | 0.00147179 | 1(Win) | true |
| Jsonifier (two-stage) | 2158.8 | 0.0789891 | 352.777ms | 6701 | 80 | 437.399 | 2960.24 | 0.00295593 | 2(Loss) | true |
| Glaze | 1925.16 | 1.0938 | 365.571ms | 6701 | 160 | 210931 | 3319.5 | 0.664704 | 3(Loss) | true |
| simdjson (ondemand) | 994.515 | 0.0787048 | 661.165ms | 6701 | 4890 | 125074 | 6425.82 | 0.0830382 | 4(Loss) | true |
