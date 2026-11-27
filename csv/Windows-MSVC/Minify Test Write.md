
----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22081.6 | 0.381413 | 2034.77ms | 466906 | 320 | 1.89294e+06 | 20165 | 0.812398 | 0.111945 | 1(Win) | true |
| simdjson (ondemand) | 20311.1 | 0.376594 | 2191.78ms | 466906 | 640 | 4.36233e+06 | 21922.8 | 1.32738 | 0.121748 | 2(Loss) | true |
| Glaze | 1668.42 | 0.197924 | 6876.18ms | 466906 | 160 | 4.46441e+07 | 266884 | 0.129336 | 1.48376 | 3(Loss) | true |
