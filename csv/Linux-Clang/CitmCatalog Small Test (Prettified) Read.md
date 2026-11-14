
----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2343.33 | 0.101288 | 974.021ms | 5839 | 4890 | 28329.5 | 2376.33 | 0.0976889 | 2.19751 | 8.7652 | 1.46189 | 0.000625615 | 4.60902e-05 | 1.35189e-05 | 1(Win) | true |
| Jsonifier | 1802.79 | 0.539467 | 1044.93ms | 5839 | 640 | 177704 | 3088.82 | 0.166095 | 2.84243 | 9.8486 | 2.08032 | 0.00144048 | 3.8534e-05 | 4.28156e-06 | 2(Loss) | true |
| Glaze | 1773.63 | 0.226216 | 1048.49ms | 5839 | 320 | 16141.6 | 3139.6 | 0.0473014 | 2.88827 | 11.2622 | 2.17503 | 0.00197112 | 1.44502e-05 | 2.14078e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1727.54 | 0.134226 | 1061.05ms | 5839 | 2560 | 47921.5 | 3223.37 | 0.194668 | 2.96245 | 11.1934 | 1.75989 | 0.00102991 | 3.49883e-05 | 8.63001e-06 | 4(Loss) | true |
