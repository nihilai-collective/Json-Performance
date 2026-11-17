
----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 3371.5 | 0.302376 | 5321.37ms | 699405 | 80 | 2.86284e+07 | 197836 | 0.348189 | 0.734229 | 1(Win) | true |
| Jsonifier | 2607.5 | 0.187506 | 6788.62ms | 699405 | 1280 | 2.94473e+08 | 255802 | 0.619273 | 0.949091 | 2(Loss) | true |
| simdjson (ondemand) | 1408.04 | 0.609153 | 6870.13ms | 767297 | 320 | 3.20703e+09 | 519697 | 0.408658 | 1.75806 | 3(Loss) | true |
