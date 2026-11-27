
----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1260.41 | 0.180128 | 3902.8ms | 53331 | 640 | 3.38128e+06 | 40352.3 | 0.0242725 | 1.9625 | 1(Win) | true |
| simdjson (ondemand) | 963.567 | 0.112515 | 5320.2ms | 53331 | 1280 | 4.51466e+06 | 52783.5 | 0.235521 | 2.56781 | 2(Loss) | true |
