
----
### Discord Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 581.653 | 0.127834 | 802.644ms | 4857 | 2560 | 265303 | 7963.51 | 0.131386 | 1(Win) | true |
| simdjson (ondemand) | 128.404 | 0.461454 | 3635.62ms | 4857 | 640 | 1.77343e+07 | 36073.5 | 1.25188 | 2(Loss) | true |
