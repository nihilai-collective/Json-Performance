
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1172.78 | 0.4509 | 85.135ms | 905 | 80 | 880.88 | 735.925 | 0.0611102 | 1(Win) | true |
| Glaze | 1047.75 | 0.582209 | 95.666ms | 905 | 4890 | 112472 | 823.739 | 1.81933 | 2(Loss) | true |
| Jsonifier (two-stage) | 290.578 | 0.677635 | 298.401ms | 905 | 320 | 129633 | 2970.2 | 0.355931 | 3(Loss) | true |
| simdjson (ondemand) | 163.431 | 0.395156 | 537.748ms | 905 | 1280 | 557412 | 5280.98 | 0.0096168 | 4(Loss) | true |
