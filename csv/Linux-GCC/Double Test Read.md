
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1392.49 | 0.0769328 | 131.066ms | 1811 | 320 | 291.359 | 1240.3 | 0.180473 | 1.73929 | 1(Win) | true |
| Glaze | 1000.77 | 0.49776 | 175.149ms | 1811 | 640 | 47227.2 | 1725.78 | 0.372891 | 2.43456 | 2(Loss) | true |
| simdjson (ondemand) | 381.944 | 0.134977 | 454.37ms | 1811 | 40 | 1490.11 | 4521.88 | 0.147834 | 6.44041 | 3(Loss) | true |
| simdjson (reflection) | 360.269 | 0.50509 | 476.705ms | 1811 | 640 | 375232 | 4793.93 | 0.276732 | 6.83224 | 4(Loss) | true |
