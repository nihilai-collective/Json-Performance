
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2342.82 | 0.126896 | 916.102ms | 3223 | 80 | 221.733 | 1311.96 | 0.261327 | 2.22903 | 9.47161 | 1.56035 | 0.00108207 | 1.93919e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 1714.15 | 0.111931 | 928.941ms | 3223 | 80 | 322.263 | 1793.12 | 0.115586 | 3.07478 | 12.9978 | 2.04902 | 0.00117903 | 7.75675e-05 | 1.55135e-05 | 2(Loss) | true |
| Glaze | 1610.97 | 0.140307 | 942.981ms | 3223 | 80 | 573.316 | 1907.97 | 0.0301276 | 3.26628 | 13.0661 | 2.43376 | 0.00127986 | 5.04189e-05 | 7.75675e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1401.84 | 0.0462295 | 971.53ms | 3223 | 4890 | 5024.23 | 2192.61 | 0.0406439 | 3.70463 | 14.112 | 2.34905 | 0.00169234 | 0.000160465 | 6.87162e-05 | 4(Loss) | true |
| simdjson (reflection) | 1381.12 | 0.0764089 | 975.343ms | 3223 | 2560 | 7402.6 | 2225.5 | 0.13801 | 3.7401 | 13.892 | 2.25039 | 0.00160286 | 0.00014653 | 5.15097e-05 | 5(Loss) | true |
