
----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5225.66 | 0.154297 | 2007.54ms | 108313 | 2560 | 2.38139e+06 | 19766.9 | 0.00840529 | 1(Win) | true |
| simdjson (stage-1) | 5007.2 | 0.111677 | 2071.91ms | 108313 | 4890 | 2.59541e+06 | 20629.4 | 0.140664 | 2(Loss) | true |
