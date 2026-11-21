
----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2866.03 | 0.175322 | 6294.09ms | 183677 | 640 | 7.34851e+06 | 61118.7 | 0.161942 | 1(Win) | true |
| Jsonifier (two-stage) | 2235.8 | 0.520894 | 7244.5ms | 183677 | 320 | 5.32954e+07 | 78346.7 | 0.530154 | 2(Loss) | true |
| Glaze | 1962.08 | 0.213877 | 9356.86ms | 183677 | 320 | 1.16669e+07 | 89276.8 | 0.195196 | 3(Loss) | true |
| simdjson (ondemand) | 1174.63 | 0.0955461 | 7894.8ms | 183677 | 640 | 1.29931e+07 | 149126 | 0.179696 | 4(Loss) | true |
