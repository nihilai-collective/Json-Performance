
----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5290.64 | 0.0556445 | 5558.47ms | 9930848 | 40 | 3.96881e+07 | 1.7901e+06 | 0.205118 | 0.467952 | 1(Win) | true |
| Glaze | 3029.08 | 0.23109 | 9679.05ms | 9930228 | 80 | 4.17589e+09 | 3.12643e+06 | 0.391164 | 0.817275 | 2(Loss) | true |
