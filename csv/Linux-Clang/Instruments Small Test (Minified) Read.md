
----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2635.46 | 0.135857 | 178.17ms | 4669 | 80 | 421.492 | 1689.54 | 0.485194 | 0.924323 | 1(Win) | true |
| Jsonifier (two-stage) | 2195.86 | 0.539511 | 211.206ms | 4669 | 40 | 4787.41 | 2027.78 | 0.0603746 | 1.11136 | 2(Loss) | true |
| Glaze | 1571.27 | 0.194565 | 288.093ms | 4669 | 2560 | 77824.1 | 2833.82 | 0.0241996 | 1.56059 | 3(Loss) | true |
| simdjson (ondemand) | 624.272 | 0.0565436 | 733.43ms | 4669 | 30 | 487.964 | 7132.63 | 0.0658509 | 3.95112 | 4(Loss) | true |
