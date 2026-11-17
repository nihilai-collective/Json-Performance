
----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2065.07 | 0.77025 | 3803.62ms | 65103 | 640 | 3.43222e+07 | 30065.3 | 1.13603 | 1(Win) | true |
| Jsonifier | 1911.47 | 0.511501 | 3482.73ms | 65103 | 640 | 1.76661e+07 | 32481.3 | 0.536474 | 2(Loss) | true |
| Glaze | 1801.17 | 0.626083 | 4029.31ms | 65103 | 320 | 1.49042e+07 | 34470.4 | 1.03293 | 3(Loss) | true |
| simdjson (ondemand) | 974.378 | 0.639307 | 6468.98ms | 65103 | 320 | 5.31027e+07 | 63719.7 | 2.59658 | 4(Loss) | true |
