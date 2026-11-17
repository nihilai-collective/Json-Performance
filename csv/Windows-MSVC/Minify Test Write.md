
----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3168.6 | 0.0315483 | 7214.26ms | 466906 | 2560 | 5.03173e+06 | 140528 | 0.00111189 | 0.959076 | 1(Win) | true |
| Glaze | 1765.5 | 0.0286575 | 6428.2ms | 466906 | 640 | 3.34332e+06 | 252209 | 0.0645962 | 1.72143 | 2(Loss) | true |
| simdjson (ondemand) | 1452.63 | 0.239161 | 7867.45ms | 466906 | 80 | 4.29953e+07 | 306531 | 0.0191697 | 2.09197 | 3(Loss) | true |
