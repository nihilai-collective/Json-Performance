
----
### Canada Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 436.813 | 0.0642955 | 1028.97ms | 4630 | 30 | 1267.22 | 10108.5 | 0.0405436 | 1(Win) | true |
| simdjson (ondemand) | 398.66 | 0.138828 | 1127.76ms | 4630 | 2560 | 605273 | 11075.9 | 0.0240304 | 2(Loss) | true |
