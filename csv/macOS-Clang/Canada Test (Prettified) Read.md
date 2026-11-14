
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1668.51 | 0.18029 | 9577.78ms | 5373214 | 160 | 4.90537e+09 | 3.07118e+06 | 0.367565 | 1(Win) | true |
| Jsonifier (two-stage) | 1586.09 | 0.276694 | 10055.9ms | 5373214 | 160 | 1.27859e+10 | 3.23077e+06 | 0.237739 | 2(Loss) | true |
| Glaze | 1218.72 | 0.129653 | 6325.54ms | 5373214 | 80 | 2.37744e+09 | 4.20464e+06 | 0.0529779 | 3(Loss) | true |
| simdjson (ondemand) | 1189.5 | 0.128075 | 6533.64ms | 5373214 | 80 | 2.43532e+09 | 4.30792e+06 | 0.0197823 | 4(Loss) | true |
