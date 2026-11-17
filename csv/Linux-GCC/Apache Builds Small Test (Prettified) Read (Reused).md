
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2866.91 | 0.144771 | 856.566ms | 3370 | 80 | 210.708 | 1121.03 | 0.0267541 | 1.82831 | 7.6635 | 1.07745 | 0.000593472 | 4.82196e-05 | 1.8546e-05 | 1(Win) | true |
| Jsonifier | 2612.07 | 0.0796997 | 853.211ms | 3370 | 2560 | 2461.75 | 1230.4 | 0.415435 | 2.02857 | 7.56944 | 1.32433 | 0.00106442 | 3.4426e-05 | 1.30981e-05 | 2(Loss) | true |
| Glaze | 2500.2 | 0.0516793 | 867.335ms | 3370 | 4890 | 2158 | 1285.45 | 0.0404281 | 2.08329 | 9.15015 | 1.69021 | 0.00105332 | 2.74283e-05 | 8.13141e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2466.71 | 0.0703791 | 873.274ms | 3370 | 2560 | 2152.54 | 1302.9 | 0.0871691 | 2.11081 | 7.38279 | 1.26558 | 0.00103 | 6.10859e-05 | 2.26029e-05 | 4(Loss) | true |
| simdjson (reflection) | 2428.79 | 0.0533941 | 873.847ms | 3370 | 4890 | 2441.04 | 1323.24 | 0.183856 | 2.14472 | 7.18368 | 1.08012 | 0.00105532 | 4.80603e-05 | 1.04373e-05 | 5(Loss) | true |
