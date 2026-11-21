
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1697.35 | 0.125497 | 9769.44ms | 5373214 | 80 | 1.14837e+09 | 3.01899e+06 | 1.85002 | 1.45862 | 1(Win) | true |
| Jsonifier (two-stage) | 1661.13 | 0.154888 | 9617.47ms | 5373214 | 160 | 3.65274e+09 | 3.08483e+06 | 2.04426 | 1.49037 | 2(Loss) | true |
| Jsonifier | 1646.94 | 0.191554 | 9652.68ms | 5373214 | 40 | 1.42087e+09 | 3.11141e+06 | 0.242556 | 1.50326 | 3(Loss) | true |
| Glaze | 1575.31 | 0.210207 | 10173ms | 5373214 | 160 | 7.48082e+09 | 3.25288e+06 | 0.854518 | 1.57162 | 4(Loss) | true |
