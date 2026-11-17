
----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2524.76 | 0.118509 | 830.942ms | 2632 | 4890 | 6788.05 | 994.182 | 0.0658879 | 2.08425 | 7.97113 | 1.38032 | 0.000770601 | 5.53981e-05 | 1.11884e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2171.12 | 0.113104 | 852.415ms | 2632 | 4890 | 8361.23 | 1156.12 | 0.0266647 | 2.41815 | 9.68503 | 1.69871 | 0.00103578 | 4.78615e-05 | 7.14814e-06 | 2(Loss) | true |
| Glaze | 1924.29 | 0.132865 | 871.347ms | 2632 | 2560 | 7689.37 | 1304.41 | 0.343053 | 2.70824 | 11.4096 | 2.14514 | 0.00118271 | 6.85672e-05 | 9.64689e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1369.5 | 0.0867732 | 940.935ms | 2632 | 4890 | 12368.8 | 1832.84 | 0.0296737 | 3.77566 | 12.9058 | 2.2405 | 0.00553686 | 8.80309e-05 | 1.49956e-05 | 4(Loss) | true |
