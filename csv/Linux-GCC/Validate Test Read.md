
----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3133.27 | 0.177579 | 9708.53ms | 631514 | 1280 | 1.49129e+08 | 192214 | 0.901406 | 0.790028 | 1(Win) | true |
| Glaze | 2419.77 | 0.207945 | 6449.58ms | 631514 | 40 | 1.07145e+07 | 248891 | 0.0353243 | 1.02307 | 2(Loss) | true |
