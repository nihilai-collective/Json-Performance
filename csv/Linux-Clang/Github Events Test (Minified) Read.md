
----
### Github Events Test (Minified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 23370.5 | 0.0620777 | 219.99ms | 53331 | 30 | 54.754 | 2176.27 | 0.200248 | 0.104685 | 1(Win) | true |
| simdjson (stage-1) | 19620.3 | 0.0583343 | 252.394ms | 53331 | 30 | 68.5989 | 2592.23 | 0.0128573 | 0.124724 | 2(Loss) | true |
