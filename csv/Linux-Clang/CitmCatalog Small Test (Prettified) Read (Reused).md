
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3237.31 | 0.0912182 | 189.462ms | 5839 | 80 | 196.952 | 1720.1 | 0.364676 | 0.752789 | 1(Win) | true |
| Jsonifier | 3112.85 | 0.0608739 | 199.6ms | 5839 | 160 | 189.733 | 1788.88 | 0.138861 | 0.784058 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 2063.26 | 0.039995 | 291.365ms | 5839 | 320 | 372.845 | 2698.88 | 0.00995882 | 1.18838 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2062.39 | 0.114112 | 295.514ms | 5839 | 40 | 379.717 | 2700.03 | 0.0496662 | 1.1891 | 3(Tie) | true |
