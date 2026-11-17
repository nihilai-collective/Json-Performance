
----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3683.03 | 0.106832 | 6564.83ms | 466906 | 640 | 1.06766e+07 | 120899 | 0.0739047 | 1.36386 | 6.67782 | 0.888273 | 0.00194665 | 0.00133511 | 1.47614e-05 | 1(Win) | true |
| Glaze | 2647.64 | 0.0282442 | 9081.96ms | 466906 | 2560 | 5.77616e+06 | 168178 | 0.0114861 | 1.90203 | 7.7472 | 1.47693 | 0.00255937 | 0.000865839 | 1.69626e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1749.91 | 0.146611 | 6706.22ms | 466906 | 640 | 8.90727e+07 | 254457 | 0.0792577 | 2.86126 | 12.571 | 1.66787 | 0.00406015 | 0.0824364 | 1.70839e-05 | 3(Loss) | true |
