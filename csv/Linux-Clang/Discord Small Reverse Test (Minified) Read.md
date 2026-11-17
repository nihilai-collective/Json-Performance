
----
### Discord Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 717.385 | 0.0388405 | 1372.65ms | 4857 | 2560 | 16100.6 | 6456.77 | 0.0606805 | 7.20229 | 31.0804 | 6.14114 | 0.00752586 | 0.000122568 | 6.18469e-05 | 1(Win) | true |
| simdjson (ondemand) | 220.705 | 0.03803 | 2829.43ms | 4857 | 1280 | 81540.3 | 20987.2 | 0.0163184 | 23.3141 | 115.9 | 22.3562 | 0.0439289 | 6.03189e-05 | 1.49591e-05 | 2(Loss) | true |
