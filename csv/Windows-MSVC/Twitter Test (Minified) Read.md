
----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 13983.1 | 1.24662 | 3162.65ms | 466906 | 1280 | 2.01712e+08 | 31844 | 0.177553 | 0.217064 | 1(Win) | true |
| simdjson (stage-1) | 11710.6 | 0.146882 | 4003.08ms | 466906 | 30 | 93574.7 | 38023.3 | 1.16964 | 0.259203 | 2(Loss) | true |
