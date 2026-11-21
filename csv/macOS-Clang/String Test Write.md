
----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1227.62 | 0.0690972 | 717.202ms | 9578 | 40 | 1057.31 | 7440.65 | 0.511293 | 1(Win) | true |
| Glaze | 1095.09 | 0.0684306 | 937.559ms | 9578 | 80 | 2606.4 | 8341.14 | 0.0810084 | 2(Loss) | true |
