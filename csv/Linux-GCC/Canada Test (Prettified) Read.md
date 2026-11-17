
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1726.55 | 0.121 | 8894.77ms | 5212421 | 80 | 9.70919e+08 | 2.87912e+06 | 0.307602 | 1.43395 | 1(Win) | true |
| simdjson (ondemand) | 1651.11 | 0.109247 | 9317.35ms | 5212421 | 40 | 4.32717e+08 | 3.01067e+06 | 0.181893 | 1.49945 | 2(Loss) | true |
