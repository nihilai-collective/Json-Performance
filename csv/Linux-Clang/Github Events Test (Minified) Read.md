
----
### Github Events Test (Minified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 24885.2 | 0.0285563 | 208.385ms | 53331 | 160 | 54.5006 | 2043.8 | 0.044055 | 0.098234 | 1(Win) | true |
| simdjson (stage-1) | 21693.5 | 0.0623174 | 239.375ms | 53331 | 40 | 85.3846 | 2344.5 | 0.015637 | 0.112726 | 2(Loss) | true |
