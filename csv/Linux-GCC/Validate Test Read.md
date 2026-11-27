
----
### Validate Test Read Results [(Here is the data we used for this test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3035.77 | 0.173131 | 5131.23ms | 631514 | 80 | 9.43771e+06 | 198387 | 0.0429206 | 0.815405 | 1(Win) | true |
| Glaze | 2450.79 | 0.096634 | 6424.97ms | 631514 | 320 | 1.80453e+07 | 245741 | 0.104565 | 1.0101 | 2(Loss) | true |
