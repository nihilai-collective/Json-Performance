
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1846.42 | 0.0497411 | 1223.94ms | 9578 | 4890 | 29609.3 | 4947.03 | 0.151086 | 2.77816 | 14.0799 | 2.70854 | 0.00123568 | 3.89227e-05 | 1.3387e-05 | 1(Win) | true |
| simdjson (ondemand) | 1421.08 | 0.0431934 | 1381.04ms | 9578 | 4890 | 37692.8 | 6427.73 | 0.182362 | 3.59271 | 17.5818 | 2.96628 | 0.0039105 | 2.40625e-05 | 6.02096e-06 | 2(Loss) | true |
| Glaze | 1416.51 | 0.0356216 | 1381.59ms | 9578 | 4890 | 25801.7 | 6448.47 | 0.320544 | 3.62322 | 17.8633 | 3.53947 | 0.00133003 | 2.10733e-05 | 2.90372e-06 | 3(Loss) | true |
| Jsonifier (two-stage) | 1368.21 | 0.0670554 | 1398.7ms | 9578 | 4890 | 97998.5 | 6676.08 | 0.196422 | 3.75827 | 18.2534 | 3.09835 | 0.00165916 | 3.36917e-05 | 1.11452e-05 | 4(Loss) | true |
