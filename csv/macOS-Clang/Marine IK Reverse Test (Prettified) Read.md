
----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2130.29 | 0.199748 | 10262.4ms | 7351818 | 160 | 6.91508e+09 | 3.29122e+06 | 0.463826 | 1(Win) | true |
| Jsonifier (two-stage) | 2028.97 | 0.127412 | 5224.59ms | 7351818 | 80 | 1.55077e+09 | 3.45557e+06 | 0.0410523 | 2(Loss) | true |
| Glaze | 1548.8 | 0.18362 | 6859.48ms | 7351818 | 30 | 2.07281e+09 | 4.52689e+06 | 0.00763748 | 3(Loss) | true |
| simdjson (ondemand) | 1238.38 | 2.25394 | 8624.98ms | 7351818 | 40 | 6.51365e+11 | 5.66162e+06 | 3.58495 | 4(Loss) | true |
