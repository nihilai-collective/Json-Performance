
----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22741.4 | 0.0929232 | 2040.66ms | 466906 | 30 | 9931.03 | 19580 | 0.440678 | 0.108619 | 1(Win) | true |
| simdjson (ondemand) | 20488.6 | 0.218829 | 2242.52ms | 466906 | 2560 | 5.79006e+06 | 21732.9 | 0.314986 | 0.12066 | 2(Loss) | true |
| Glaze | 1991.76 | 0.228092 | 6002.96ms | 466906 | 160 | 4.16029e+07 | 223559 | 0.19086 | 1.24282 | 3(Loss) | true |
