
----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1013.35 | 0.142309 | 5996.28ms | 124597 | 2560 | 7.12863e+07 | 117260 | 0.150634 | 2.99869 | 1(Win) | true |
| Jsonifier | 992.938 | 0.159842 | 6099.11ms | 124597 | 2560 | 9.36689e+07 | 119670 | 0.216622 | 3.06027 | 2(Loss) | true |
| Glaze | 910.792 | 0.251776 | 6681.28ms | 124597 | 1280 | 1.38107e+08 | 130463 | 0.032467 | 3.33626 | 3(Loss) | true |
| simdjson (ondemand) | 840.422 | 0.316165 | 7239.1ms | 124597 | 320 | 6.39437e+07 | 141387 | 0.0134843 | 3.61589 | 4(Loss) | true |
