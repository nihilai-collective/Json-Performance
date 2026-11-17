
----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4471.51 | 0.613051 | 7928.32ms | 699405 | 40 | 3.34505e+07 | 149168 | 1.70049 | 0.553574 | 1(Win) | true |
| Glaze | 3277.7 | 0.176402 | 5437.08ms | 699405 | 640 | 8.24721e+07 | 203498 | 0.988259 | 0.755234 | 2(Loss) | true |
| simdjson (ondemand) | 1462.9 | 0.207615 | 6890.58ms | 767297 | 80 | 8.62791e+07 | 500206 | 0.637527 | 1.6921 | 3(Loss) | true |
