
----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 2499.76 | 2.32097 | 196.734ms | 4669 | 40 | 68367.5 | 1781.25 | 5.12571 | -(Win) | false |
| Jsonifier (two-stage) | 1606.64 | 0.838824 | 309.763ms | 4669 | 2560 | 1.38355e+06 | 2771.45 | 0.706957 | 2(Loss) | true |
| Glaze | 1223.77 | 1.16577 | 350.023ms | 4669 | 4890 | 8.79797e+06 | 3638.52 | 0.797377 | 3(Loss) | true |
| simdjson (ondemand) | 497.548 | 0.377126 | 902.505ms | 4669 | 2560 | 2.91603e+06 | 8949.31 | 1.1495 | 4(Loss) | true |
