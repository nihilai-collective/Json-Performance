
----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 519.012 | 0.0672719 | 960.479ms | 4669 | 30 | 999.269 | 8579.2 | 0.0640675 | 1(Win) | true |
| simdjson (ondemand) | 153.15 | 0.0794476 | 3019.1ms | 4669 | 2560 | 1.36589e+06 | 29074.2 | 0.0842164 | 2(Loss) | true |
