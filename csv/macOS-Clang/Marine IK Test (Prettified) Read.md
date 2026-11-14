
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2158.59 | 0.240847 | 10084.9ms | 7351818 | 160 | 9.79149e+09 | 3.24806e+06 | 0.00268571 | 1(Win) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 1953.89 | 0.283885 | 5209.51ms | 7351818 | 80 | 8.30168e+09 | 3.58835e+06 | 5.07687 | -(Loss) | false |
| Glaze | 1544.43 | 0.209573 | 6874.31ms | 7351818 | 40 | 3.62065e+09 | 4.5397e+06 | 0.0249609 | 3(Loss) | true |
| simdjson (ondemand) | 1465.7 | 0.231437 | 7250.02ms | 7351818 | 40 | 4.90259e+09 | 4.78355e+06 | 0.0250084 | 4(Loss) | true |
