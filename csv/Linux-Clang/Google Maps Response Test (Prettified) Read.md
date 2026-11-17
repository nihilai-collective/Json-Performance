
----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3329.29 | 0.167695 | 737.96ms | 25388 | 2560 | 380746 | 7272.39 | 0.170158 | 0.740743 | 1(Win) | true |
| Jsonifier | 2994.63 | 0.280694 | 828.142ms | 25388 | 640 | 329622 | 8085.1 | 0.0745561 | 0.824008 | 2(Loss) | true |
| Glaze | 2361.27 | 0.207756 | 1028.39ms | 25388 | 80 | 36304.7 | 10253.8 | 0.565412 | 1.04566 | 3(Loss) | true |
| simdjson (ondemand) | 1845.27 | 0.13056 | 1316.88ms | 25388 | 2560 | 751269 | 13121 | 0.199296 | 1.33886 | 4(Loss) | true |
