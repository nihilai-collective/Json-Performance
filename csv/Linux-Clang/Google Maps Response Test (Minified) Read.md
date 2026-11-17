
----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2482.41 | 0.0679695 | 1195.83ms | 11812 | 2560 | 24353.8 | 4537.85 | 0.0725915 | 2.05499 | 9.98112 | 1.74729 | 0.00366943 | 4.27267e-05 | 1.71634e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1824.93 | 0.0532568 | 1364.42ms | 11812 | 4890 | 52846.4 | 6172.74 | 0.173262 | 2.78711 | 13.4227 | 2.2914 | 0.00516504 | 4.03562e-05 | 1.64645e-05 | 2(Loss) | true |
| Glaze | 1792.26 | 0.0602143 | 1368.95ms | 11812 | 4890 | 70041.2 | 6285.25 | 0.00460887 | 2.84032 | 13.6889 | 2.65442 | 0.00105215 | 3.98887e-05 | 1.45428e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1054.31 | 0.0919939 | 1818.46ms | 11812 | 1280 | 123664 | 10684.6 | 0.0703938 | 4.81888 | 20.5064 | 3.40835 | 0.00796376 | 4.55707e-05 | 1.87839e-05 | 4(Loss) | true |
