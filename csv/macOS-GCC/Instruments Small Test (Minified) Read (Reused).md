
----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1326.47 | 1.1355 | 377.017ms | 4669 | 160 | 232457 | 3356.8 | 0.0952381 | 1(Win) | true |
| simdjson (ondemand) | 1163.07 | 0.267641 | 433.134ms | 4669 | 2560 | 268770 | 3828.4 | 2.75845 | 2(Loss) | true |
