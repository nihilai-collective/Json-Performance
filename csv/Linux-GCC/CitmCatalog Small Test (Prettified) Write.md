
----
### CitmCatalog Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16603.7 | 0.317291 | 760.339ms | 6938 | 40 | 63.9487 | 398.5 | 0.0251004 | 0.342563 | 1.0467 | 0.125829 | 0.000147737 | 3.24301e-05 | 0 | 1(Win) | true |
| Glaze | 2770.82 | 0.243703 | 964.807ms | 6960 | 1280 | 43624.8 | 2395.53 | 0.00736996 | 1.89052 | 4.28549 | 0.706322 | 0.00028803 | 3.69298e-05 | 1.11126e-05 | 2(Loss) | true |
| simdjson (reflection) | 517.893 | 0.0823422 | 2012.71ms | 6938 | 4890 | 541181 | 12776 | 0.109988 | 9.96082 | 38.5643 | 7.26074 | 0.0074562 | 0.000117989 | 4.96657e-05 | 3(Loss) | true |
