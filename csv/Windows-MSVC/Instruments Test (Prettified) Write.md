
----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14662.5 | 0.151365 | 1425.68ms | 213963 | 4890 | 2.1698e+06 | 13916.5 | 0.0917014 | 0.168493 | 1(Win) | true |
| Glaze | 3666.81 | 0.186806 | 5586.55ms | 213963 | 2560 | 2.76645e+07 | 55648 | 0.013195 | 0.674857 | 2(Loss) | true |
