
----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 1449.73 | 0.0873348 | 320.629ms | 4857 | 40 | 311.456 | 3195.07 | 0.0075643 | 1.69331 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1440.2 | 0.3487 | 336.466ms | 4857 | 640 | 80495.5 | 3216.21 | 0.439429 | 1.70514 | 1(Tie) | true |
