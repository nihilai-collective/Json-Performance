
----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 3352.2 | 0.442204 | 5061.81ms | 699405 | 80 | 6.19346e+07 | 198975 | 0.289819 | 0.738454 | 1(Win) | true |
| Jsonifier | 2652.49 | 0.101261 | 6470.99ms | 699405 | 1280 | 8.29944e+07 | 251464 | 0.778838 | 0.93301 | 2(Loss) | true |
| simdjson (ondemand) | 1544.89 | 0.161633 | 6231.54ms | 767297 | 160 | 9.37812e+07 | 473660 | 1.00374 | 1.60232 | 3(Loss) | true |
