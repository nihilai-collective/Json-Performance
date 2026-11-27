
----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 23237.1 | 0.0527401 | 451.683ms | 108313 | 30 | 164.892 | 4445.27 | 0.0014997 | 0.105868 | 1(Win) | true |
| simdjson (stage-1) | 19473.9 | 0.0222517 | 538.123ms | 108313 | 80 | 111.448 | 5304.29 | 0.01202 | 0.126505 | 2(Loss) | true |
