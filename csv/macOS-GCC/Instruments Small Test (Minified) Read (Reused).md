
----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3044.81 | 0.503042 | 160.104ms | 4669 | 4890 | 264634 | 1462.39 | 0.14384 | 1(Win) | true |
| Jsonifier (two-stage) | 1788.23 | 0.311166 | 265.938ms | 4669 | 4890 | 293557 | 2490.01 | 0.0399147 | 2(Loss) | true |
| Glaze | 1569.62 | 0.983268 | 310.686ms | 4669 | 320 | 248973 | 2836.8 | 2.72306 | 3(Loss) | true |
| simdjson (reflection) | 1319.91 | 0.3111 | 353.168ms | 4669 | 2560 | 281969 | 3373.5 | 0.0266714 | 4(Loss) | true |
| simdjson (ondemand) | 1159.8 | 0.366586 | 384.291ms | 4669 | 2560 | 507077 | 3839.2 | 1.30885 | 5(Loss) | true |
