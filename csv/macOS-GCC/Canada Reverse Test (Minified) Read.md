
----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 431.127 | 0.596792 | 7753.2ms | 2090234 | 30 | 2.28427e+10 | 4.6237e+06 | 3.43616 | 1(Win) | true |
| simdjson (ondemand) | 399.593 | 1.02145 | 7527.57ms | 2090234 | 40 | 1.03859e+11 | 4.98858e+06 | 0.0619272 | 2(Loss) | true |
