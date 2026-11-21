
----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3223.56 | 0.116966 | 2873.44ms | 83958 | 80 | 67524.3 | 24838.5 | 0.358488 | 0.767155 | 1(Win) | true |
| Jsonifier | 2446.26 | 0.0437947 | 3669.54ms | 83958 | 40 | 8219.05 | 32731 | 0.265479 | 1.01122 | 2(Loss) | true |
| Glaze | 2421.48 | 0.133391 | 3715.42ms | 83958 | 640 | 1.24509e+06 | 33066 | 0.0428882 | 1.02166 | 3(Loss) | true |
| simdjson (ondemand) | 1339.75 | 0.157252 | 6299.75ms | 83958 | 320 | 2.82634e+06 | 59764 | 0.0515983 | 1.84715 | 4(Loss) | true |
