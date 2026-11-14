
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2577.23 | 0.037412 | 3871.48ms | 83958 | 4890 | 660616 | 31067.7 | 0.0253656 | 1.95553 | 8.76062 | 1.44207 | 0.00256496 | 2.19873e-05 | 1.16598e-05 | 1(Win) | true |
| Glaze | 2420.16 | 0.0878152 | 4062.55ms | 83958 | 320 | 270100 | 33084 | 0.0342522 | 2.09026 | 9.97514 | 2.07256 | 0.00422726 | 2.00249e-05 | 9.97523e-06 | 2(Loss) | true |
| simdjson (reflection) | 2255.45 | 0.0200374 | 4301.78ms | 83958 | 4890 | 247427 | 35500 | 0.0597502 | 2.23766 | 9.73046 | 1.63279 | 0.00296765 | 2.15659e-05 | 1.25684e-05 | 3(Loss) | true |
| Jsonifier | 2227.46 | 0.0347251 | 4366.87ms | 83958 | 160 | 24929.4 | 35946.1 | 0.00716401 | 2.27213 | 8.89125 | 1.83539 | 0.00461682 | 2.38214e-05 | 1.54095e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1906.46 | 0.107181 | 4957.96ms | 83958 | 320 | 648410 | 41998.5 | 0.295615 | 2.65473 | 10.5582 | 1.89162 | 0.00600289 | 1.54467e-05 | 6.96033e-06 | 5(Loss) | true |
