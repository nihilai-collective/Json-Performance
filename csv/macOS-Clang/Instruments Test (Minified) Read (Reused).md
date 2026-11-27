
----
### Instruments Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1373.9 | 0.101387 | 7815.61ms | 108313 | 1280 | 7.43755e+06 | 75184.3 | 0.168991 | 1(Win) | true |
| simdjson (ondemand) | 1185.87 | 0.299989 | 9121.12ms | 108313 | 80 | 5.46248e+06 | 87105.3 | 0.115007 | 2(Loss) | true |
