
----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2856.98 | 0.0425603 | 614.968ms | 18245 | 80 | 537.493 | 6090.27 | 0.113835 | 0.86281 | 1(Win) | true |
| Jsonifier | 2319.98 | 0.0431649 | 756.312ms | 18245 | 80 | 838.443 | 7499.99 | 0.137311 | 1.06354 | 2(Loss) | true |
| simdjson (ondemand) | 1949.36 | 0.185325 | 895.167ms | 18245 | 1280 | 350253 | 8925.9 | 0.193051 | 1.26636 | 3(Loss) | true |
| Glaze | 1824.38 | 0.0822767 | 971.208ms | 18245 | 30 | 1847.27 | 9537.37 | 0.36633 | 1.3535 | 4(Loss) | true |
