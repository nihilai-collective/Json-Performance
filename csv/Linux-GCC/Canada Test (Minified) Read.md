
----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 24573.6 | 0.142052 | 8547.14ms | 2251027 | 1280 | 1.9712e+07 | 87359.8 | 0.31889 | 0.100716 | 1(Win) | true |
| simdjson (stage-1) | 16043.4 | 0.0510955 | 6904.28ms | 2251027 | 2560 | 1.19667e+07 | 133809 | 0.546384 | 0.154284 | 2(Loss) | true |
