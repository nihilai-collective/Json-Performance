
----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19442.5 | 0.0378532 | 418.793ms | 83958 | 40 | 97.2045 | 4118.23 | 0.112583 | 0.126511 | 1(Win) | true |
| simdjson (stage-1) | 16042 | 0.141109 | 504.066ms | 83958 | 2560 | 126987 | 4991.19 | 0.0829446 | 0.15344 | 2(Loss) | true |
