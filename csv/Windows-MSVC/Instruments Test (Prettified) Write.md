
----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13647.8 | 0.0916796 | 1515.29ms | 213963 | 640 | 120249 | 14951.2 | 0.00209008 | 0.222311 | 1(Win) | true |
| Glaze | 4406.45 | 0.221367 | 4785.4ms | 213963 | 2560 | 2.69007e+07 | 46307.3 | 1.15655 | 0.689364 | 2(Loss) | true |
