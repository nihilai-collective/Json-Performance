
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1371.49 | 0.209449 | 3959.24ms | 56369 | 160 | 1.07838e+06 | 39196.6 | 0.0467774 | 1.80397 | 1(Win) | true |
| simdjson (ondemand) | 1209.77 | 0.123053 | 4439.24ms | 56369 | 1280 | 3.82707e+06 | 44436.3 | 0.218225 | 2.04527 | 2(Loss) | true |
