
----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21618.2 | 0.319596 | 2130.02ms | 466906 | 320 | 1.38667e+06 | 20597.3 | 0.0464499 | 0.114363 | 1(Win) | true |
| simdjson (ondemand) | 17080.9 | 0.204549 | 2607.81ms | 466906 | 1280 | 3.63949e+06 | 26068.7 | 0.247317 | 0.144762 | 2(Loss) | true |
| Glaze | 2661.79 | 0.0933138 | 8669.54ms | 466906 | 320 | 7.79745e+06 | 167284 | 0.091949 | 0.929946 | 3(Loss) | true |
