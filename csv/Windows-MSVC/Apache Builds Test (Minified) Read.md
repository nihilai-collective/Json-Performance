
----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 749.722 | 0.377262 | 6283.42ms | 94653 | 2560 | 5.28196e+08 | 120402 | 0.205626 | 4.05278 | 1(Win) | true |
| simdjson (ondemand) | 685.837 | 0.31673 | 6772.31ms | 94653 | 2560 | 4.44883e+08 | 131618 | 0.0293313 | 4.43048 | 2(Loss) | true |
