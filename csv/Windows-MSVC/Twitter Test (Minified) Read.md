
----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 23382.3 | 0.0483207 | 1968.51ms | 466906 | 30 | 2540.23 | 19043.3 | 0.333685 | 0.105684 | 1(Win) | true |
| simdjson (stage-1) | 19020.6 | 0.27862 | 2447.22ms | 466906 | 640 | 2.72279e+06 | 23410.2 | 0.00867754 | 0.129914 | 2(Loss) | true |
