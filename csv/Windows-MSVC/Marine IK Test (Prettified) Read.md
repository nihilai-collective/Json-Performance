
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2247.83 | 0.232921 | 9896.86ms | 7351818 | 30 | 1.58344e+09 | 3.11911e+06 | 0.329165 | 1.10141 | 1(Win) | true |
| Jsonifier | 2112.04 | 0.206685 | 5025.67ms | 7351818 | 80 | 3.76612e+09 | 3.31965e+06 | 0.353901 | 1.17222 | 2(Loss) | true |
| simdjson (ondemand) | 820.701 | 0.370344 | 6042.15ms | 7351818 | 30 | 3.00297e+10 | 8.54299e+06 | 0.118826 | 3.01671 | 3(Loss) | true |
| Glaze | 753.769 | 0.499693 | 6524.24ms | 7351818 | 40 | 8.64132e+10 | 9.30158e+06 | 0.00154994 | 3.28457 | 4(Loss) | true |
