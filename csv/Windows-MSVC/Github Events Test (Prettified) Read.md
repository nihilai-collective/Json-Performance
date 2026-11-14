
----
### Github Events Test (Prettified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 23177.6 | 0.171814 | 284.122ms | 65103 | 80 | 1694.62 | 2678.75 | 0.0466853 | 0.105916 | 1(Win) | true |
| simdjson (stage-1) | 20825.8 | 0.147299 | 319.668ms | 65103 | 80 | 1542.72 | 2981.25 | 0.0419463 | 0.117572 | 2(Loss) | true |
