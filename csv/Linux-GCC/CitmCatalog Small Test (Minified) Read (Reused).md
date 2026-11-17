
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1873.12 | 0.0841406 | 181.283ms | 3223 | 40 | 76.2538 | 1640.95 | 0.153132 | 1.29936 | 1(Win) | true |
| Jsonifier (two-stage) | 1737.53 | 0.109768 | 196.922ms | 3223 | 80 | 301.646 | 1769 | 0.0792034 | 1.40343 | 2(Loss) | true |
| Glaze | 1519.07 | 0.216661 | 220.18ms | 3223 | 4890 | 93980.1 | 2023.41 | 0.104473 | 1.60676 | 3(Loss) | true |
| simdjson (ondemand) | 1508.17 | 0.072342 | 232.78ms | 3223 | 40 | 86.9481 | 2038.03 | 0.0657884 | 1.61965 | 4(Loss) | true |
| simdjson (reflection) | 1355.44 | 0.104728 | 252.092ms | 3223 | 80 | 451.209 | 2267.68 | 0.252922 | 1.80327 | 5(Loss) | true |
