
----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 23789.6 | 0.0531831 | 211.711ms | 53331 | 40 | 51.7122 | 2137.93 | 0.0907377 | 0.102718 | 1(Win) | true |
| simdjson (stage-1) | 21278.1 | 0.0559115 | 240.426ms | 53331 | 30 | 53.5816 | 2390.27 | 0.0418188 | 0.115038 | 2(Loss) | true |
