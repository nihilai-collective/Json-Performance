
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3044.82 | 0.0221134 | 827.337ms | 25388 | 160 | 494.728 | 7951.84 | 0.00958806 | 1(Win) | true |
| Jsonifier (two-stage) | 2572.38 | 0.0213447 | 1054.72ms | 25388 | 160 | 645.78 | 9412.24 | 0.129716 | 2(Loss) | true |
| Glaze | 1825 | 0.0877714 | 1393.15ms | 25388 | 4890 | 663046 | 13266.8 | 0.558739 | 3(Loss) | true |
| simdjson (ondemand) | 1707.9 | 0.0900235 | 1452.05ms | 25388 | 30 | 4886.1 | 14176.4 | 0.0578762 | 4(Loss) | true |
