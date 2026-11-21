
----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2758.48 | 0.185264 | 5306.21ms | 500299 | 80 | 8.21472e+06 | 172965 | 0.177837 | 0.897373 | 1(Win) | true |
| Jsonifier (two-stage) | 2248.07 | 0.16903 | 6366.49ms | 500299 | 160 | 2.05914e+07 | 212237 | 0.142317 | 1.10114 | 2(Loss) | true |
| Glaze | 1719.78 | 0.516729 | 7747.81ms | 500299 | 160 | 3.28822e+08 | 277433 | 0.680582 | 1.43947 | 3(Loss) | true |
| simdjson (ondemand) | 1268.8 | 0.308473 | 5406.77ms | 500299 | 30 | 4.03669e+07 | 376041 | 0.270781 | 1.95114 | 4(Loss) | true |
