
----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21498.7 | 0.123762 | 510.225ms | 108313 | 40 | 1414.41 | 4804.73 | 0.486893 | 0.114489 | 1(Win) | true |
| simdjson (stage-1) | 15925.2 | 0.143353 | 651.148ms | 108313 | 40 | 3458.31 | 6486.27 | 0.54058 | 0.15481 | 2(Loss) | true |
