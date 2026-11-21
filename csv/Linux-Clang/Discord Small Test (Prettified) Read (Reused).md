
----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3010.57 | 0.0545383 | 265.037ms | 6701 | 80 | 107.22 | 2122.71 | 0.0371125 | 0.812407 | 1(Win) | true |
| Glaze | 2387.84 | 0.200899 | 288.83ms | 6701 | 2560 | 74005.4 | 2676.3 | 0.261655 | 1.02674 | 2(Loss) | true |
| Jsonifier | 2090.9 | 0.253631 | 329.198ms | 6701 | 2560 | 153836 | 3056.37 | 0.0408893 | 1.17402 | 3(Loss) | true |
| simdjson (ondemand) | 1226.84 | 0.0673142 | 547.852ms | 6701 | 80 | 983.567 | 5208.95 | 0.149997 | 2.00727 | 4(Loss) | true |
