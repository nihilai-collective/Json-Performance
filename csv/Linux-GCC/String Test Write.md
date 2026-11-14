
----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4323.16 | 0.348287 | 941.133ms | 9578 | 40 | 2166.11 | 2112.88 | 0.0563685 | 1.21502 | 5.37764 | 1.07622 | 0.00253445 | 6.26436e-05 | 3.13218e-05 | 1(Win) | true |
| simdjson (reflection) | 4194.54 | 0.0928007 | 942.76ms | 9578 | 1280 | 5227.5 | 2177.66 | 0.0346319 | 1.25325 | 6.23815 | 1.16235 | 0.000562569 | 3.24637e-05 | 7.58574e-06 | 2(Loss) | true |
| Glaze | 2202.42 | 0.11425 | 1143.48ms | 9578 | 640 | 14369.5 | 4147.39 | 0.0050481 | 2.36104 | 12.677 | 2.62539 | 0.000875052 | 2.83854e-05 | 8.80925e-06 | 3(Loss) | true |
