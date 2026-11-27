
----
### Random Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 821.936 | 0.207853 | 10004.2ms | 676745 | 640 | 1.70477e+09 | 785212 | 0.10863 | 3.69749 | 1(Win) | true |
| simdjson (ondemand) | 556.097 | 0.159429 | 7346.47ms | 676745 | 160 | 5.4778e+08 | 1.16058e+06 | 0.0362558 | 5.46522 | 2(Loss) | true |
