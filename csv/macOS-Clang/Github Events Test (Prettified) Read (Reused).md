
----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2385.03 | 0.11746 | 3236.33ms | 65103 | 1280 | 1.19675e+06 | 26032 | 0.105857 | 1(Win) | true |
| Jsonifier (two-stage) | 2259.25 | 0.0997644 | 3403.07ms | 65103 | 2560 | 1.92426e+06 | 27481.3 | 0.0654567 | 2(Loss) | true |
| Glaze | 2094.09 | 0.131579 | 3486.08ms | 65103 | 1280 | 1.94803e+06 | 29648.7 | 0.0387947 | 3(Loss) | true |
| simdjson (ondemand) | 1196.28 | 0.0996387 | 5723.76ms | 65103 | 2560 | 6.84591e+06 | 51900 | 0.157387 | 4(Loss) | true |
