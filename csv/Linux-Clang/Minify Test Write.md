
----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 23663.4 | 0.0698191 | 1993.84ms | 466906 | 30 | 5178.13 | 18817.1 | 0.00372017 | 0.104473 | 1(Win) | true |
| Jsonifier | 21757.8 | 0.410326 | 2085.04ms | 466906 | 80 | 564126 | 20465.1 | 0.0104435 | 0.113618 | 2(Loss) | true |
| Glaze | 2627.59 | 0.0402233 | 8785.48ms | 466906 | 2560 | 1.18943e+07 | 169462 | 0.42795 | 0.942078 | 3(Loss) | true |
