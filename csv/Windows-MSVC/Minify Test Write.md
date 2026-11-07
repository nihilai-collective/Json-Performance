
----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4058.09 | 0.345421 | 5872.6ms | 466906 | 160 | 2.29844e+07 | 109726 | 0.709777 | 0.609885 | 1(Win) | true |
| Glaze | 1834.98 | 0.139736 | 6283.4ms | 466906 | 320 | 3.67929e+07 | 242661 | 0.0670108 | 1.34909 | 2(Loss) | true |
| simdjson (ondemand) | 1406.15 | 0.121871 | 8186.29ms | 466906 | 320 | 4.76594e+07 | 316664 | 0.0594436 | 1.76044 | 3(Loss) | true |
