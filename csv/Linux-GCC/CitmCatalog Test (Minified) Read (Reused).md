
----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2929.05 | 0.109376 | 5271.13ms | 500299 | 30 | 952295 | 162893 | 0.171223 | 1.72438 | 8.56693 | 1.45078 | 0.00720856 | 0.00409468 | 1.95217e-05 | 1(Win) | true |
| Glaze STATISTICAL TIE | 2152.19 | 0.159364 | 6830.06ms | 500299 | 30 | 3.74457e+06 | 221692 | 0.052262 | 2.34732 | 10.5102 | 1.99256 | 0.00935527 | 0.00280033 | 1.91885e-05 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2149.92 | 0.355222 | 6819.43ms | 500299 | 640 | 3.97734e+08 | 221925 | 0.0400718 | 2.3351 | 11.29 | 1.83227 | 0.00991487 | 0.0311602 | 3.05442e-05 | 2(Tie) | true |
| simdjson (ondemand) | 1734.02 | 0.399821 | 8034.68ms | 500299 | 1280 | 1.54914e+09 | 275154 | 0.985899 | 2.91349 | 13.1091 | 2.15034 | 0.00883992 | 0.0139295 | 2.73571e-05 | 4(Loss) | true |
| simdjson (reflection) | 1682.55 | 0.0855348 | 8398.08ms | 500299 | 80 | 4.70652e+06 | 283571 | 0.0758409 | 3.00228 | 13.1292 | 2.17396 | 0.0104877 | 0.0137749 | 2.72337e-05 | 5(Loss) | true |
