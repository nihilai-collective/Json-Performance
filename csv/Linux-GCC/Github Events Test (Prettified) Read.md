
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1883.43 | 0.0329673 | 4044.74ms | 65103 | 4890 | 577535 | 32964.9 | 0.278382 | 2.72513 | 9.17213 | 1.57522 | 0.0103263 | 4.37784e-05 | 3.18043e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1858.02 | 0.0362144 | 4079.29ms | 65103 | 2560 | 374891 | 33415.7 | 0.120964 | 2.75067 | 9.15867 | 1.49313 | 0.0101084 | 6.86772e-05 | 5.5951e-05 | 2(Loss) | true |
| Jsonifier | 1731.26 | 0.0638796 | 4334.09ms | 65103 | 640 | 335877 | 35862.3 | 0.205407 | 2.9502 | 9.22254 | 1.68632 | 0.00914553 | 2.93285e-05 | 1.92723e-05 | 3(Loss) | true |
| Glaze | 1667.34 | 0.0421553 | 4462.51ms | 65103 | 2560 | 630810 | 37237.2 | 0.068844 | 3.07012 | 10.7723 | 2.11741 | 0.0133521 | 4.68188e-05 | 3.36186e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1595.83 | 0.0666192 | 4626.68ms | 65103 | 640 | 429939 | 38905.8 | 0.00844919 | 3.20541 | 9.4759 | 1.72305 | 0.0113166 | 3.32406e-05 | 2.49364e-05 | 5(Loss) | true |
