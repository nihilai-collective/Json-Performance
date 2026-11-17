
----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2589.88 | 0.167206 | 6652.13ms | 183677 | 4890 | 6.25404e+07 | 67635.5 | 0.0236789 | 1(Win) | true |
| Jsonifier (two-stage) | 2471.42 | 0.283561 | 7382.44ms | 183677 | 1280 | 5.17035e+07 | 70877.4 | 0.178757 | 2(Loss) | true |
| Glaze | 1729.49 | 0.275296 | 5248.74ms | 183677 | 1280 | 9.95146e+07 | 101283 | 0.396107 | 3(Loss) | true |
| simdjson (ondemand) | 1055.07 | 0.555156 | 8805.08ms | 183677 | 80 | 6.79617e+07 | 166024 | 0.99323 | 4(Loss) | true |
