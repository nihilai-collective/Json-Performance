
----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1581.22 | 0.0238119 | 4500.25ms | 53331 | 4890 | 286862 | 32165.3 | 0.0803667 | 3.2558 | 11.6843 | 2.21519 | 0.0100457 | 3.35559e-05 | 1.96749e-05 | 1(Win) | true |
| simdjson (ondemand) | 1230.54 | 0.0326603 | 5417.13ms | 53331 | 2560 | 466496 | 41331.8 | 0.140279 | 4.18431 | 15.6491 | 3.01052 | 0.0164603 | 1.35138e-05 | 4.42402e-06 | 2(Loss) | true |
