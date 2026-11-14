
----
### Github Events Test (Minified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 23005.2 | 0.0483675 | 227.25ms | 53331 | 40 | 45.7378 | 2210.82 | 0.0373303 | 0.106254 | 1(Win) | true |
| simdjson (stage-1) | 17323.3 | 0.050475 | 300.596ms | 53331 | 40 | 87.8436 | 2935.95 | 0.130961 | 0.141563 | 2(Loss) | true |
