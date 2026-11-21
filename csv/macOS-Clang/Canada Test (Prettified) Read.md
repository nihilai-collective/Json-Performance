
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1345.7 | 0.79591 | 5731.7ms | 5373214 | 80 | 7.3483e+10 | 3.80789e+06 | 1.05299 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1220.37 | 1.35768 | 6070.77ms | 5373214 | 30 | 9.7499e+10 | 4.19897e+06 | 0.172001 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1193.97 | 0.0793523 | 6561.38ms | 5373214 | 40 | 4.63939e+08 | 4.29181e+06 | 0.615578 | 2(Tie) | true |
| Glaze | 1114.67 | 1.22973 | 6975.83ms | 5373214 | 30 | 9.58766e+10 | 4.59713e+06 | 0.102132 | 4(Loss) | true |
