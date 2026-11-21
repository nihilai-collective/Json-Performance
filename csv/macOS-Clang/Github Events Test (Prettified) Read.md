
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1838.57 | 0.141771 | 3511ms | 65103 | 640 | 1.46688e+06 | 33769.2 | 0.104026 | 1(Win) | true |
| Jsonifier (two-stage) | 1765.2 | 0.0716605 | 3573.18ms | 65103 | 4890 | 3.10657e+06 | 35172.8 | 0.0692827 | 2(Loss) | true |
| Glaze | 1678.27 | 0.215877 | 3841.78ms | 65103 | 320 | 2.04099e+06 | 36994.7 | 0.078421 | 3(Loss) | true |
| simdjson (ondemand) | 1073.44 | 0.0410552 | 5865.73ms | 65103 | 40 | 22555.1 | 57839.4 | 0.150219 | 4(Loss) | true |
