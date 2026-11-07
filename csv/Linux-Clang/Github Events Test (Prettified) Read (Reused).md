
----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2912.82 | 0.103172 | 2574.16ms | 65103 | 2560 | 1.23806e+06 | 21315.1 | 0.0730467 | 0.848902 | 1(Win) | true |
| Jsonifier | 2039.23 | 0.0571062 | 3526.25ms | 65103 | 4890 | 1.47823e+06 | 30446.3 | 0.0523869 | 1.21306 | 2(Loss) | true |
| Glaze | 2026.6 | 0.150963 | 3584.92ms | 65103 | 640 | 1.36895e+06 | 30636.1 | 0.0725537 | 1.22063 | 3(Loss) | true |
| simdjson (ondemand) | 1370.9 | 0.0731711 | 5007.58ms | 65103 | 2560 | 2.81131e+06 | 45289.2 | 0.00790814 | 1.80487 | 4(Loss) | true |
