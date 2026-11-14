
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2189.05 | 0.0886508 | 7237.95ms | 631514 | 640 | 3.80715e+07 | 275123 | 0.082861 | 2.30735 | 7.30199 | 1.15229 | 0.0122009 | 0.0348996 | 9.65364e-05 | 1(Win) | true |
| Glaze | 2022.95 | 0.0497179 | 7805.61ms | 631514 | 640 | 1.40216e+07 | 297712 | 0.0324049 | 2.49703 | 9.09149 | 1.66455 | 0.0114079 | 0.0187992 | 5.89481e-05 | 2(Loss) | true |
| Jsonifier | 1577.69 | 0.0968327 | 9976.52ms | 631514 | 320 | 4.37239e+07 | 381735 | 0.0920038 | 3.20506 | 7.97122 | 1.53396 | 0.0103473 | 0.0256684 | 0.000334118 | 3(Loss) | true |
| simdjson (ondemand) | 1233.92 | 0.123486 | 6326.3ms | 631514 | 320 | 1.16245e+08 | 488084 | 0.129942 | 4.06628 | 13.7943 | 2.36388 | 0.0101586 | 0.0412706 | 0.000180533 | 4(Loss) | true |
