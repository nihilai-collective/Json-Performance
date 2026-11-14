
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2671.16 | 0.11164 | 5230.88ms | 1151920 | 160 | 3.3729e+07 | 411266 | 0.0736075 | 1.1377 | 1(Win) | true |
| Jsonifier | 2375.59 | 0.120464 | 5863.88ms | 1151920 | 160 | 4.96517e+07 | 462436 | 0.0517372 | 1.27929 | 2(Loss) | true |
| Glaze | 1635.11 | 0.0965397 | 8530.2ms | 1151920 | 160 | 6.73107e+07 | 671856 | 0.0635771 | 1.85867 | 3(Loss) | true |
| simdjson (ondemand) | 1360.8 | 0.230873 | 5088.69ms | 1151920 | 80 | 2.77903e+08 | 807288 | 0.00774138 | 2.23336 | 4(Loss) | true |
