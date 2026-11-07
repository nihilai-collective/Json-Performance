
----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1068.9 | 0.328353 | 414.408ms | 4630 | 640 | 117748 | 4130.91 | 0.1201 | 2.30201 | 1(Win) | true |
| Jsonifier (two-stage) | 1004.65 | 0.142591 | 442.241ms | 4630 | 40 | 1570.99 | 4395.07 | 0.00322341 | 2.44991 | 2(Loss) | true |
| Glaze | 766.426 | 0.0944433 | 582.226ms | 4630 | 40 | 1184.2 | 5761.18 | 0.1015 | 3.21612 | 3(Loss) | true |
| simdjson (ondemand) | 733.31 | 0.226502 | 606.924ms | 4630 | 1280 | 238091 | 6021.34 | 0.0129374 | 3.36105 | 4(Loss) | true |
