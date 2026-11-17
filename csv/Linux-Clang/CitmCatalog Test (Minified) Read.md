
----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1280.96 | 0.205876 | 9669.14ms | 500299 | 80 | 4.7042e+07 | 372471 | 0.452056 | 1.93259 | 1(Win) | true |
| simdjson (ondemand) | 1192.96 | 0.0789085 | 5114.43ms | 500299 | 640 | 6.37436e+07 | 399949 | 0.179654 | 2.07514 | 2(Loss) | true |
