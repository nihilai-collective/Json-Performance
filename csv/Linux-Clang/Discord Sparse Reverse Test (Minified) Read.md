
----
### Discord Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1776.76 | 0.0162513 | 3758.56ms | 56369 | 4890 | 118226 | 30256.1 | 0.00287917 | 2.88616 | 13.3852 | 2.5076 | 0.00652264 | 2.02507e-05 | 1.18377e-05 | 1(Win) | true |
| simdjson (ondemand) | 1297.16 | 0.0890276 | 4800.8ms | 56369 | 640 | 871214 | 41442.7 | 0.105025 | 3.93463 | 17.4915 | 2.9041 | 0.00936871 | 5.7933e-06 | 1.41368e-06 | 2(Loss) | true |
