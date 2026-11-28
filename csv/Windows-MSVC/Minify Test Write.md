
----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 24585.2 | 0.327661 | 1856.1ms | 466906 | 2560 | 9.01567e+06 | 18111.5 | 0.405762 | 0.100536 | 1(Win) | true |
| simdjson (ondemand) | 22005.2 | 0.522164 | 2076.27ms | 466906 | 1280 | 1.429e+07 | 20235.1 | 0.310215 | 0.112342 | 2(Loss) | true |
| Glaze | 1973.7 | 0.824887 | 5748.08ms | 466906 | 80 | 2.77062e+08 | 225605 | 0.0741897 | 1.25421 | 3(Loss) | true |
