
----
### Discord Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 653.054 | 0.0927213 | 746.889ms | 4857 | 40 | 1730.05 | 7092.82 | 0.10387 | 1(Win) | true |
| simdjson (ondemand) | 143.888 | 0.0518004 | 3313.43ms | 4857 | 30 | 8342.09 | 32191.7 | 0.00455584 | 2(Loss) | true |
