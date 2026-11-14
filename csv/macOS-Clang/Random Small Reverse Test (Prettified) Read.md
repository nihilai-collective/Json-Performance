
----
### Random Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1096.44 | 0.0371759 | 785.603ms | 8150 | 30 | 208.351 | 7088.83 | 0.0394831 | 1(Win) | true |
| simdjson (ondemand) | 554.241 | 0.0762428 | 1409.61ms | 8150 | 2560 | 292655 | 14023.6 | 0.0577459 | 2(Loss) | true |
