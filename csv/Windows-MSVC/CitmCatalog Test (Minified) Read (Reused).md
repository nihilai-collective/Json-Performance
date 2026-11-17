
----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1513.99 | 0.100495 | 9228.88ms | 500299 | 640 | 6.4192e+07 | 315142 | 0.0627094 | 1.63511 | 1(Win) | true |
| Jsonifier (two-stage) | 1263.95 | 0.366222 | 5373.78ms | 500299 | 160 | 3.05779e+08 | 377484 | 0.31041 | 1.9586 | 2(Loss) | true |
| Glaze | 817.747 | 0.15565 | 7964.82ms | 500299 | 160 | 1.3196e+08 | 583459 | 0.399135 | 3.02744 | 3(Loss) | true |
| simdjson (ondemand) | 540.777 | 0.623309 | 5819.44ms | 500299 | 320 | 9.67785e+09 | 882290 | 2.37387 | 4.57802 | 4(Loss) | true |
