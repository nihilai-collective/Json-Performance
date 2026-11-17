
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3584.95 | 0.243349 | 7854.54ms | 1151920 | 30 | 1.66824e+07 | 306435 | 0.394937 | 0.690499 | 1(Win) | true |
| Jsonifier | 2949.04 | 0.192706 | 9692.42ms | 1151920 | 1280 | 6.59603e+08 | 372513 | 0.193678 | 0.839429 | 2(Loss) | true |
| Glaze | 2288.52 | 0.237698 | 6160.73ms | 1151920 | 80 | 1.04154e+08 | 480030 | 0.0859832 | 1.08174 | 3(Loss) | true |
| simdjson (ondemand) | 2234.55 | 0.10045 | 6329.77ms | 1151920 | 160 | 3.90193e+07 | 491622 | 0.100074 | 1.10787 | 4(Loss) | true |
