
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2406.21 | 0.243262 | 10068.4ms | 7351818 | 160 | 8.03881e+09 | 2.91381e+06 | 0.309964 | 1(Win) | true |
| Jsonifier (two-stage) | 2269.9 | 0.277072 | 5205.65ms | 7351818 | 80 | 5.85939e+09 | 3.08879e+06 | 0.394878 | 2(Loss) | true |
| Glaze | 1659.38 | 0.17782 | 6843.53ms | 7351818 | 40 | 2.25799e+09 | 4.22522e+06 | 0.120432 | 3(Loss) | true |
| simdjson (ondemand) | 1572.9 | 0.144274 | 7233.2ms | 7351818 | 80 | 3.30866e+09 | 4.45753e+06 | 0.0712485 | 4(Loss) | true |
