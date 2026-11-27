
----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1041.96 | 0.716525 | 6321.62ms | 264040 | 30 | 8.99533e+07 | 241667 | 0.86148 | 2.37579 | 1(Win) | true |
| simdjson (ondemand) | 922.566 | 0.591113 | 7436.59ms | 264040 | 30 | 7.80922e+07 | 272943 | 0.0366511 | 2.68318 | 2(Loss) | true |
