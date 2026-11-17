
----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12538.1 | 0.241207 | 3657.4ms | 475954 | 640 | 4.88006e+06 | 36202 | 0.012924 | 0.19726 | 1(Win) | true |
| simdjson (reflection) | 9390.69 | 0.357098 | 4837.85ms | 475954 | 80 | 2.38342e+06 | 48335.7 | 0.156444 | 0.263484 | 2(Loss) | true |
| Glaze | 5548.83 | 0.229838 | 8261.94ms | 475954 | 320 | 1.13116e+07 | 81802 | 0.162845 | 0.445982 | 3(Loss) | true |
