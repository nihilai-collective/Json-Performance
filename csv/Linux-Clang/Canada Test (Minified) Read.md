
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1007.75 | 0.0660805 | 6701.34ms | 2251027 | 80 | 1.58525e+08 | 2.13025e+06 | 0.463701 | 2.45674 | 1(Win) | true |
| Jsonifier (two-stage) | 923.635 | 0.424926 | 7362.31ms | 2251027 | 30 | 2.92623e+09 | 2.32424e+06 | 0.838294 | 2.68045 | 2(Loss) | true |
| Glaze | 766.57 | 0.101556 | 8746.38ms | 2251027 | 40 | 3.23541e+08 | 2.80046e+06 | 0.0529291 | 3.2297 | 3(Loss) | true |
| simdjson (ondemand) | 750.193 | 0.146216 | 8995.13ms | 2251027 | 30 | 5.25201e+08 | 2.86159e+06 | 0.0529694 | 3.30019 | 4(Loss) | true |
