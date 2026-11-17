
----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3951.68 | 0.285257 | 5792.48ms | 466906 | 320 | 3.30611e+07 | 112680 | 0.332999 | 0.626326 | 1(Win) | true |
| Glaze | 2506.52 | 0.201374 | 9072.99ms | 466906 | 160 | 2.04759e+07 | 177647 | 0.131036 | 0.987537 | 2(Loss) | true |
| simdjson (ondemand) | 1687.38 | 0.0862415 | 6752.35ms | 466906 | 1280 | 6.62939e+07 | 263885 | 0.140388 | 1.46698 | 3(Loss) | true |
