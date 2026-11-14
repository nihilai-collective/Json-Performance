
----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 405.054 | 0.328177 | 1130.3ms | 4669 | 4890 | 6.36427e+06 | 10992.9 | 0.771589 | 1(Win) | true |
| simdjson (ondemand) | 153.448 | 0.742262 | 2666.83ms | 4669 | 160 | 7.42263e+06 | 29017.6 | 1.49902 | 2(Loss) | true |
