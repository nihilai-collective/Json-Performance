
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 705.793 | 0.234792 | 7153.95ms | 409725 | 320 | 5.40686e+08 | 553624 | 0.445568 | 3.5076 | 1(Win) | true |
| simdjson (ondemand) | 614.779 | 0.200927 | 8348.6ms | 409725 | 80 | 1.30471e+08 | 635585 | 0.0868523 | 4.02694 | 2(Loss) | true |
