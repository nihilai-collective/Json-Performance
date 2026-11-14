
----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1528.86 | 0.0984896 | 10180.8ms | 5212421 | 160 | 1.64075e+09 | 3.2514e+06 | 1.07877 | 1.61936 | 1(Win) | true |
| simdjson (ondemand) | 1447.25 | 0.113376 | 5118.86ms | 5212421 | 40 | 6.06595e+08 | 3.43477e+06 | 0.685636 | 1.71069 | 2(Loss) | true |
