
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1662.96 | 0.462946 | 9293.09ms | 5212421 | 30 | 5.74508e+09 | 2.98922e+06 | 0.0918285 | 1.48878 | 1(Win) | true |
| simdjson (ondemand) | 1581.54 | 0.0741472 | 9702.86ms | 5212421 | 160 | 8.69012e+08 | 3.1431e+06 | 0.156772 | 1.56541 | 2(Loss) | true |
