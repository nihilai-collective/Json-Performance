
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1709.73 | 0.371397 | 9451ms | 5373214 | 160 | 1.98248e+10 | 2.99713e+06 | 0.781443 | 1.44806 | 1(Win) | true |
| Jsonifier | 1681.14 | 0.0598383 | 9543ms | 5373214 | 80 | 2.66139e+08 | 3.04811e+06 | 0.267596 | 1.47269 | 2(Loss) | true |
| simdjson (ondemand) | 1572.79 | 0.0827591 | 10150.4ms | 5373214 | 40 | 2.90817e+08 | 3.2581e+06 | 0.162119 | 1.57416 | 3(Loss) | true |
| simdjson (reflection) | 1568.23 | 0.0585709 | 10153.4ms | 5373214 | 80 | 2.93025e+08 | 3.26758e+06 | 0.321757 | 1.57874 | 4(Loss) | true |
| Glaze | 1521.25 | 0.0894016 | 5030.53ms | 5373214 | 40 | 3.62759e+08 | 3.36848e+06 | 0.739956 | 1.62749 | 5(Loss) | true |
