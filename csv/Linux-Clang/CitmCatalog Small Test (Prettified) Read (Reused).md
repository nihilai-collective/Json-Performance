
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2716.7 | 0.307752 | 970.589ms | 5839 | 640 | 25467 | 2049.73 | 0.320578 | 1.92165 | 7.92619 | 1.24645 | 0.000632065 | 3.79988e-05 | 1.09715e-05 | 1(Win) | true |
| Glaze STATISTICAL TIE | 2019.02 | 0.117133 | 1040.32ms | 5839 | 40 | 417.461 | 2758.03 | 0.0558663 | 2.54388 | 10.3523 | 1.94622 | 0.00143004 | 3.8534e-05 | 0 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 2009.26 | 0.282627 | 1041.42ms | 5839 | 2560 | 157062 | 2771.42 | 0.115106 | 2.55273 | 8.96695 | 1.85631 | 0.00136234 | 4.20797e-05 | 8.42931e-06 | 2(Tie) | true |
| simdjson (ondemand) | 1950.5 | 0.147509 | 1051.44ms | 5839 | 2560 | 45400.6 | 2854.92 | 0.00731962 | 2.63082 | 10.3281 | 1.54342 | 0.000620625 | 3.39848e-05 | 6.15474e-06 | 4(Loss) | true |
