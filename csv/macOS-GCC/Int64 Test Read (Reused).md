
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2904.14 | 0.662251 | 137.929ms | 3862 | 4890 | 344941 | 1268.22 | 1.10985 | 1(Win) | true |
| Glaze | 1179.27 | 1.06373 | 311.517ms | 3862 | 320 | 353196 | 3123.2 | 0.509684 | 2(Loss) | true |
| Jsonifier (two-stage) | 901.128 | 0.856004 | 476.391ms | 3862 | 320 | 391700 | 4087.2 | 3.67289 | 3(Loss) | true |
| simdjson (ondemand) | 406.913 | 0.427013 | 947.267ms | 3862 | 2560 | 3.82422e+06 | 9051.3 | 1.80842 | 4(Loss) | true |
