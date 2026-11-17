
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2101.45 | 0.171838 | 894.507ms | 3223 | 80 | 505.37 | 1462.65 | 0.0923835 | 2.52028 | 10.0689 | 1.65622 | 0.00107431 | 3.1027e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 1655.17 | 0.0630018 | 935.147ms | 3223 | 4890 | 6693.45 | 1857.02 | 0.0274909 | 3.15617 | 12.6292 | 2.00528 | 0.00134787 | 6.97314e-05 | 1.48473e-05 | 2(Loss) | true |
| Glaze | 1566.46 | 0.0640743 | 953.216ms | 3223 | 4890 | 7729.66 | 1962.19 | 0.289763 | 3.28433 | 13.0661 | 2.43376 | 0.00123556 | 3.28036e-05 | 7.67744e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1396.87 | 0.137512 | 973.167ms | 3223 | 640 | 5859.66 | 2200.41 | 0.116107 | 3.68339 | 14.1952 | 2.34595 | 0.00142821 | 0.000143015 | 5.4782e-05 | 4(Loss) | true |
| simdjson (reflection) | 1305.7 | 0.0571687 | 996.225ms | 3223 | 4890 | 8856.5 | 2354.06 | 0.19865 | 3.95025 | 14.2248 | 2.29103 | 0.00115365 | 0.000103741 | 2.73469e-05 | 5(Loss) | true |
