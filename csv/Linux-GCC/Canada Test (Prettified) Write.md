
----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5612.32 | 0.324949 | 7097.3ms | 6661897 | 160 | 2.16502e+09 | 1.13202e+06 | 0.256329 | 0.441132 | 1(Win) | true |
| Glaze | 3126.76 | 0.115765 | 6342.92ms | 6661897 | 160 | 8.85273e+08 | 2.0319e+06 | 0.0412362 | 0.791765 | 2(Loss) | true |
| simdjson (reflection) | 375.793 | 0.399086 | 5115.86ms | 6661989 | 30 | 1.36573e+11 | 1.69066e+07 | 0.636083 | 6.5881 | 3(Loss) | true |
