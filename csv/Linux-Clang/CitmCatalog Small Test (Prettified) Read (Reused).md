
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2950.62 | 0.211061 | 956.349ms | 5839 | 30 | 475.978 | 1887.23 | 0.190392 | 1.78487 | 7.503 | 1.43364 | 0.000588 | 0.000165553 | 8.56311e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2678.23 | 0.135631 | 969.124ms | 5839 | 2560 | 20358 | 2079.17 | 0.112062 | 1.92729 | 8.23566 | 1.29509 | 0.000610791 | 3.31152e-05 | 8.69691e-06 | 2(Loss) | true |
| Glaze | 2046.07 | 0.170675 | 1031.19ms | 5839 | 30 | 647.289 | 2721.57 | 0.0709871 | 2.50883 | 10.3523 | 1.94622 | 0.0015699 | 1.14175e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 1945.67 | 0.138692 | 1048.04ms | 5839 | 1280 | 20167.4 | 2862 | 0.175009 | 2.66412 | 10.4254 | 1.52663 | 0.000793827 | 3.57242e-05 | 5.21815e-06 | 4(Loss) | true |
