
----
### CitmCatalog Small Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15132.4 | 0.0838387 | 779.441ms | 6938 | 640 | 86.0047 | 437.247 | 0.0906845 | 0.365709 | 1.04036 | 0.159988 | 0.000144134 | 1.23865e-05 | 4.50418e-07 | 1(Win) | true |
| Glaze | 3029.27 | 0.147861 | 953.07ms | 6960 | 4890 | 51328.8 | 2191.15 | 0.32822 | 1.70246 | 4.30421 | 0.71092 | 0.00033757 | 6.39647e-05 | 2.5533e-05 | 2(Loss) | true |
| simdjson (reflection) | 488.095 | 0.188107 | 2101.35ms | 6938 | 640 | 416152 | 13556 | 0.19724 | 10.3821 | 39.0824 | 7.32733 | 0.00775935 | 6.84635e-05 | 3.42318e-05 | 3(Loss) | true |
