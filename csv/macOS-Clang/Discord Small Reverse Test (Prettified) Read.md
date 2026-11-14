
----
### Discord Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 649.228 | 1.35824 | 970.793ms | 6701 | 80 | 1.42997e+06 | 9843.34 | 1.54595 | 1(Win) | true |
| simdjson (ondemand) | 162.227 | 0.437563 | 3699.61ms | 6701 | 640 | 1.90149e+07 | 39392.7 | 1.10032 | 2(Loss) | true |
