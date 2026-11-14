
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1592.17 | 0.357652 | 6366.75ms | 108313 | 40 | 2.1536e+06 | 64877.2 | 0.293876 | 1.55433 | 1(Win) | true |
| simdjson (ondemand) | 1530.65 | 0.166741 | 6821.51ms | 108313 | 160 | 2.02589e+06 | 67484.8 | 0.0600588 | 1.61684 | 2(Loss) | true |
