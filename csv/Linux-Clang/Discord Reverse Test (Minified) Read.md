
----
### Discord Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 608.993 | 0.0688633 | 8795.13ms | 56369 | 2560 | 9.45958e+06 | 88273.1 | 0.872283 | 4.06417 | 1(Win) | true |
| simdjson (ondemand) | 146.659 | 0.104785 | 9395.32ms | 56369 | 1280 | 1.88832e+08 | 366550 | 0.372341 | 16.8805 | 2(Loss) | true |
