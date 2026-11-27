
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3136.31 | 0.120866 | 921.775ms | 5839 | 1280 | 5894.67 | 1775.5 | 0.137756 | 1.67873 | 7.04675 | 1.24131 | 0.00063086 | 3.63932e-05 | 7.35892e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2792.92 | 0.0760169 | 942.28ms | 5839 | 4890 | 11232.8 | 1993.79 | 0.059347 | 1.87995 | 7.93852 | 1.1865 | 0.000636332 | 4.4269e-05 | 6.09399e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2439.52 | 0.0634163 | 974.143ms | 5839 | 2560 | 5364.26 | 2282.62 | 0.0379422 | 2.15179 | 8.38106 | 1.32103 | 0.000943213 | 4.26149e-05 | 8.09482e-06 | 3(Loss) | true |
| simdjson (reflection) | 2380.39 | 0.152128 | 985.114ms | 5839 | 80 | 1013.18 | 2339.32 | 0.0181643 | 2.20256 | 8.32899 | 1.28224 | 0.0011132 | 3.21117e-05 | 4.28156e-06 | 4(Loss) | true |
| Glaze | 2014.99 | 0.151413 | 1015.69ms | 5839 | 320 | 5602.83 | 2763.54 | 0.000904646 | 2.5918 | 10.3408 | 1.91985 | 0.00138027 | 2.99709e-05 | 1.07039e-05 | 5(Loss) | true |
