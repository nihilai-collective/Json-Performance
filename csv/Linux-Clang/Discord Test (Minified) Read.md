
----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 23123.9 | 0.0262478 | 238.209ms | 56369 | 160 | 59.5751 | 2324.77 | 0.0142467 | 0.105876 | 1(Win) | true |
| simdjson (stage-1) | 19989.2 | 0.0426888 | 273.693ms | 56369 | 30 | 39.5402 | 2689.33 | 0.0247831 | 0.122764 | 2(Loss) | true |
