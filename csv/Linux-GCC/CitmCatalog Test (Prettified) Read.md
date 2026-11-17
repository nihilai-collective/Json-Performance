
----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19392.8 | 0.0947224 | 5744.68ms | 1151920 | 2560 | 7.37068e+06 | 56647.6 | 0.233393 | 0.127597 | 1(Win) | true |
| simdjson (stage-1) | 16059.2 | 0.404057 | 6804.8ms | 1151920 | 40 | 3.05592e+06 | 68406.6 | 0.374397 | 0.154098 | 2(Loss) | true |
