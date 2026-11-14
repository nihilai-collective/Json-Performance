
----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16353.1 | 0.322156 | 1349.29ms | 213963 | 1280 | 2.06832e+06 | 12477.8 | 2.03348 | 1(Win) | true |
| Glaze | 2405.54 | 0.231985 | 8731.39ms | 213963 | 1280 | 4.95661e+07 | 84825.6 | 1.67473 | 2(Loss) | true |
| simdjson (reflection) | 290.133 | 0.294641 | 8546.25ms | 213963 | 640 | 2.74821e+09 | 703303 | 0.249793 | 3(Loss) | true |
