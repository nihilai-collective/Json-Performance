
----
### Minify Test Write (Reused) Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3707.28 | 0.0798467 | 6513.39ms | 466906 | 1280 | 1.17726e+07 | 120109 | 0.317693 | 1.35454 | 6.67669 | 0.888018 | 0.00193927 | 0.00127074 | 1.7703e-06 | 1(Win) | true |
| Glaze | 2648.96 | 0.0732269 | 9039.5ms | 466906 | 320 | 4.84843e+06 | 168095 | 0.0116131 | 1.90066 | 7.74607 | 1.47668 | 0.00261375 | 0.00082526 | 8.78121e-06 | 2(Loss) | true |
| simdjson (ondemand) | 1618.3 | 0.0808662 | 7243.24ms | 466906 | 640 | 3.16851e+07 | 275151 | 0.0619123 | 3.08771 | 12.5711 | 1.66791 | 0.00376087 | 0.10476 | 2.82511e-05 | 3(Loss) | true |
