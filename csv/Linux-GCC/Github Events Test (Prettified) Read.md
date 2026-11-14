
----
### Github Events Test (Prettified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 20226.2 | 0.0437204 | 309.907ms | 65103 | 30 | 54.0333 | 3069.63 | 0.12177 | 0.121338 | 1(Win) | true |
| simdjson (stage-1) | 16549.2 | 0.0334248 | 382.384ms | 65103 | 160 | 251.596 | 3751.66 | 0.0470013 | 0.148471 | 2(Loss) | true |
