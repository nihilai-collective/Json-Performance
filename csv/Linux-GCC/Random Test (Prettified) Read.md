
----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 14903.4 | 0.0745871 | 5452.56ms | 728486 | 80 | 96713.3 | 46615.9 | 0.243049 | 0.345506 | 1.8134 | 0.0990672 | 0.000153332 | 7.62712e-05 | 3.43177e-07 | 1(Win) | true |
| simdjson (stage-1) | 13548 | 0.0750615 | 5829.79ms | 728486 | 80 | 118527 | 51279.9 | 0.114144 | 0.379978 | 1.97425 | 0.0748896 | 0.000365055 | 7.30968e-06 | 3.68916e-06 | 2(Loss) | true |
