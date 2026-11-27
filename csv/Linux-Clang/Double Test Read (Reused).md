
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1341.02 | 0.205218 | 845.554ms | 1811 | 320 | 2235.37 | 1287.91 | 0.0174733 | 3.97266 | 19.2093 | 3.92159 | 0.000947336 | 8.45527e-05 | 3.45113e-06 | 1(Win) | true |
| Glaze | 910.312 | 0.0866011 | 908.137ms | 1811 | 2560 | 6911.04 | 1897.27 | 0.0159177 | 5.78352 | 29.0337 | 4.45334 | 0.00115074 | 0.00016889 | 2.6962e-05 | 2(Loss) | true |
| simdjson (ondemand) | 461.039 | 0.107095 | 1098.98ms | 1811 | 1280 | 20602.1 | 3746.11 | 0.0710824 | 11.2928 | 58.2435 | 11.2082 | 0.000677285 | 0.000104828 | 1.63929e-05 | 3(Loss) | true |
